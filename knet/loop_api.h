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

#ifndef LOOP_API_H
#define LOOP_API_H

#include "config.h"

/**
 * @defgroup loop �¼�ѭ��
 * �����¼�ѭ��
 *
 * <pre>
 * �����¼�API����Ϊ������ͬ����ϵͳ����ѡȡ���İ�װ�������˲�ͬƽ̨�ľ���ʵ�֣�
 * Ϊ���ṩͳһ�ĵ��ýӿ�.
 *
 * �ܵ�����channel_ref_tͨ������loop_create_channel��loop_create_channel_exist_socket_fd
 * ������loop_run�������¼�ѭ�����ȴ�����loop_exit�˳���������ֶ�����loop_run_once����һ���¼�
 * ѭ���Լ�����ѭ���ĵ���Ƶ��.
 *
 * ÿ��loop_t�ڶ�ά���˻�Ծ�ܵ����ѹر�(δ����)�ܵ���˫����������ͨ��loop_get_active_channel_count
 * ��loop_get_close_channel_count��ȡ�þ�������.
 *
 * �ڴ����ܵ�ʱ��Ҫע��������Ҫ�����ò�����
 *
 * 1. max_send_list_len �����������Ԫ�ظ���
 * 2. recv_ring_len     ���ܻ�������󳤶�
 *
 * ͨ����ܵ��ڷ�������(stream_push_ϵ��)���ܵ��᳢��ֱ�ӷ��ͣ���������Ҫ���͵����ݣ������Ϊĳ��ԭ��
 * ���²���ֱ�ӷ��ͣ����ݻᱻ�����ڷ��������ڵȴ����ʵ�ʱ�����ͣ������������ĳ��ȴﵽ���ޣ��ܵ��ᱻ�ر�.
 * ͬ�������ܻ���������׽����ڽ����ݶ�ȡ�����������һֱ����stream_t��ȡ���ݣ���ô����ᱻд�����ܵ�Ҳ
 * �ᱻ�ر�.
 *
 * </pre>
 * @{
 */

/**
 * ����һ���¼�ѭ��
 * @return loop_tʵ��
 */
extern loop_t* loop_create();

/**
 * �����¼�ѭ��
 * �¼�ѭ���ڵ����йܵ�Ҳ�ᱻ����
 * @param loop loop_tʵ��
 */
extern void loop_destroy(loop_t* loop);

/**
 * �����ܵ�
 * @param loop loop_tʵ��
 * @param max_send_list_len ���ͻ���������󳤶�
 * @param recv_ring_len ���ܻ��λ�������󳤶�
 * @return channel_ref_tʵ��
 */
extern channel_ref_t* loop_create_channel(loop_t* loop, uint32_t max_send_list_len, uint32_t recv_ring_len);

/**
 * ʹ���Ѵ��ڵ��׽��ִ����ܵ�
 * @param loop loop_tʵ��
 * @param socket_fd �׽���
 * @param max_send_list_len ���ͻ���������󳤶�
 * @param recv_ring_len ���ܻ��λ�������󳤶�
 * @return channel_ref_tʵ��
 */
extern channel_ref_t* loop_create_channel_exist_socket_fd(loop_t* loop, socket_t socket_fd,
    uint32_t max_send_list_len, uint32_t recv_ring_len);

/**
 * ����һ���¼�ѭ��
 * loop_t�����̰߳�ȫ�ģ������ڶ���߳���ͬʱ��ͬһ��loop_tʵ������loop_run_once
 * @param loop loop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int loop_run_once(loop_t* loop);

/**
 * �����¼�ѭ��ֱ������loop_exit()
 * loop_t�����̰߳�ȫ�ģ������ڶ���߳���ͬʱ��ͬһ��loop_tʵ������loop_run
 * @param loop loop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int loop_run(loop_t* loop);

/**
 * �˳�����loop_run()
 * @param loop loop_tʵ��
 */
extern void loop_exit(loop_t* loop);

/**
 * ��ȡ��Ծ�ܵ�����
 * @param loop loop_tʵ��
 * @return ��Ծ�ܵ�����
 */
extern int loop_get_active_channel_count(loop_t* loop);

/**
 * ��ȡ�ѹرչܵ�����
 * @param loop loop_tʵ��
 * @return �رչܵ�����
 */
extern int loop_get_close_channel_count(loop_t* loop);

/**
 * �����û�����ָ��
 * @param loop loop_tʵ��
 * @param data �û�����ָ��
 */
extern void loop_set_data(loop_t* loop, void* data);

/**
 * ȡ��ͳ����
 * @param loop loop_tʵ��
 * @return loop_profile_tʵ��
 */
extern loop_profile_t* loop_get_profile(loop_t* loop);

/** @} */

#endif /* LOOP_API_H */
