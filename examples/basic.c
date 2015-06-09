#include "example_config.h"

#if COMPILE_BASIC_C

#include "knet.h"

/* �ͻ��� - �������ص� */
void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
    char* hello = "hello world";
    stream_t* stream = channel_ref_get_stream(channel);
    if (e & channel_cb_event_connect) { /* ���ӳɹ� */
        /* д�� */
        stream_push(stream, hello, 12);
    }
}

/* ����� - �ͻ��˻ص� */
void client_cb(channel_ref_t* channel, channel_cb_event_e e) {
    char buffer[32] = {0};
    /* ��ȡ�Զ˵�ַ */
    address_t* peer_addr = channel_ref_get_peer_address(channel);
    stream_t* stream = channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        /* ��ȡ */
        stream_pop(stream, buffer, sizeof(buffer));
        /* �ر� */
        channel_ref_close(channel);
        /* �˳�ѭ�� */
        loop_exit(channel_ref_get_loop(channel));
        printf("recv from connector: %s, ip: %s, port: %d\n", buffer,
            address_get_ip(peer_addr), address_get_port(peer_addr));
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
    /* ����ѭ�� */
    loop_t* loop = loop_create();
    /* �����ͻ��� */
    channel_ref_t* connector = loop_create_channel(loop, 8, 1024);
    /* ���������� */
    channel_ref_t* acceptor = loop_create_channel(loop, 8, 1024);
    /* ���ûص� */
    channel_ref_set_cb(connector, connector_cb);
    channel_ref_set_cb(acceptor, acceptor_cb);
    /* ���� */
    channel_ref_accept(acceptor, 0, 80, 10);
    /* ���� */
    channel_ref_connect(connector, "127.0.0.1", 80, 5);
    /* ���� */
    loop_run(loop);
    /* ����, connector, acceptor����Ҫ�ֶ����� */
    loop_destroy(loop);
    return 0;
}

#endif /* COMPILE_BASIC_C */
