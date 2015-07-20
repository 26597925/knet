/*
 * Copyright (c) 2014-2015, dennis wang
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL dennis wang BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "channel_ref.h"
#include "channel.h"
#include "loop.h"
#include "misc.h"
#include "stream.h"
#include "loop_balancer.h"
#include "buffer.h"
#include "ringbuffer.h"
#include "address.h"
#include "loop_profile.h"


typedef struct _channel_ref_info_t {
    /* �������ݳ�Ա */
    int                      balance;         /* �Ƿ񱻸��ؾ����־ */
    channel_t*               channel;         /* �ڲ��ܵ� */
    dlist_node_t*            loop_node;       /* �ܵ�����ڵ� */
    stream_t*                stream;          /* �ܵ�(��/д)������ */
    loop_t*                  loop;            /* �ܵ���������loop_t */
    address_t*               peer_address;    /* �Զ˵�ַ */
    address_t*               local_address;   /* ���ص�ַ */
    channel_event_e          event;           /* �ܵ�Ͷ���¼� */
    volatile channel_state_e state;           /* �ܵ�״̬ */
    atomic_counter_t         ref_count;       /* ���ü��� */
    channel_ref_cb_t         cb;              /* �ص� */
    time_t                   last_recv_ts;    /* ���һ�ζ�����ʱ������룩 */
    time_t                   timeout;         /* �����г�ʱ���룩 */
    time_t                   connect_timeout; /* connect()��ʱ���룩 */
    int                      flag;            /* ѡȡ����ʹ���Զ����־λ */
    void*                    data;            /* ѡȡ����ʹ���Զ������� */
    void*                    user_data;       /* �û�����ָ�� */
    /* ��չ���ݳ�Ա */
} channel_ref_info_t;

struct _channel_ref_t {
    int                 share;     /* �Ƿ�ͨ��channel_ref_share()���� */
    uint64_t            domain_id; /* ��ID */
    dlist_node_t*       list_node; /* ������ڵ� */
    channel_ref_info_t* ref_info;  /* �ܵ���Ϣ */
};

channel_ref_t* channel_ref_create(loop_t* loop, channel_t* channel) {
    channel_ref_t* channel_ref = create(channel_ref_t);
    verify(channel_ref);
    memset(channel_ref, 0, sizeof(channel_ref_t));
    channel_ref->ref_info = create(channel_ref_info_t);
    verify(channel_ref->ref_info);
    memset(channel_ref->ref_info, 0, sizeof(channel_ref_info_t));
    channel_ref->ref_info->stream = stream_create(channel_ref);
    verify(channel_ref->ref_info->stream);
    channel_ref->ref_info->channel      = channel;
    channel_ref->ref_info->ref_count    = 0;
    channel_ref->ref_info->loop         = loop;
    channel_ref->ref_info->last_recv_ts = time(0);
    channel_ref->ref_info->state        = channel_state_init;
    loop_profile_increase_active_channel_count(loop_get_profile(loop));
    return channel_ref;
}

int channel_ref_destroy(channel_ref_t* channel_ref) {
    verify(channel_ref);
    /* ������ü��� */
    if (channel_ref->ref_info) {
        if (!atomic_counter_zero(&channel_ref->ref_info->ref_count)) {
            return error_ref_nonzero;
        }
        if (channel_ref->ref_info->peer_address) {
            address_destroy(channel_ref->ref_info->peer_address);
        }
        if (channel_ref->ref_info->local_address) {
            address_destroy(channel_ref->ref_info->local_address);
        }
        /* ֪ͨѡȡ��ɾ���ܵ������Դ */
        if ((channel_ref->ref_info->state != channel_state_init) && /* �Ѿ������뵽loop�ܵ����� */
            channel_ref->ref_info->loop) {
            impl_remove_channel_ref(channel_ref->ref_info->loop, channel_ref);
        }
        if (channel_ref->ref_info->channel) {
            channel_destroy(channel_ref->ref_info->channel);
        }
        if (channel_ref->ref_info->stream) {
            stream_destroy(channel_ref->ref_info->stream);
        }
        destroy(channel_ref->ref_info);
    }
    destroy(channel_ref);
    return error_ok;
}

