#include "example_config.h"

#if COMPILE_RPC

#include "knet.h"

krpc_t* rpc = 0;

int rpc_cb(krpc_object_t* o) {
    printf("call rpc_cb, param count %d\n", krpc_vector_get_size(o));
    return rpc_ok;
}

/* �ͻ��� - �������ص� */
void connector_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    int i = 0;
    krpc_object_t* o = 0;
    krpc_object_t* v = 0;
    char* hello = "hello world";
    kstream_t* stream = knet_channel_ref_get_stream(channel);
    if (e & channel_cb_event_connect) { /* ���ӳɹ� */
        /* д�� */
        v = krpc_object_create();
        for (i = 0; i < 10; i++) {
            o = krpc_object_create();
            krpc_string_set_s(o, hello, 12);
            krpc_vector_push_back(v, o);
        }
        o = krpc_object_create();
        krpc_number_set_i64(o, 9238948959);
        krpc_vector_push_back(v, o);
        krpc_call(rpc, stream, 1, v);
        /* �����ڶ���Ҳ�ᱻ���� */
        krpc_object_destroy(v);
    }
}

/* ����� - �ͻ��˻ص� */
void client_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e) {
    char buffer[32] = {0};
    /* ��ȡ�Զ˵�ַ */
    kaddress_t* peer_addr = knet_channel_ref_get_peer_address(channel);
    kstream_t* stream = knet_channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        if (error_ok == krpc_proc(rpc, stream)) {
            /* �˳�ѭ�� */
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
    /* ����ѭ�� */
    kloop_t* loop = knet_loop_create();
    /* �����ͻ��� */
    kchannel_ref_t* connector = knet_loop_create_channel(loop, 8, 1024);
    /* ���������� */
    kchannel_ref_t* acceptor = knet_loop_create_channel(loop, 8, 1024);
    rpc = krpc_create();
    /* ����RPC�ص� */
    krpc_add_cb(rpc, 1, rpc_cb);
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
    krpc_destroy(rpc);
    return 0;
}

#endif /* COMPILE_RPC */
