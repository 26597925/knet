#include "example_config.h"

#if COMPILE_FRAMEWORK_C

#include "knet.h"

kframework_t* f = 0;

/* ����� - �ͻ��˻ص� */
void client_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    int bytes = 0;
    char buffer[16] = {0};
    kstream_t* stream = knet_channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        bytes = knet_stream_available(stream);
        memset(buffer, 0, sizeof(buffer));
        /* ��ȡ */
        knet_stream_pop(stream, buffer, sizeof(buffer));
        if (*buffer == 'q') {
            printf("bye...\n");
            knet_framework_stop(f);
            return;
        }
        printf("recv: %s\n", buffer);
        /* echo */
        knet_stream_push(stream, buffer, bytes);
    }
}

int main() {
    kframework_config_t* c = 0;
    kframework_acceptor_config_t* ac = 0;
    f = knet_framework_create();
    c = knet_framework_get_config(f);
    ac = knet_framework_config_new_acceptor(c);
    knet_framework_acceptor_config_set_local_address(ac, 0, 23);
    knet_framework_acceptor_config_set_client_cb(ac, client_cb);
    /* �������, �ȴ��رգ�����*/
    knet_framework_start_wait_destroy(f);
    return 0;
}

#endif /* COMPILE_FRAMEWORK_C */