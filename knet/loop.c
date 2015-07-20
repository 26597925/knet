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

#include "config.h"
#include "loop.h"
#include "list.h"
#include "channel_ref.h"
#include "channel.h"
#include "misc.h"
#include "loop_balancer.h"
#include "loop_profile.h"
#include "stream.h"


struct _loop_t {
    dlist_t*              active_channel_list; /* ��Ծ�ܵ����� */
    dlist_t*              close_channel_list;  /* �ѹرչܵ����� */
    dlist_t*              event_list;          /* �¼����� */
    lock_t*               lock;                /* ��-�¼�����*/
    channel_ref_t*        notify_channel;      /* �¼�֪ͨд�ܵ� */
    channel_ref_t*        read_channel;        /* �¼�֪ͨ���ܵ� */
    loop_balancer_t*      balancer;            /* ���ؾ����� */
    void*                 impl;                /* �¼�ѡȡ��ʵ�� */
    volatile int          running;             /* �¼�ѭ�����б�־ */
    thread_id_t           thread_id;           /* �¼�ѡȡ����ǰ�����߳�ID */
    loop_balance_option_e balance_options;     /* ���ؾ������� */
    loop_profile_t*       profile;             /* ͳ�� */
    void*                 data;                /* �û�����ָ�� */
};

typedef enum _loop_event_e {
    loop_event_accept = 1,    /* �����������¼� */
    loop_event_connect,       /* ���������¼� */
    loop_event_send,          /* �����¼� */
    loop_event_close,         /* �ر��¼� */
    loop_event_accept_async,  /* �첽������� */
} loop_event_e;

typedef struct _loop_event_t {
    channel_ref_t* channel_ref; /* �¼���عܵ� */
    buffer_t*      send_buffer; /* ���ͻ�����ָ�� */
    loop_event_e   event;       /* �¼����� */
} loop_event_t;

loop_event_t* loop_event_create(channel_ref_t* channel_ref, buffer_t* send_buffer, loop_event_e e) {
    loop_event_t* ev = 0;
    verify(channel_ref); /* send_buffer����Ϊ0 */
    ev = create(loop_event_t);
    verify(ev);
    ev->channel_ref = channel_ref;
    ev->send_buffer = send_buffer;
    ev->event = e;
    return ev;
}

void loop_event_destroy(loop_event_t* loop_event) {
    verify(loop_event);
    destroy(loop_event);
}

channel_ref_t* loop_event_get_channel_ref(loop_event_t* loop_event) {
    verify(loop_event);
    return loop_event->channel_ref;
}

buffer_t* loop_event_get_send_buffer(loop_event_t* loop_event) {
    verify(loop_event);
    return loop_event->send_buffer;
}

loop_event_e loop_event_get_event(loop_event_t* loop_event) {
    verify(loop_event);
    return loop_event->event;
}

loop_t* loop_create() {
    socket_t pair[2] = {0}; /* �¼���д������ */
    loop_t*  loop    = create(loop_t);
    verify(loop);
    memset(loop, 0, sizeof(loop_t));
    /* ����ѡȡ��ʵ�� */
    if (impl_create(loop)) {
        destroy(loop);
        log_fatal("loop_create() failed, reason: impl_create()");
        return 0;
    }
    /* ������д������ */
    if (socket_pair(pair)) {
        destroy(loop);
        log_fatal("loop_create() failed, reason: socket_pair()");
        return 0;
    }
    loop->profile = loop_profile_create(loop);
    loop->active_channel_list = dlist_create();
    loop->close_channel_list = dlist_create();
    loop->event_list = dlist_create();
    loop->lock = lock_create();
    loop->balance_options = loop_balancer_in | loop_balancer_out;
    loop->notify_channel = loop_create_channel_exist_socket_fd(loop, pair[0], 0, 0);
    verify(loop->notify_channel);
    loop->read_channel = loop_create_channel_exist_socket_fd(loop, pair[1], 0, 1024 * 64);
    verify(loop->read_channel);
    loop_add_channel_ref(loop, loop->notify_channel);
    loop_add_channel_ref(loop, loop->read_channel);
    channel_ref_set_state(loop->notify_channel, channel_state_active);
    channel_ref_set_state(loop->read_channel, channel_state_active);
    /* ע����¼� */
    channel_ref_set_event(loop->read_channel, channel_event_recv);
    /* ���ö��¼��ص� */
    channel_ref_set_cb(loop->read_channel, loop_queue_cb);
    return loop;
}

