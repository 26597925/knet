#include "example_config.h"

#if COMPILE_MULTI_CONNECTOR

#include "knet.h"

/*
 ����loop_tʵ��, �����������һ��������
 */

#define MAX_CONNECTOR 200  /* �������������� */
int connector_count = MAX_CONNECTOR; /* ��ǰ���������� */

/* �ͻ��� - �������ص� */
void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
    char buffer[32] = {0};
    char* hello = "hello world";
    stream_t* stream = channel_ref_get_stream(channel);
    if (e & channel_cb_event_connect) { /* ���ӳɹ� */
        /* д�� */
        stream_push(stream, hello, 12);
    } else if (e & channel_cb_event_recv) {
        /* echo���ݶ�ȡ */
        stream_pop(stream, buffer, sizeof(buffer));
        /* �ر� */
        channel_ref_close(channel);
    } else if (e & channel_cb_event_connect_timeout) {
        /* �ر� */
        channel_ref_close(channel);
        printf("connector close: timeout\n");
    }
}

/* ����� - �ͻ��˻ص� */
void client_cb(channel_ref_t* channel, channel_cb_event_e e) {
    char buffer[32] = {0};
    address_t* peer_address = 0;
    stream_t* stream = channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        /* ��ȡ */
        stream_pop(stream, buffer, sizeof(buffer));
        /* �����Ƿ��ȡ������ д��12�ֽ� */
        stream_push(stream, buffer, 12);
    } else if (e & channel_cb_event_close) {
        peer_address = channel_ref_get_peer_address(channel);
        printf("peer close: %s, %d, %d\n", address_get_ip(peer_address),
            address_get_port(peer_address), connector_count);
        /* �Զ˹ر� */
        connector_count--;
        if (connector_count == 0) { /* ȫ���ر� */
            /* �˳� */
            loop_exit(channel_ref_get_loop(channel));
        }
    }
}

/* �����߻ص� */
void acceptor_cb(channel_ref_t* channel, channel_cb_event_e e) {
    if (e & channel_cb_event_accept) { /* ������ */
        /* ���ûص� */
        channel_ref_set_cb(channel, client_cb);
    }
}

int main() {
    int i = 0;
    channel_ref_t* connector = 0;
    /* ����ѭ�� */
    loop_t* loop = loop_create();
    /* ���������� */
    channel_ref_t* acceptor = loop_create_channel(loop, 8, 1024);
    /* ���ûص� */
    channel_ref_set_cb(acceptor, acceptor_cb);
    /* ���� */
    channel_ref_accept(acceptor, 0, 80, 500);
    /* ���� */
    for (; i < MAX_CONNECTOR; i++) {
        /* �����ͻ��� */
        connector = loop_create_channel(loop, 8, 1024);
        /* ���ûص� */
        channel_ref_set_cb(connector, connector_cb);
        channel_ref_connect(connector, "127.0.0.1", 80, 2);
    }
    /* ���� */
    loop_run(loop);
    /* ����, connector, acceptor����Ҫ�ֶ����� */
    loop_destroy(loop);
    return 0;
}

#endif /* COMPILE_MULTI_CONNECTOR */
