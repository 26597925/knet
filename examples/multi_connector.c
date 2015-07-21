#include "example_config.h"

#if COMPILE_MULTI_CONNECTOR

#include "knet.h"

/**
 ����kloop_tʵ��, �����������һ��������
 */

#define MAX_CONNECTOR 200  /* �������������� */
int connector_count = MAX_CONNECTOR; /* ��ǰ���������� */

/* �ͻ��� - �������ص� */
void connector_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    char buffer[32] = {0};
    char* hello = "hello world";
    kstream_t* stream = knet_channel_ref_get_stream(channel);
    if (e & channel_cb_event_connect) { /* ���ӳɹ� */
        /* д�� */
        knet_stream_push(stream, hello, 12);
    } else if (e & channel_cb_event_recv) {
        /* echo���ݶ�ȡ */
        knet_stream_pop(stream, buffer, sizeof(buffer));
        /* �ر� */
        knet_channel_ref_close(channel);
    } else if (e & channel_cb_event_connect_timeout) {
        /* �ر� */
        knet_channel_ref_close(channel);
        printf("connector close: timeout\n");
    }
}

/* ����� - �ͻ��˻ص� */
void client_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    char buffer[32] = {0};
    kaddress_t* peer_address = 0;
    kstream_t* stream = knet_channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        /* ��ȡ */
        knet_stream_pop(stream, buffer, sizeof(buffer));
        /* �����Ƿ��ȡ������ д��12�ֽ� */
        knet_stream_push(stream, buffer, 12);
    } else if (e & channel_cb_event_close) {
        peer_address = knet_channel_ref_get_peer_address(channel);
        printf("peer close: %s, %d, %d\n", address_get_ip(peer_address),
            address_get_port(peer_address), connector_count);
        /* �Զ˹ر� */
        connector_count--;
        if (connector_count == 0) { /* ȫ���ر� */
            /* �˳� */
            knet_loop_exit(knet_channel_ref_get_loop(channel));
        }
    }
}

/* �����߻ص� */
void acceptor_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    if (e & channel_cb_event_accept) { /* ������ */
        /* ���ûص� */
        knet_channel_ref_set_cb(channel, client_cb);
    }
}

int main() {
    int i = 0;
    kchannel_ref_t* connector = 0;
    /* ����ѭ�� */
    kloop_t* loop = knet_loop_create();
    /* ���������� */
    kchannel_ref_t* acceptor = knet_loop_create_channel(loop, 8, 1024);
    /* ���ûص� */
    knet_channel_ref_set_cb(acceptor, acceptor_cb);
    /* ���� */
    knet_channel_ref_accept(acceptor, 0, 80, 500);
    /* ���� */
    for (; i < MAX_CONNECTOR; i++) {
        /* �����ͻ��� */
        connector = knet_loop_create_channel(loop, 8, 1024);
        /* ���ûص� */
        knet_channel_ref_set_cb(connector, connector_cb);
        knet_channel_ref_connect(connector, "127.0.0.1", 80, 2);
    }
    /* ���� */
    knet_loop_run(loop);
    /* ����, connector, acceptor����Ҫ�ֶ����� */
    knet_loop_destroy(loop);
    return 0;
}

#endif /* COMPILE_MULTI_CONNECTOR */
