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

#ifndef LOOP_PROFILE_H
#define LOOP_PROFILE_H

#include "config.h"
#include "loop_profile_api.h"

/**
 * ����kloop_tͳ����
 * @param loop kloop_tʵ��
 * @return kloop_profile_tʵ��
 */
kloop_profile_t* knet_loop_profile_create(kloop_t* loop);

/**
 * ����ͳ����
 * @param profile kloop_profile_tʵ��
 */
void knet_loop_profile_destroy(kloop_profile_t* profile);

/**
 * �����ѽ������ӵĹܵ�����
 * @param profile kloop_profile_tʵ��
 * @return �ѽ������ӵĹܵ�����
 */
uint32_t knet_loop_profile_increase_established_channel_count(kloop_profile_t* profile);

/**
 * �����ѽ������ӵĹܵ�����
 * @param profile kloop_profile_tʵ��
 * @return �ѽ������ӵĹܵ�����
 */
uint32_t knet_loop_profile_decrease_established_channel_count(kloop_profile_t* profile);

/**
 * �����ѽ�����δ���ӵĹܵ�����
 * @param profile kloop_profile_tʵ��
 * @return �ѽ�����δ���ӵĹܵ�����
 */
uint32_t knet_loop_profile_increase_active_channel_count(kloop_profile_t* profile);

/**
 * �����ѽ�����δ���ӵĹܵ�����
 * @param profile kloop_profile_tʵ��
 * @return �ѽ�����δ���ӵĹܵ�����
 */
uint32_t knet_loop_profile_decrease_active_channel_count(kloop_profile_t* profile);

/**
 * �����ѹرչܵ�����
 * @param profile kloop_profile_tʵ��
 * @return �ѹرչܵ�����
 */
uint32_t knet_loop_profile_increase_close_channel_count(kloop_profile_t* profile);

/**
 * �����ѹرչܵ�����
 * @param profile kloop_profile_tʵ��
 * @return �ѹرչܵ�����
 */
uint32_t knet_loop_profile_decrease_close_channel_count(kloop_profile_t* profile);

/**
 * ���ӷ����ֽ���
 * @param profile kloop_profile_tʵ��
 * @param send_bytes �ѷ��͵��ֽ���
 * @return �����ֽ���
 */
uint64_t knet_loop_profile_add_send_bytes(kloop_profile_t* profile, uint64_t send_bytes);

/**
 * ���ӽ����ֽ���
 * @param profile kloop_profile_tʵ��
 * @param recv_bytes �ѽ��յ��ֽ���
 * @return �����ֽ���
 */
uint64_t knet_loop_profile_add_recv_bytes(kloop_profile_t* profile, uint64_t recv_bytes);

#endif /* LOOP_PROFILE_H */