void loop_destroy(loop_t* loop) {
    dlist_node_t*  node        = 0;
    dlist_node_t*  temp        = 0;
    channel_ref_t* channel_ref = 0;
    loop_event_t*  event       = 0;
    verify(loop);
    /* �رչܵ� */
    dlist_for_each_safe(loop->active_channel_list, node, temp) {
        channel_ref = (channel_ref_t*)dlist_node_get_data(node);
        channel_ref_update_close_in_loop(channel_ref_get_loop(channel_ref), channel_ref);
    }
    /* �����ѹرչܵ� */
    dlist_for_each_safe(loop->close_channel_list, node, temp) {
        channel_ref = (channel_ref_t*)dlist_node_get_data(node);
        channel_ref_destroy(channel_ref);
    }
    /* ����ѡȡ�� */
    impl_destroy(loop);
    dlist_destroy(loop->close_channel_list);
    dlist_destroy(loop->active_channel_list);
    /* ����δ�����¼� */
    dlist_for_each_safe(loop->event_list, node, temp) {
        event = (loop_event_t*)dlist_node_get_data(node);
        destroy(event);
    }
    loop_profile_destroy(loop->profile);
    dlist_destroy(loop->event_list);
    lock_destroy(loop->lock);
    destroy(loop);
}

void loop_add_event(loop_t* loop, loop_event_t* loop_event) {
    verify(loop);
    verify(loop_event);
    lock_lock(loop->lock);
    log_info("invoke loop_add_event(), event[type:%d]", loop_event->event);
    /* �¼���ӵ�����β�� */
    dlist_add_tail_node(loop->event_list, loop_event);
    lock_unlock(loop->lock);
    loop_notify(loop);
}

void loop_notify_accept(loop_t* loop, channel_ref_t* channel_ref) {
    verify(loop);
    verify(channel_ref);
    loop_add_event(loop, loop_event_create(channel_ref, 0, loop_event_accept));
}

void loop_notify_accept_async(loop_t* loop, channel_ref_t* channel_ref) {
    verify(loop);
    verify(channel_ref);
    loop_add_event(loop, loop_event_create(channel_ref, 0, loop_event_accept_async));
}

void loop_notify_connect(loop_t* loop, channel_ref_t* channel_ref) {
    verify(loop);
    verify(channel_ref);
    loop_add_event(loop, loop_event_create(channel_ref, 0, loop_event_connect));
}

void loop_notify_send(loop_t* loop, channel_ref_t* channel_ref, buffer_t* send_buffer) {
    verify(loop);
    verify(channel_ref);
    verify(send_buffer);
    loop_add_event(loop, loop_event_create(channel_ref, send_buffer, loop_event_send));
}

void loop_notify_close(loop_t* loop, channel_ref_t* channel_ref) {
    verify(loop);
    verify(channel_ref);
    loop_add_event(loop, loop_event_create(channel_ref, 0, loop_event_close));
}

void loop_queue_cb(channel_ref_t* channel, channel_cb_event_e e) {
    verify(channel);
    if (e & channel_cb_event_recv) {
        /* ������ж��������� */
        stream_eat_all(channel_ref_get_stream(channel));
        loop_event_process(channel_ref_get_loop(channel));
    } else if (e & channel_cb_event_close) {
        if (loop_check_running(channel_ref_get_loop(channel))) {
            /* ���ӶϿ�, �������� */
            verify(0);
        }
    }
}