int channel_ref_connect(channel_ref_t* channel_ref, const char* ip, int port, int timeout) {
    int     error = error_ok;
    loop_t* loop  = 0;
    verify(channel_ref);
    verify(port);
    if (!ip) {
        ip = "127.0.0.1";
    }
    if (channel_ref_check_state(channel_ref, channel_state_connect)) {
        /* �Ѿ���������״̬ */
        return error_connect_in_progress;
    }
    if (timeout) {
        /* ���ó�ʱʱ��� */
        channel_ref->ref_info->connect_timeout = time(0) + timeout;
    }
    /* ���Ŀ������ܾ�������ʧ�� */
    error = channel_connect(channel_ref->ref_info->channel, ip, port);
    if (error_ok != error) {
        return error;
    }
    /* ���ؾ��� */
    loop = channel_ref_choose_loop(channel_ref);
    if (loop) {
        /* ����ԭloop��active�ܵ����� */
        loop_profile_decrease_active_channel_count(
            loop_get_profile(channel_ref->ref_info->loop));
        /* ����Ŀ��loop */
        channel_ref->ref_info->loop = loop;
        /* ����Ŀ��loop��active�ܵ����� */
        loop_profile_increase_active_channel_count(loop_get_profile(loop));
        /* ��ӵ�����loop */
        loop_notify_connect(loop, channel_ref);
        return error_ok;
    }
    /* ��ǰ�߳��ڷ������� */
    return channel_ref_connect_in_loop(channel_ref);
}

void channel_ref_accept_async(channel_ref_t* channel_ref) {
    verify(channel_ref);
    loop_add_channel_ref(channel_ref->ref_info->loop, channel_ref);
    channel_ref_set_state(channel_ref, channel_state_accept);
    channel_ref_set_event(channel_ref, channel_event_recv);
}

int channel_ref_accept(channel_ref_t* channel_ref, const char* ip, int port, int backlog) {
    int error = 0;
    thread_id_t thread_id = 0;
    verify(channel_ref);
    verify(port);
    if (channel_ref_check_state(channel_ref, channel_state_accept)) {
        /* �Ѿ����ڼ���״̬ */
        return error_accept_in_progress;
    }
    /* ���� */
    error = channel_accept(channel_ref->ref_info->channel, ip, port, backlog);
    if (error == error_ok) {
        thread_id = loop_get_thread_id(channel_ref->ref_info->loop);
        if (thread_id) { /* loop_t��ĳ���߳����й� */
            if (thread_id != thread_get_self_id()) { /* ���߳����������� */
                loop_notify_accept_async(channel_ref->ref_info->loop, channel_ref);
                return error;
            }
        }
        /* ��ǰ�߳��� */
        loop_add_channel_ref(channel_ref->ref_info->loop, channel_ref);
        channel_ref_set_state(channel_ref, channel_state_accept);
        channel_ref_set_event(channel_ref, channel_event_recv);
    }
    return error;
}

channel_ref_t* channel_ref_share(channel_ref_t* channel_ref) {
    channel_ref_t* channel_ref_shared = 0;
    verify(channel_ref);
    channel_ref_shared = create(channel_ref_t);
    verify(channel_ref_shared);
    memset(channel_ref_shared, 0, sizeof(channel_ref_t));
    /* ���ӹܵ����ü��� */
    atomic_counter_inc(&channel_ref->ref_info->ref_count);
    /* ����ܵ���Ϣָ�� */
    channel_ref_shared->ref_info = channel_ref->ref_info;
    channel_ref_shared->share = 1;
    return channel_ref_shared;
}

void channel_ref_leave(channel_ref_t* channel_ref) {
    verify(channel_ref);
    /* �ݼ����ü��� */
    atomic_counter_dec(&channel_ref->ref_info->ref_count);
    /* �ܵ���Ϣ������loop_t���� */
    destroy(channel_ref);
}

void channel_ref_update_close_in_loop(loop_t* loop, channel_ref_t* channel_ref) {
    verify(loop);
    verify(channel_ref);
    if (channel_ref_check_state(channel_ref, channel_state_close)) {
        return;
    }
    channel_ref_set_state(channel_ref, channel_state_close);
    channel_ref_clear_event(channel_ref, channel_event_recv | channel_event_send);
    /* �ȵ��ûص�����֤���ڲ������Ի�õ�ַ��Ϣ */
    if (channel_ref->ref_info->cb) {
        channel_ref->ref_info->cb(channel_ref, channel_cb_event_close);
    }
    channel_close(channel_ref->ref_info->channel);
    loop_close_channel_ref(channel_ref->ref_info->loop, channel_ref);
}

