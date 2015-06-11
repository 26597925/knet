#include "example_config.h"

#if COMPILE_TELNET_ECHO

#include "knet.h"

/*
 telnet����
 */

loop_t* loop = 0;

/* ����� - �ͻ��˻ص� */
void client_cb(channel_ref_t* channel, channel_cb_event_e e) {
    int bytes = 0;
    char buffer[16] = {0};
    stream_t* stream = channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        memset(buffer, 0, sizeof(buffer));
        /* ��ȡ */
        bytes = stream_pop(stream, buffer, sizeof(buffer));
        if (*buffer == 'q') {
            printf("bye...\n");
            loop_exit(loop);
            return;
        }
        printf("recv: %s\n", buffer);
        /* echo */
        stream_push(stream, buffer, bytes);
    }
}

/* �����߻ص� */
void acceptor_cb(channel_ref_t* channel, channel_cb_event_e e) {
    if (e & channel_cb_event_accept) { /* ������ */
        printf("telnet client accepted...\n");
        /* ���ûص� */
        channel_ref_set_cb(channel, client_cb);
    }
}

int main() {
    channel_ref_t* acceptor = 0;
    loop = loop_create();
    acceptor = loop_create_channel(loop, 8, 1024);
    channel_ref_set_cb(acceptor, acceptor_cb);
    channel_ref_accept(acceptor, 0, 23, 10);
    loop_run(loop);
    loop_destroy(loop);
    return 0;
}

#endif /* COMPILE_TELNET_ECHO */
