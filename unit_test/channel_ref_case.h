/*
 * Copyright (c) 2014-2015, dennis wang
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 * 
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL dennis wang BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "helper.h"
#include "knet.h"

CASE(Test_Channel_Ref_State) {
    struct holder {
        static void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
            if (e & channel_cb_event_connect) {
                EXPECT_TRUE(channel_ref_check_state(channel, channel_state_active));
                EXPECT_FALSE(channel_ref_check_balance(channel));
                loop_exit(channel_ref_get_loop(channel));
            } else if (e & channel_cb_event_close) {
                EXPECT_TRUE(channel_ref_check_state(channel, channel_state_close));
            }
        }
    };

    loop_t* loop = loop_create();

    channel_ref_t* connector = loop_create_channel(loop, 1, 1024);
    channel_ref_t* acceptor = loop_create_channel(loop, 1, 1024);
    channel_ref_accept(acceptor, 0, 80, 1);
    channel_ref_connect(connector, "127.0.0.1", 80, 1);
    channel_ref_set_cb(connector, &holder::connector_cb);
    EXPECT_TRUE(channel_ref_check_state(connector, channel_state_connect));
    EXPECT_TRUE(channel_ref_check_state(acceptor, channel_state_accept));

    loop_run(loop);
    loop_destroy(loop);
}

CASE(Test_Channel_Ref_Close_Socket_Fd_Outside) {
    struct holder {
        static void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
            if (e & channel_cb_event_connect) {
                #ifdef WIN32
                // �������ķ�ʽ�ر�socket
                closesocket(channel_ref_get_socket_fd(channel));
                #else
                close(channel_ref_get_socket_fd(channel));
                #endif // WIN32
                stream_t* s = channel_ref_get_stream(channel);
                // ��Ϊ�Ѿ�������رգ�����ʧ��
                EXPECT_FALSE(error_ok == stream_push(s, "123", 4));
            } else if (e & channel_cb_event_close) {
                // ��loop_run�ڱ�ǿ�ƹر���
                loop_exit(channel_ref_get_loop(channel));
            }
        }
    };

    loop_t* loop = loop_create();

    channel_ref_t* connector = loop_create_channel(loop, 1, 1024);
    channel_ref_t* acceptor = loop_create_channel(loop, 1, 1024);
    channel_ref_accept(acceptor, 0, 80, 1);
    channel_ref_connect(connector, "127.0.0.1", 80, 1);
    channel_ref_set_cb(connector, &holder::connector_cb);
    EXPECT_TRUE(channel_ref_check_state(connector, channel_state_connect));
    EXPECT_TRUE(channel_ref_check_state(acceptor, channel_state_accept));

    loop_run(loop);
    loop_destroy(loop);
}

CASE(Test_Channel_Ref_Connect_Accept_Twice) {
    loop_t* loop = loop_create();

    channel_ref_t* connector = loop_create_channel(loop, 1, 1024);
    channel_ref_t* acceptor = loop_create_channel(loop, 1, 1024);
    channel_ref_connect(connector, "127.0.0.1", 80, 1);
    EXPECT_FALSE(error_ok == channel_ref_connect(connector, "127.0.0.1", 80, 1));

    channel_ref_accept(acceptor, 0, 80, 1);
    EXPECT_FALSE(error_ok == channel_ref_accept(acceptor, 0, 80, 1));

    loop_destroy(loop);
}

CASE(Test_Channel_Ref_Uuid) {
    loop_t* loop = loop_create();

    channel_ref_t* channel = loop_create_channel(loop, 1, 1024);
    EXPECT_TRUE(channel_ref_get_uuid(channel));

    loop_destroy(loop);
}

CASE(Test_Channel_Connect_Timeout) {
    struct holder {
        static void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
            if (e & channel_cb_event_connect_timeout) {
                loop_exit(channel_ref_get_loop(channel));
            } else if (e & channel_cb_event_close) {                
            } else {
                CASE_FAIL();
            }
        }
    };

    loop_t* loop = loop_create();

    channel_ref_t* connector = loop_create_channel(loop, 1, 1024);
    channel_ref_set_cb(connector, &holder::connector_cb);
    channel_ref_connect(connector, "127.0.0.1", 80, 1);

    loop_run(loop);
    loop_destroy(loop);
}

CASE(Test_Channel_Idle_Timeout) {
    struct holder {
        static void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
            if (e & channel_cb_event_timeout) {
                loop_exit(channel_ref_get_loop(channel));
            } else if (e & channel_cb_event_close) {                
            } else {
                CASE_FAIL();
            }
        }
    };

    loop_t* loop = loop_create();

    channel_ref_t* connector = loop_create_channel(loop, 1, 1024);
    channel_ref_set_cb(connector, &holder::connector_cb);
    channel_ref_set_timeout(connector, 1); /* ���ö���ʱ */
    channel_ref_connect(connector, "127.0.0.1", 80, 0);

    loop_run(loop);
    loop_destroy(loop);
}

// C++���������ྲ̬��Ա����������⣬ֻ�з�������
channel_ref_t* case_Test_Channel_Share_Leave_channel = 0;

CASE(Test_Channel_Share_Leave) {
    // ��ʵ�����Թ����Ƿ�ﵽҪ��ͨ��channel_ref_share/channel_ref_leave
    // �ڶ��̻߳�����ʹ�ã���ֻ��һ���̵߳������Ҳ�������ڹܵ����ñ��ദʹ�õ��ֲ���ͳһ����
    // �ܵ��������ڵ����

    struct holder {
        static void connector_cb(channel_ref_t* channel, channel_cb_event_e e) {
            if (e & channel_cb_event_connect) {
                // ����һ��������
                case_Test_Channel_Share_Leave_channel = channel_ref_share(channel);
                // �رչܵ�
                channel_ref_close(channel);
            } else if (e & channel_cb_event_close) {
                // �յ��ر��¼�, ������Ϊ�ж�һ�����ã��ܵ����ܱ�����
                // ������������
                channel_ref_leave(case_Test_Channel_Share_Leave_channel);
                loop_exit(channel_ref_get_loop(channel));
                // loop_exit���ú�ܵ���״̬���ջ��ǻᱻɨ��һ��
                // ���ɨ���йܵ���������
            }
        }
    };

    loop_t* loop = loop_create();
    channel_ref_t* connector = loop_create_channel(loop, 1, 1024);
    channel_ref_t* acceptor = loop_create_channel(loop, 1, 1024);
    channel_ref_accept(acceptor, 0, 80, 1);
    channel_ref_connect(connector, "127.0.0.1", 80, 1);
    channel_ref_set_cb(connector, &holder::connector_cb);
    EXPECT_TRUE(channel_ref_check_state(connector, channel_state_connect));
    EXPECT_TRUE(channel_ref_check_state(acceptor, channel_state_accept));

    loop_run(loop);

    // 4���ܵ��ֱ�Ϊ��
    // 1. loop�¼����ܵ�
    // 2. loop�¼�д�ܵ�
    // 3. acceptor�ܵ�
    // 4. �½���������
    // connector�ܵ��Ѿ�������
    // ��Ϊ��connector_cb�ڵ�����loop_exit(), �½����������п��ܻ�δ���ر�
    EXPECT_TRUE(3 <= loop_get_active_channel_count(loop));

    // ����Ƿ���δ���ٵĹܵ�
    EXPECT_TRUE(0 == loop_get_close_channel_count(loop));

    // ʣ���4���ܵ������ﱻ����
    loop_destroy(loop);
}