void channel_ref_close(channel_ref_t* channel_ref) {
    loop_t*     loop = 0;
    verify(channel_ref);
    loop = channel_ref->ref_info->loop;
    if (!loop_get_thread_id(loop) || (channel_ref->ref_info->state == channel_state_init)) {
        /* δ�����뵽������ */
        channel_ref_destroy(channel_ref);
        return;
    }
    if (loop_get_thread_id(loop) != thread_get_self_id()) {
        /* ֪ͨ�ܵ������߳� */
        log_info("close channel cross thread, notify thread[id:%d]", loop_get_thread_id(loop));
        loop_notify_close(loop, channel_ref);
    } else {
        /* ���߳��ڹر� */
        log_info("close channel[%llu] in loop thread[id: %d]", channel_ref_get_uuid(channel_ref), loop_get_thread_id(loop));
        channel_ref_update_close_in_loop(loop, channel_ref);
    }
}

void channel_ref_update_send_in_loop(loop_t* loop, channel_ref_t* channel_ref, buffer_t* send_buffer) {
    int error = 0;
    verify(loop);
    verify(channel_ref);
    verify(send_buffer);
    loop_profile_add_send_bytes(loop_get_profile(loop), buffer_get_length(send_buffer));
    error = channel_send_buffer(channel_ref->ref_info->channel, send_buffer);
    switch (error) {
    case error_send_patial:
        channel_ref_set_event(channel_ref, channel_event_send);
        break;
    case error_send_fail:
        channel_ref_close(channel_ref);
        break;
    default:
        break;
    }
}

int channel_ref_write(channel_ref_t* channel_ref, const char* data, int size) {
    loop_t*   loop        = 0;
    buffer_t* send_buffer = 0;
    int       error       = error_ok;
    verify(channel_ref);
    verify(data);
    verify(size);
    if (!channel_ref_check_state(channel_ref, channel_state_active)) {
        return error_not_connected;
    }
    loop = channel_ref->ref_info->loop;
    if (loop_get_thread_id(loop) != thread_get_self_id()) {
        /* ת��loop�����̷߳��� */
        log_info("send cross thread, notify thread[id:%d]", loop_get_thread_id(loop));
        send_buffer = buffer_create(size);
        verify(send_buffer);
        if (!send_buffer) {
            return error_no_memory;
        }
        buffer_put(send_buffer, data, size);
        loop_notify_send(loop, channel_ref, send_buffer);
    } else {
        loop_profile_add_send_bytes(loop_get_profile(channel_ref->ref_info->loop), size);
        /* ��ǰ�̷߳��� */
        error = channel_send(channel_ref->ref_info->channel, data, size);
        switch (error) {
        case error_send_patial:
            channel_ref_set_event(channel_ref, channel_event_send);
            /* ���ڵ����߲��Ǵ��� */
            error = error_ok;
            break;
        case error_send_fail:
            channel_ref_close(channel_ref);
            break;
        default:
            break;
        }
    }
    return error;
}

socket_t channel_ref_get_socket_fd(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_get_socket_fd(channel_ref->ref_info->channel);
}

stream_t* channel_ref_get_stream(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->stream;
}

loop_t* channel_ref_get_loop(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->loop;
}

void channel_ref_set_loop_node(channel_ref_t* channel_ref, dlist_node_t* node) {
    verify(channel_ref); /* node����Ϊ0 */
    channel_ref->ref_info->loop_node = node;
}

dlist_node_t* channel_ref_get_loop_node(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->loop_node;
}

void channel_ref_set_event(channel_ref_t* channel_ref, channel_event_e e) {
    verify(channel_ref);
    impl_event_add(channel_ref, e);
    channel_ref->ref_info->event |= e;
}

channel_event_e channel_ref_get_event(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->event;
}

void channel_ref_clear_event(channel_ref_t* channel_ref, channel_event_e e) {
    verify(channel_ref);
    impl_event_remove(channel_ref, e);
    channel_ref->ref_info->event &= ~e;
}

