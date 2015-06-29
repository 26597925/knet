#include <iostream>
#include <sstream>
#include "rpc_sample.h"

using namespace rpc_sample;

namespace rpc_sample {

int my_rpc_func1(my_object_t& my_obj) {
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    std::cout << "invoke my_rpc_func1!" << std::endl;
    std::stringstream ss;
    my_obj.print(ss);
    std::cout << ss.str();
    return rpc_ok;
}

int my_rpc_func2(std::vector<my_object_t>& my_objs, int8_t my_i8) {
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    std::cout << "invoke my_rpc_func2!" << std::endl;
    std::vector<my_object_t>::iterator guard = my_objs.begin();
    for (; guard != my_objs.end(); guard++) {
        std::stringstream ss;
        guard->print(ss, "");
        std::cout << ss.str();
    }
    std::cout << "my_i8=" << (int)my_i8 << std::endl;
    return rpc_ok;
}

int my_rpc_func3(const std::string& my_str, int8_t my_i8) {
    std::cout << ">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>" << std::endl;
    std::cout << "invoke my_rpc_func3!" << std::endl;
    std::cout << "my_str=" << my_str << std::endl;
    std::cout << "my_i8=" << (int)my_i8 << std::endl;
    return rpc_ok;
}

}

/* �ͻ��� - �������ص� */
void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
    stream_t* stream = channel_ref_get_stream(channel);
    if (e & channel_cb_event_connect) { /* ���ӳɹ� */
        /* ����RPC���� */
        my_object_t my_obj;
        my_obj.ni8 = 1;
        my_obj.ni16 = 2;
        my_obj.ni32 = 3;
        my_obj.ni64 = 4;
        my_obj.nui8 = 5;
        my_obj.nui16 = 6;
        my_obj.nui32 = 7;
        my_obj.nui64 = 8;
        my_obj.nf32 = 9.0f;
        my_obj.nf64 = 10.0f;
        my_obj.str = "hello world!";
        rpc_sample_ptr()->my_rpc_func1(stream, my_obj);
        std::vector<my_object_t> objs;
        objs.push_back(my_obj);
        objs.push_back(my_obj);
        rpc_sample_ptr()->my_rpc_func2(stream, objs, 16);
        rpc_sample_ptr()->my_rpc_func3(stream, "hello world!", 16);
    }
}

/* ����� - �ͻ��˻ص� */
void client_cb(channel_ref_t* channel, channel_cb_event_e e) {
    static int i = 0;
    stream_t* stream = channel_ref_get_stream(channel);
    if (e & channel_cb_event_recv) { /* �����ݿ��Զ� */
        for (;;) {
            int error = rpc_sample_ptr()->rpc_proc(stream);
            if (error == error_ok) {
                if (++i >= 3) {
                    loop_exit(channel_ref_get_loop(channel));
                    break;
                }
            } else {
                break;
            }
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
