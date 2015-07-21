#include "example_config.h"

#if COMPILE_BASIC_C

#include "knet.h"

/**
 ����kloop_tʵ��, ����������������������
 */

/* �ͻ��� - �������ص� */
void connector_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    char* hello = "hello world";
    kstream_t* stream = knet_channel_ref_get_stream(channel);
    if (e & channel_cb_event_connect) { /* ���ӳɹ� */
        /* д�� */
        knet_stream_push(stream, hello, 12);
    }
}

/* ����� - �ͻ��˻ص� */
void client_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    char buffer[32] = {0};
    /* ��ȡ�Զ˵�ַ */
    kaddress_t* peer_addr = knet_channel_ref_get_peer_address(channel);
    kstream_t* stream = knet_channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        /* ��ȡ */
        knet_stream_pop(stream, buffer, sizeof(buffer));
        /* �ر� */
        knet_channel_ref_close(channel);
        /* �˳�ѭ�� */
        knet_loop_exit(knet_channel_ref_get_loop(channel));
        printf("recv from connector: %s, ip: %s, port: %d\n", buffer,
            address_get_ip(peer_addr), address_get_port(peer_addr));
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
    /* ����ѭ�� */
    kloop_t* loop = knet_loop_create();
    /* �����ͻ��� */
    kchannel_ref_t* connector = knet_loop_create_channel(loop, 8, 1024);
    /* ���������� */
    kchannel_ref_t* acceptor = knet_loop_create_channel(loop, 8, 1024);
    /* ���ûص� */
    knet_channel_ref_set_cb(connector, connector_cb);
    knet_channel_ref_set_cb(acceptor, acceptor_cb);
    /* ���� */
    knet_channel_ref_accept(acceptor, 0, 80, 10);
    /* ���� */
    knet_channel_ref_connect(connector, "127.0.0.1", 80, 5);
    /* ���� */
    knet_loop_run(loop);
    /* ����, connector, acceptor����Ҫ�ֶ����� */
    knet_loop_destroy(loop);
    return 0;
}

#endif /* COMPILE_BASIC_C */