void channel_ref_set_state(channel_ref_t* channel_ref, channel_state_e state) {
    verify(channel_ref);
    channel_ref->ref_info->state = state;
}

int channel_ref_check_state(channel_ref_t* channel_ref, channel_state_e state) {
    verify(channel_ref);
    return (channel_ref->ref_info->state == state);
}

int channel_ref_check_event(channel_ref_t* channel_ref, channel_event_e event) {
    verify(channel_ref);
    return (channel_ref->ref_info->event & event);
}

channel_ref_t* channel_ref_accept_from_socket_fd(channel_ref_t* channel_ref, loop_t* loop, socket_t client_fd, int event) {
    channel_t*     acceptor_channel    = 0;
    uint32_t       max_send_list_len   = 0;
    uint32_t       max_ringbuffer_size = 0;
    channel_t*     client_channel      = 0;
    channel_ref_t* client_ref          = 0;
    verify(channel_ref);
    verify(channel_ref->ref_info);
    verify(client_fd > 0);
    acceptor_channel = channel_ref->ref_info->channel;
    verify(acceptor_channel);
    max_send_list_len = channel_get_max_send_list_len(acceptor_channel);
    verify(max_send_list_len);
    max_ringbuffer_size = ringbuffer_get_max_size(channel_get_ringbuffer(acceptor_channel));
    verify(max_ringbuffer_size);
    client_channel = channel_create_exist_socket_fd(client_fd, max_send_list_len, max_ringbuffer_size);
    verify(client_channel);
    client_ref = channel_ref_create(loop, client_channel);
    verify(client_ref);
    if (event) {
        /* ��ӵ���ǰ�߳�loop */
        loop_add_channel_ref(channel_ref->ref_info->loop, client_ref);
        /* ������ͬʱ�����¼���״̬ */
        channel_ref_set_state(client_ref, channel_state_active);
        channel_ref_set_event(client_ref, channel_event_recv);
    }
    return client_ref;
}

void channel_ref_update_accept(channel_ref_t* channel_ref) {
    channel_ref_t* client_ref = 0;
    loop_t*        loop       = 0;
    socket_t       client_fd  = 0;
    verify(channel_ref);
    /* �鿴ѡȡ���Ƿ����Զ���ʵ�� */
    client_fd = impl_channel_accept(channel_ref);
    if (!client_fd) {
        /* Ĭ��ʵ�� */
        client_fd = socket_accept(channel_get_socket_fd(channel_ref->ref_info->channel));
    }
    verify(client_fd > 0);
    channel_ref_set_state(channel_ref, channel_state_accept);
    channel_ref_set_event(channel_ref, channel_event_recv);
    if (client_fd) {
        loop = channel_ref_choose_loop(channel_ref);
        if (loop) {
            client_ref = channel_ref_accept_from_socket_fd(channel_ref, loop, client_fd, 0);
            verify(client_ref);
            channel_ref_set_user_data(client_ref, channel_ref->ref_info->user_data);
            /* ���ûص� */
            channel_ref_set_cb(client_ref, channel_ref->ref_info->cb);
            /* ��ӵ�����loop */
            loop_notify_accept(loop, client_ref);
        } else {
            client_ref = channel_ref_accept_from_socket_fd(channel_ref, channel_ref->ref_info->loop, client_fd, 1);
            verify(client_ref);
            channel_ref_set_user_data(client_ref, channel_ref->ref_info->user_data);
            /* ���ûص� */
            if (channel_ref->ref_info->cb) {
                channel_ref->ref_info->cb(client_ref, channel_cb_event_accept);
            }
        }
    }
}

void channel_ref_update_accept_in_loop(loop_t* loop, channel_ref_t* channel_ref) {
    verify(loop);
    verify(channel_ref);
    /* ��ӵ���ǰ�߳�loop */
    loop_add_channel_ref(loop, channel_ref);
    channel_ref_set_state(channel_ref, channel_state_active);
    channel_ref_set_event(channel_ref, channel_event_recv);
    /* ���ûص� */
    if (channel_ref->ref_info->cb) {
        channel_ref->ref_info->cb(channel_ref, channel_cb_event_accept);
    }
}