void loop_notify(loop_t* loop) {
    char c = 1;
    verify(loop);
    /* ����һ���ֽڴ������ص�  */
    socket_send(channel_ref_get_socket_fd(loop->notify_channel), &c, sizeof(c));
}

void loop_event_process(loop_t* loop) {
    dlist_node_t* node       = 0;
    dlist_node_t* temp       = 0;
    loop_event_t* loop_event = 0;
    verify(loop);
    lock_lock(loop->lock);
    /* ÿ�ζ��¼��ص��ڴ��������¼����� */
    dlist_for_each_safe(loop->event_list, node, temp) {
        loop_event = (loop_event_t*)dlist_node_get_data(node);
        switch(loop_event->event) {
            case loop_event_accept:
                channel_ref_update_accept_in_loop(loop, loop_event->channel_ref);
                break;
            case loop_event_accept_async:
                channel_ref_accept_async(loop_event->channel_ref);
                break;
            case loop_event_connect:
                channel_ref_connect_in_loop(loop_event->channel_ref);
                break;
            case loop_event_send:
                channel_ref_update_send_in_loop(loop, loop_event->channel_ref, loop_event->send_buffer);
                break;
            case loop_event_close:
                channel_ref_update_close_in_loop(loop, loop_event->channel_ref);
                break;
            default:
                break;
        }
        loop_event_destroy(loop_event);
        dlist_delete(loop->event_list, node);
    }
    lock_unlock(loop->lock);
}

channel_ref_t* loop_create_channel_exist_socket_fd(loop_t* loop, socket_t socket_fd, uint32_t max_send_list_len, uint32_t recv_ring_len) {
    verify(loop);
    return channel_ref_create(loop, channel_create_exist_socket_fd(socket_fd, max_send_list_len, recv_ring_len));
}

channel_ref_t* loop_create_channel(loop_t* loop, uint32_t max_send_list_len, uint32_t recv_ring_len) {
    verify(loop);
    return channel_ref_create(loop, channel_create(max_send_list_len, recv_ring_len));
}

thread_id_t loop_get_thread_id(loop_t* loop) {
    verify(loop);
    return loop->thread_id;
}

int loop_run_once(loop_t* loop) {
    verify(loop);
    loop->thread_id = thread_get_self_id();
    return impl_run_once(loop);
}

int loop_run(loop_t* loop) {
    int error = 0;
    verify(loop);
    loop->running = 1;
    while (loop->running) {
        error = loop_run_once(loop);
        if (error_loop_fail == error) {
            loop->running = 0;
        }
    }
    return error;
}

void loop_exit(loop_t* loop) {
    verify(loop);
    loop->running = 0;
}

dlist_t* loop_get_active_list(loop_t* loop) {
    verify(loop);
    return loop->active_channel_list;
}

dlist_t* loop_get_close_list(loop_t* loop) {
    verify(loop);
    return loop->close_channel_list;
}

void loop_add_channel_ref(loop_t* loop, channel_ref_t* channel_ref) {
    dlist_node_t* node = 0;
    verify(channel_ref);
    verify(loop);
    node = channel_ref_get_loop_node(channel_ref);
    if (node) {
        /* �Ѿ��������������Ҫ��������ڵ� */
        dlist_add_front(loop->active_channel_list, node);
    } else {
        /* ��������ڵ� */
        dlist_add_front_node(loop->active_channel_list, channel_ref);
    }
    loop_profile_decrease_active_channel_count(loop->profile);
    loop_profile_increase_established_channel_count(loop->profile);
    /* ���ýڵ� */
    channel_ref_set_loop_node(channel_ref, dlist_get_front(loop->active_channel_list));
    /* ֪ͨѡȡ����ӹܵ� */
    impl_add_channel_ref(loop, channel_ref);
}

void loop_remove_channel_ref(loop_t* loop, channel_ref_t* channel_ref) {
    verify(loop);
    verify(channel_ref);
    /* ����뵱ǰ����������������ٽڵ� */
    dlist_remove(loop->active_channel_list, channel_ref_get_loop_node(channel_ref));
    loop_profile_decrease_established_channel_count(loop->profile);
    loop_profile_increase_close_channel_count(loop->profile);
}

