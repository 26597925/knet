#include "example_config.h"

#if COMPILE_CONNECTOR_TIMEOUT

#include "knet.h"

/* �ͻ��� - �������ص� */
void connector_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    if (e & channel_cb_event_connect_timeout) { /* ���ӳɹ� */
        knet_channel_ref_close(channel);
        /* ���ӳ�ʱ���˳�ѭ�� */
        knet_loop_exit(knet_channel_ref_get_loop(channel));
    } else if (e & channel_cb_event_close) {
        /* ���������˳�ѭ�� */
        printf("connect failed!\n");
        knet_loop_exit(knet_channel_ref_get_loop(channel));
    }
}

int main() {
    /* ����ѭ�� */
    kloop_t* loop = knet_loop_create();
    /* �����ͻ��� */
    kchannel_ref_t* connector = knet_loop_create_channel(loop, 8, 1024);
    /* ���ûص� */
    knet_channel_ref_set_cb(connector, connector_cb);
    /* ���� */
    if (error_ok != knet_channel_ref_connect(connector, "127.0.0.1", 8000, 2)) {
        printf("remote unreachable\n");
    } else {
        /* ���� */
        knet_loop_run(loop);
    }
    /* ����, connector, acceptor����Ҫ�ֶ����� */
    knet_loop_destroy(loop);
    return 0;
}

#endif /* COMPILE_CONNECTOR_TIMEOUT */