void channel_ref_update_connect(channel_ref_t* channel_ref) {
    verify(channel_ref);
    channel_ref_set_event(channel_ref, channel_event_recv);
    channel_ref_set_state(channel_ref, channel_state_active);
    /* ���ûص� */
    if (channel_ref->ref_info->cb) {
        channel_ref->ref_info->cb(channel_ref, channel_cb_event_connect);
    }
}

void channel_ref_update_recv(channel_ref_t* channel_ref) {
    int error = 0;
    uint32_t bytes = 0;
    verify(channel_ref);
    bytes = stream_available(channel_ref->ref_info->stream);
    error = channel_update_recv(channel_ref->ref_info->channel);
    switch (error) {
        case error_recv_fail:
            channel_ref_close(channel_ref);
            break;
        case error_recv_buffer_full:
            channel_ref_close(channel_ref);
            break;
        default:
            break;
    }
    if (error == error_ok) {
        loop_profile_add_recv_bytes(loop_get_profile(channel_ref->ref_info->loop),
            stream_available(channel_ref->ref_info->stream) - bytes);
        if (channel_ref->ref_info->cb) {
            channel_ref->ref_info->cb(channel_ref, channel_cb_event_recv);
        }
        channel_ref_set_event(channel_ref, channel_event_recv);
    }
}

void channel_ref_update_send(channel_ref_t* channel_ref) {
    int error = 0;
    verify(channel_ref);
    error = channel_update_send(channel_ref->ref_info->channel);
    switch (error) {
        case error_send_fail:
            channel_ref_close(channel_ref);
            break;
        case error_send_patial:
            channel_ref_set_event(channel_ref, channel_event_send);
            break;
        default:
            break;
    }
    if (error == error_ok) {
        if (channel_ref->ref_info->cb) {
            channel_ref->ref_info->cb(channel_ref, channel_cb_event_send);
        }
    }
}

void channel_ref_update(channel_ref_t* channel_ref, channel_event_e e, time_t ts) {
    verify(channel_ref);
    if (channel_ref_check_state(channel_ref, channel_state_close)) {
        return;
    }
    if ((e & channel_event_recv) && channel_ref_check_event(channel_ref, channel_event_recv)) {
        if (channel_ref_check_state(channel_ref, channel_state_accept)) {
            /* ������ */
            channel_ref_update_accept(channel_ref);
        } else {
            /* ���һ�ζ�ȡ�����ݵ�ʱ������룩 */
            channel_ref->ref_info->last_recv_ts = ts;
            /* �� */
            channel_ref_update_recv(channel_ref);
        }
    } 
    if ((e & channel_event_send) && channel_ref_check_event(channel_ref, channel_event_send)) {
        if (channel_ref_check_state(channel_ref, channel_state_connect)) {
            /* ������� */
            channel_ref_update_connect(channel_ref);
        } else {
            /* д */
            channel_ref_update_send(channel_ref);
        }
    }
}

ringbuffer_t* channel_ref_get_ringbuffer(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_get_ringbuffer(channel_ref->ref_info->channel);
}

loop_t* channel_ref_choose_loop(channel_ref_t* channel_ref) {
    loop_t*          loop         = 0;
    loop_t*          current_loop = 0;
    loop_balancer_t* balancer     = 0;
    verify(channel_ref);
    current_loop = channel_ref->ref_info->loop;
    /*if (!loop_get_thread_id(current_loop)) {
        return 0;
    }*/
    balancer = loop_get_balancer(current_loop);
    if (!balancer) {
        return 0;
    }
    /* ����Ƿ�����loop_balancer_out���� */
    if (loop_check_balance_options(channel_ref->ref_info->loop, loop_balancer_out)) {
        loop = loop_balancer_choose(balancer);
        if (loop == channel_ref->ref_info->loop) {
            return 0;
        }
    }
    return loop;
}

void channel_ref_set_flag(channel_ref_t* channel_ref, int flag) {
    verify(channel_ref);
    channel_ref->ref_info->flag = flag;
}

int channel_ref_get_flag(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->flag;
}

void channel_ref_set_data(channel_ref_t* channel_ref, void* data) {
    verify(channel_ref);
    channel_ref->ref_info->data = data;
}

void* channel_ref_get_data(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->data;
}