void loop_set_impl(loop_t* loop, void* impl) {
    verify(loop);
    verify(impl);
    loop->impl = impl;
}

void* loop_get_impl(loop_t* loop) {
    verify(loop);
    return loop->impl;
}

void loop_close_channel_ref(loop_t* loop, channel_ref_t* channel_ref) {
    verify(loop);
    verify(channel_ref);
    /* ����㺯�����׽����Ѿ����ر� */
    /* �ӻ�Ծ������ȡ�� */
    loop_remove_channel_ref(loop, channel_ref);
    /* ���뵽�ѹر����� */
    dlist_add_front(loop->close_channel_list, channel_ref_get_loop_node(channel_ref));
}

void loop_set_balancer(loop_t* loop, loop_balancer_t* balancer) {
    verify(loop); /* balancer����Ϊ0 */
    loop->balancer = balancer;
}

loop_balancer_t* loop_get_balancer(loop_t* loop) {
    verify(loop);
    return loop->balancer;
}

void loop_check_timeout(loop_t* loop, time_t ts) {
    dlist_node_t*  node        = 0;
    dlist_node_t*  temp        = 0;
    channel_ref_t* channel_ref = 0;
    verify(loop);
    dlist_for_each_safe(loop_get_active_list(loop), node, temp) {
        channel_ref = (channel_ref_t*)dlist_node_get_data(node);
        if (channel_ref_check_state(channel_ref, channel_state_connect)) {
            if (socket_check_send_ready(channel_ref_get_socket_fd(channel_ref))) {
                impl_event_add(channel_ref, channel_event_send);
            }
            if (channel_ref_check_connect_timeout(channel_ref, ts)) {
                /* ���ӳ�ʱ */            
                if (channel_ref_get_cb(channel_ref)) {
                    channel_ref_get_cb(channel_ref)(channel_ref, channel_cb_event_connect_timeout);
                }
            }
        }
        if (channel_ref_check_timeout(channel_ref, ts)) {
            /* ����ʱ������ */
            if (channel_ref_get_cb(channel_ref)) {
                channel_ref_get_cb(channel_ref)(channel_ref, channel_cb_event_timeout);
            }
        }
    }
}

void loop_check_close(loop_t* loop) {
    dlist_node_t*  node        = 0;
    dlist_node_t*  temp        = 0;
    channel_ref_t* channel_ref = 0;
    verify(loop);
    dlist_for_each_safe(loop_get_close_list(loop), node, temp) {
        channel_ref = (channel_ref_t*)dlist_node_get_data(node);
        if (error_ok == channel_ref_destroy(channel_ref)) {
            loop_profile_decrease_close_channel_count(loop->profile);
            dlist_delete(loop_get_close_list(loop), node);
        }
    }
}

int loop_check_running(loop_t* loop) {
    verify(loop);
    return loop->running;
}

int loop_get_active_channel_count(loop_t* loop) {
    verify(loop);
    return dlist_get_count(loop->active_channel_list);
}

int loop_get_close_channel_count(loop_t* loop) {
    verify(loop);
    return dlist_get_count(loop->close_channel_list);
}

void loop_set_balance_options(loop_t* loop, loop_balance_option_e options) {
    verify(loop);
    loop->balance_options = options;
}

loop_balance_option_e loop_get_balance_options(loop_t* loop) {
    verify(loop);
    return loop->balance_options;
}

int loop_check_balance_options(loop_t* loop, loop_balance_option_e options) {
    verify(loop);
    return (loop->balance_options & options);
}

void loop_set_data(loop_t* loop, void* data) {
    verify(loop);
    loop->data = data;
}

void* loop_get_data(loop_t* loop) {
    verify(loop);
    return loop->data;
}

loop_profile_t* loop_get_profile(loop_t* loop) {
    verify(loop);
    return loop->profile;
}
