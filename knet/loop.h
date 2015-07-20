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

#ifndef LOOP_H
#define LOOP_H

#include "config.h"
#include "loop_api.h"

/**
 * ���channel_ref_tʵ������Ծ����
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void loop_add_channel_ref(loop_t* loop, channel_ref_t* channel_ref);

/**
 * �ӵ���Ծ����ɾ��channel_ref_tʵ��
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void loop_remove_channel_ref(loop_t* loop, channel_ref_t* channel_ref);

/**
 * �ӵ���Ծ����ɾ��channel_ref_tʵ����������ر�����
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void loop_close_channel_ref(loop_t* loop, channel_ref_t* channel_ref);

/**
 * ȡ�û�Ծ����
 * @param loop loop_tʵ��
 * @return dlist_tʵ��
 */
dlist_t* loop_get_active_list(loop_t* loop);

/**
 * ȡ�ùر�����
 * @param loop loop_tʵ��
 * @return dlist_tʵ��
 */
dlist_t* loop_get_close_list(loop_t* loop);

/**
 * ����ѡȡ��ʵ��
 * @param loop loop_tʵ��
 * @param impl ѡȡ��ʵ��
 */
void loop_set_impl(loop_t* loop, void* impl);

/**
 * ȡ��ѡȡ��ʵ��
 * @param loop loop_tʵ��
 * @return ѡȡ��ʵ��
 */
void* loop_get_impl(loop_t* loop);

/**
 * ȡ��ѡȡ����ǰ�߳�ID
 * @param loop loop_tʵ��
 * @return �߳�ID
 */
thread_id_t loop_get_thread_id(loop_t* loop);

/**
 * ���ø��ؾ�����(loop_balancer_tʵ����
 * @param loop loop_tʵ��
 * @param balancer loop_balancer_tʵ��
 */
void loop_set_balancer(loop_t* loop, loop_balancer_t* balancer);

/**
 * ȡ�ø��ؾ�����(loop_balancer_tʵ����
 * @param loop loop_tʵ��
 * @return loop_balancer_tʵ��
 */
loop_balancer_t* loop_get_balancer(loop_t* loop);

/**
 * �����¼�֪ͨ - ������������
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void loop_notify_accept(loop_t* loop, channel_ref_t* channel_ref);

/**
 * �������֪ͨ - ��ǰloop�ڼ���
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void loop_notify_accept_async(loop_t* loop, channel_ref_t* channel_ref);

/**
 * �����¼�֪ͨ - ��������
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void loop_notify_connect(loop_t* loop, channel_ref_t* channel_ref);

/**
 * �����¼�֪ͨ - ���̷߳���
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 * @param send_buffer buffer_tʵ��
 */
void loop_notify_send(loop_t* loop, channel_ref_t* channel_ref, buffer_t* send_buffer);

/**
 * �����¼�֪ͨ - �رչܵ�
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void loop_notify_close(loop_t* loop, channel_ref_t* channel_ref);

/**
 * ֪ͨ�ܵ��ص�����
 * @param channel channel_ref_tʵ��
 * @param e �ܵ��¼�
 */
void loop_queue_cb(channel_ref_t* channel, channel_cb_event_e e);

/**
 * �������¼��ص�loop_queue_cb
 * @param loop loop_tʵ��
 */
void loop_notify(loop_t* loop);

/**
 * �����¼�
 * @param loop loop_tʵ��
 */
void loop_event_process(loop_t* loop);

/**
 * ����Ծ�ܵ����г�ʱ
 * @param loop loop_tʵ��
 * @param ts ��ǰʱ������룩
 */
void loop_check_timeout(loop_t* loop, time_t ts);

/**
 * ���رչܵ��Ƿ��������
 * @param loop loop_tʵ��
 */
void loop_check_close(loop_t* loop);

/**
 * ����Ƿ���������
 * @param loop loop_tʵ��
 */
int loop_check_running(loop_t* loop);

/**
 * ���ø��ؾ�������
 * @param loop loop_tʵ��
 * @param options ѡ�loop_balancer_in�� loop_balancer_out��
 */
void loop_set_balance_options(loop_t* loop, loop_balance_option_e options);

/**
 * ȡ�ø��ؾ�������
 * @param loop loop_tʵ��
 * @return ���ؾ�������
 */
loop_balance_option_e loop_get_balance_options(loop_t* loop);

/**
 * ��鸺�ؾ��������Ƿ���
 * @param loop loop_tʵ��
 * @param options ���ؾ�������
 * @retval 0 δ����
 * @retval ���� ����
 */
int loop_check_balance_options(loop_t* loop, loop_balance_option_e options);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ��������ʼ��
 * @param loop loop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */

int impl_create(loop_t* loop);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ֹͣ������
 * @param loop loop_tʵ��
 */
void impl_destroy(loop_t* loop);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ����һ���¼�ѭ��
 * @param loop loop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int impl_run_once(loop_t* loop);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - Ͷ��һ����������¼�
 * @param loop loop_tʵ��
 * @param e �¼�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int impl_event_add(channel_ref_t* channel_ref, channel_event_e e);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ȡ��һ����������¼�
 * @param loop loop_tʵ��
 * @param e �¼�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int impl_event_remove(channel_ref_t* channel_ref, channel_event_e e);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ֪ͨ���µĹܵ������˻�Ծ����
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int impl_add_channel_ref(loop_t* loop, channel_ref_t* channel_ref);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ֪ͨ�ܵ��رղ�����
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int impl_remove_channel_ref(loop_t* loop, channel_ref_t* channel_ref);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - �����ӵ���ʱ���ѡȡ���Զ���ʵ��
 * @param channel_ref channel_ref_tʵ��
 * @return �׽���
 */
socket_t impl_channel_accept(channel_ref_t* channel_ref);

/**
 * ȡ���û�����ָ��
 * @param loop loop_tʵ��
 * @return �û�����ָ��
 */
void* loop_get_data(loop_t* loop);

#endif /* LOOP_H */