void channel_ref_set_loop(channel_ref_t* channel_ref, loop_t* loop) {
    channel_ref->ref_info->loop = loop;
}

int channel_ref_check_balance(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->balance;
}

void channel_ref_set_timeout(channel_ref_t* channel_ref, int timeout) {
    verify(channel_ref); /* timeout����Ϊ0 */
    channel_ref->ref_info->timeout = (time_t)timeout;
}

int channel_ref_check_connect_timeout(channel_ref_t* channel_ref, time_t ts) {
    verify(channel_ref);
    if (channel_ref_check_state(channel_ref, channel_state_connect)) {
        if (channel_ref->ref_info->connect_timeout) {
            return (channel_ref->ref_info->connect_timeout < ts);
        }
    }
    return 0;
}

int channel_ref_check_timeout(channel_ref_t* channel_ref, time_t ts) {
    verify(channel_ref);
    if (!channel_ref->ref_info->timeout) {
        return 0;
    }
    if ((ts - channel_ref->ref_info->last_recv_ts) > channel_ref->ref_info->timeout) {
        channel_ref->ref_info->last_recv_ts = ts;
        return 1;
    }
    return 0;
}

void channel_ref_set_cb(channel_ref_t* channel_ref, channel_ref_cb_t cb) {
    verify(channel_ref);
    channel_ref->ref_info->cb = cb;
}

channel_ref_cb_t channel_ref_get_cb(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->cb;
}

int channel_ref_connect_in_loop(channel_ref_t* channel_ref) {
    verify(channel_ref);
    loop_add_channel_ref(channel_ref->ref_info->loop, channel_ref);
    channel_ref_set_state(channel_ref, channel_state_connect);
    channel_ref_set_event(channel_ref, channel_event_send);
    return error_ok;
}

address_t* channel_ref_get_peer_address(channel_ref_t* channel_ref) {
    verify(channel_ref);
    if (channel_ref->ref_info->peer_address) {
        return channel_ref->ref_info->peer_address;
    }
    channel_ref->ref_info->peer_address = address_create();
    socket_getpeername(channel_ref, channel_ref->ref_info->peer_address);
    return channel_ref->ref_info->peer_address;
}

address_t* channel_ref_get_local_address(channel_ref_t* channel_ref) {
    verify(channel_ref);
    if (channel_ref->ref_info->local_address) {
        return channel_ref->ref_info->local_address;
    }
    channel_ref->ref_info->local_address = address_create();
    socket_getsockname(channel_ref, channel_ref->ref_info->local_address);
    return channel_ref->ref_info->local_address;
}

void channel_ref_set_domain_node(channel_ref_t* channel_ref, dlist_node_t* node) {
    verify(channel_ref);
    channel_ref->list_node = node;
}

dlist_node_t* channel_ref_get_domain_node(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->list_node;
}

int channel_ref_check_share(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->share;
}

void channel_ref_set_domain_id(channel_ref_t* channel_ref, uint64_t domain_id) {
    verify(channel_ref);
    channel_ref->domain_id = domain_id;
}

uint64_t channel_ref_get_domain_id(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->domain_id;
}

void channel_ref_incref(channel_ref_t* channel_ref) {
    verify(channel_ref);
    atomic_counter_inc(&channel_ref->ref_info->ref_count);
}

void channel_ref_decref(channel_ref_t* channel_ref) {
    verify(channel_ref);
    atomic_counter_dec(&channel_ref->ref_info->ref_count);
}

int channel_ref_check_ref(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return !atomic_counter_zero(&channel_ref->ref_info->ref_count);
}

int channel_ref_get_ref(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->ref_count;
}

uint64_t channel_ref_get_uuid(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_get_uuid(channel_ref->ref_info->channel);
}

int channel_ref_equal(channel_ref_t* a, channel_ref_t* b) {
    return ((channel_ref_get_uuid(a) == channel_ref_get_uuid(b)) &&
        (a->ref_info == b->ref_info));
}

void channel_ref_set_user_data(channel_ref_t* channel_ref, void* data) {
    verify(channel_ref);
    channel_ref->ref_info->user_data = data;
}

void* channel_ref_get_user_data(channel_ref_t* channel_ref) {
    verify(channel_ref);
    return channel_ref->ref_info->user_data;
}
