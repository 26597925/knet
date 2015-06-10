#include "example_config.h"

#if COMPILE_BROADCAST

#include "knet.h"

#define MAX_CONNECTOR 10
broadcast_t* broadcast = 0;
int current_count = 0;
int connector_count = MAX_CONNECTOR;

/* ����� - �ͻ��˻ص� */
void client_cb(channel_ref_t* channel, channel_cb_event_e e) {
    if (e & channel_cb_event_close) {
        connector_count--;
        if (connector_count == 0) {
            printf("all client closed\n");
            loop_exit(channel_ref_get_loop(channel));
        }
    }
}

void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {    
    int bytes = 0;
    char buffer[16] = {0};
    stream_t* stream = channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        memset(buffer, 0, sizeof(buffer));
        /* ��ȡ */
        bytes = stream_pop(stream, buffer, sizeof(buffer));
        printf("recv: %s\n", buffer);
        channel_ref_close(channel);
    }
}

/* �����߻ص� */
void acceptor_cb(channel_ref_t* channel, channel_cb_event_e e) {
    if (e & channel_cb_event_accept) { /* ������ */
        /* ���ûص� */
        channel_ref_set_cb(channel, client_cb);
        current_count++;
        /* ���뵽�㲥�� */
        broadcast_join(broadcast, channel);
        if (current_count == MAX_CONNECTOR) {
            /* ȫ��������ɣ��㲥 */
            broadcast_write(broadcast, "hello world", 12);
        }
    }
}

int main() {
    int i = 0;
    loop_t* loop = loop_create();
    channel_ref_t* acceptor = 0;
    channel_ref_t* connector = 0;
    acceptor = loop_create_channel(loop, 8, 1024);
    channel_ref_accept(acceptor, 0, 8000, 50);
    channel_ref_set_cb(acceptor, acceptor_cb);
    broadcast = broadcast_create();
    for (; i < MAX_CONNECTOR; i++) {
        connector = loop_create_channel(loop, 8, 1024);
        channel_ref_set_cb(connector, connector_cb);
        channel_ref_connect(connector, "127.0.0.1", 8000, 0);
    }

    loop_run(loop);
    broadcast_destroy(broadcast);
    loop_destroy(loop);

    return 0;
}

#endif /* COMPILE_BROADCAST */
