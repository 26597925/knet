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

#ifndef LOOP_PROFILE_API_H
#define LOOP_PROFILE_API_H

#include "config.h"

/**
 * ȡ���Ѿ��������ӵĹܵ�����
 * @param profile kloop_profile_tʵ��
 * @return �������ӵĹܵ�����
 */
extern uint32_t knet_loop_profile_get_established_channel_count(kloop_profile_t* profile);

/**
 * ȡ���Ѿ���������δ���ӵĹܵ�����
 * @param profile kloop_profile_tʵ��
 * @return ��������δ���ӵĹܵ�����
 */
extern uint32_t knet_loop_profile_get_active_channel_count(kloop_profile_t* profile);

/**
 * ȡ���Ѿ��رյĹܵ�����
 * @param profile kloop_profile_tʵ��
 * @return �Ѿ��رյĹܵ�����
 */
extern uint32_t knet_loop_profile_get_close_channel_count(kloop_profile_t* profile);

/**
 * ȡ���Ѿ����͵��ֽ���
 * @param profile kloop_profile_tʵ��
 * @return �Ѿ����͵��ֽ���
 */
extern uint64_t knet_loop_profile_get_sent_bytes(kloop_profile_t* profile);

/**
 * ȡ���Ѿ����յ��ֽ���
 * @param profile kloop_profile_tʵ��
 * @return �Ѿ����յ��ֽ���
 */
extern uint64_t knet_loop_profile_get_recv_bytes(kloop_profile_t* profile);

/**
 * ȡ�÷��ʹ���
 * @param profile kloop_profile_tʵ��
 * @return ����(�ֽ�/��)
 */
extern uint32_t knet_loop_profile_get_sent_bandwidth(kloop_profile_t* profile);

/**
 * ȡ�ý��մ���
 * @param profile kloop_profile_tʵ��
 * @return ����(�ֽ�/��)
 */
extern uint32_t knet_loop_profile_get_recv_bandwidth(kloop_profile_t* profile);

/**
 * ��ͳ����Ϣд���ļ�
 * @param profile kloop_profile_tʵ��
 * @param fp FILEָ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_loop_profile_dump_file(kloop_profile_t* profile, FILE* fp);

/**
 * ��ͳ����Ϣд��ܵ���
 * @param profile kloop_profile_tʵ��
 * @param stream kstream_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_loop_profile_dump_stream(kloop_profile_t* profile, kstream_t* stream);

/**
 * ��ͳ����Ϣ��ӡ����׼���
 * @param profile kloop_profile_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_loop_profile_dump_stdout(kloop_profile_t* profile);

#endif /* LOOP_PROFILE_API_H */
