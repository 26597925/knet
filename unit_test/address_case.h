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

CASE(Test_Address) {
    loop_t* loop = loop_create();

    channel_ref_t* channel = loop_create_channel(loop, 0, 1024);
    address_t* peer = channel_ref_get_peer_address(channel);
    address_t* local = channel_ref_get_local_address(channel);
    // δ��������
    EXPECT_TRUE(std::string("0.0.0.0") == address_get_ip(peer));
    EXPECT_FALSE(address_get_port(peer));
    EXPECT_TRUE_OUTPUT(std::string("0.0.0.0") == address_get_ip(local), address_get_ip(local));
    EXPECT_FALSE(address_get_port(local));

    channel_ref_close(channel); /* δ���������ӣ���Ҫ�ֶ����� */

    channel_ref_t* connector = loop_create_channel(loop, 1, 1024);
    channel_ref_t* acceptor = loop_create_channel(loop, 1, 1024);
    channel_ref_accept(acceptor, 0, 80, 1);
    channel_ref_connect(connector, "127.0.0.1", 80, 1);
    loop_run_once(loop);

    peer = channel_ref_get_peer_address(connector);
    local = channel_ref_get_local_address(connector);
    EXPECT_TRUE(std::string("0.0.0.0") != address_get_ip(peer));
    EXPECT_TRUE(80 == address_get_port(peer));
    EXPECT_TRUE(std::string("0.0.0.0") != address_get_ip(local));
    EXPECT_TRUE(0 != address_get_port(local));

    loop_destroy(loop);
}
