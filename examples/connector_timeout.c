#include "example_config.h"

#if COMPILE_CONNECTOR_TIMEOUT

#include "knet.h"

/* �ͻ��� - �������ص� */
void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
    if (e & channel_cb_event_connect_timeout) { /* ���ӳɹ� */
        channel_ref_close(channel);
        /* ���ӳ�ʱ���˳�ѭ�� */
        loop_exit(channel_ref_get_loop(channel));
    } else if (e & channel_cb_event_close) {
        /* ���������˳�ѭ�� */
        printf("connect failed!\n");
        loop_exit(channel_ref_get_loop(channel));
    }
}

int main() {
    /* ����ѭ�� */
    loop_t* loop = loop_create();
    /* �����ͻ��� */
    channel_ref_t* connector = loop_create_channel(loop, 8, 1024);
    /* ���ûص� */
    channel_ref_set_cb(connector, connector_cb);
    /* ���� */
    if (error_ok != channel_ref_connect(connector, "127.0.0.1", 8000, 2)) {
        printf("remote unreachable\n");
    } else {
        /* ���� */
        loop_run(loop);
    }
    /* ����, connector, acceptor����Ҫ�ֶ����� */
    loop_destroy(loop);
    return 0;
}

#endif /* COMPILE_CONNECTOR_TIMEOUT */
