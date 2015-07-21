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
 * ���kchannel_ref_tʵ������Ծ����
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 */
void knet_loop_add_channel_ref(kloop_t* loop, kchannel_ref_t* channel_ref);

/**
 * �ӵ���Ծ����ɾ��kchannel_ref_tʵ��
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 */
void knet_loop_remove_channel_ref(kloop_t* loop, kchannel_ref_t* channel_ref);

/**
 * �ӵ���Ծ����ɾ��kchannel_ref_tʵ����������ر�����
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 */
void knet_loop_close_channel_ref(kloop_t* loop, kchannel_ref_t* channel_ref);

/**
 * ȡ�û�Ծ����
 * @param loop kloop_tʵ��
 * @return kdlist_tʵ��
 */
kdlist_t* knet_loop_get_active_list(kloop_t* loop);

/**
 * ȡ�ùر�����
 * @param loop kloop_tʵ��
 * @return kdlist_tʵ��
 */
kdlist_t* knet_loop_get_close_list(kloop_t* loop);

/**
 * ����ѡȡ��ʵ��
 * @param loop kloop_tʵ��
 * @param impl ѡȡ��ʵ��
 */
void knet_loop_set_impl(kloop_t* loop, void* impl);

/**
 * ȡ��ѡȡ��ʵ��
 * @param loop kloop_tʵ��
 * @return ѡȡ��ʵ��
 */
void* knet_loop_get_impl(kloop_t* loop);

/**
 * ȡ��ѡȡ����ǰ�߳�ID
 * @param loop kloop_tʵ��
 * @return �߳�ID
 */
thread_id_t knet_loop_get_thread_id(kloop_t* loop);

/**
 * ���ø��ؾ�����(kloop_balancer_tʵ����
 * @param loop kloop_tʵ��
 * @param balancer kloop_balancer_tʵ��
 */
void knet_loop_set_balancer(kloop_t* loop, kloop_balancer_t* balancer);

/**
 * ȡ�ø��ؾ�����(kloop_balancer_tʵ����
 * @param loop kloop_tʵ��
 * @return kloop_balancer_tʵ��
 */
kloop_balancer_t* knet_loop_get_balancer(kloop_t* loop);

/**
 * �����¼�֪ͨ - ������������
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 */
void knet_loop_notify_accept(kloop_t* loop, kchannel_ref_t* channel_ref);

/**
 * �������֪ͨ - ��ǰloop�ڼ���
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 */
void knet_loop_notify_accept_async(kloop_t* loop, kchannel_ref_t* channel_ref);

/**
 * �����¼�֪ͨ - ��������
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 */
void knet_loop_notify_connect(kloop_t* loop, kchannel_ref_t* channel_ref);

/**
 * �����¼�֪ͨ - ���̷߳���
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 * @param send_buffer kbuffer_tʵ��
 */
void knet_loop_notify_send(kloop_t* loop, kchannel_ref_t* channel_ref, kbuffer_t* send_buffer);

/**
 * �����¼�֪ͨ - �رչܵ�
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 */
void knet_loop_notify_close(kloop_t* loop, kchannel_ref_t* channel_ref);

/**
 * ֪ͨ�ܵ��ص�����
 * @param channel kchannel_ref_tʵ��
 * @param e �ܵ��¼�
 */
void knet_loop_queue_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e);

/**
 * �������¼��ص�knet_loop_queue_cb
 * @param loop kloop_tʵ��
 */
void knet_loop_notify(kloop_t* loop);

/**
 * �����¼�
 * @param loop kloop_tʵ��
 */
void knet_loop_event_process(kloop_t* loop);

/**
 * ����Ծ�ܵ����г�ʱ
 * @param loop kloop_tʵ��
 * @param ts ��ǰʱ������룩
 */
void knet_loop_check_timeout(kloop_t* loop, time_t ts);

/**
 * ���رչܵ��Ƿ��������
 * @param loop kloop_tʵ��
 */
void knet_loop_check_close(kloop_t* loop);

/**
 * ����Ƿ���������
 * @param loop kloop_tʵ��
 */
int knet_loop_check_running(kloop_t* loop);

/**
 * ���ø��ؾ�������
 * @param loop kloop_tʵ��
 * @param options ѡ�loop_balancer_in�� loop_balancer_out��
 */
void knet_loop_set_balance_options(kloop_t* loop, knet_loop_balance_option_e options);

/**
 * ȡ�ø��ؾ�������
 * @param loop kloop_tʵ��
 * @return ���ؾ�������
 */
knet_loop_balance_option_e knet_loop_get_balance_options(kloop_t* loop);

/**
 * ��鸺�ؾ��������Ƿ���
 * @param loop kloop_tʵ��
 * @param options ���ؾ�������
 * @retval 0 δ����
 * @retval ���� ����
 */
int knet_loop_check_balance_options(kloop_t* loop, knet_loop_balance_option_e options);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ��������ʼ��
 * @param loop kloop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */

int knet_impl_create(kloop_t* loop);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ֹͣ������
 * @param loop kloop_tʵ��
 */
void knet_impl_destroy(kloop_t* loop);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ����һ���¼�ѭ��
 * @param loop kloop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int knet_impl_run_once(kloop_t* loop);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - Ͷ��һ����������¼�
 * @param loop kloop_tʵ��
 * @param e �¼�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int knet_impl_event_add(kchannel_ref_t* channel_ref, knet_channel_event_e e);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ȡ��һ����������¼�
 * @param loop kloop_tʵ��
 * @param e �¼�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int knet_impl_event_remove(kchannel_ref_t* channel_ref, knet_channel_event_e e);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ֪ͨ���µĹܵ������˻�Ծ����
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int knet_impl_add_channel_ref(kloop_t* loop, kchannel_ref_t* channel_ref);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - ֪ͨ�ܵ��رղ�����
 * @param loop kloop_tʵ��
 * @param channel_ref kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int knet_impl_remove_channel_ref(kloop_t* loop, kchannel_ref_t* channel_ref);

/* 
 * ѡȡ����Ҫʵ�ֵĺ��� - �����ӵ���ʱ���ѡȡ���Զ���ʵ��
 * @param channel_ref kchannel_ref_tʵ��
 * @return �׽���
 */
socket_t knet_impl_channel_accept(kchannel_ref_t* channel_ref);

/**
 * ȡ���û�����ָ��
 * @param loop kloop_tʵ��
 * @return �û�����ָ��
 */
void* knet_loop_get_data(kloop_t* loop);

#endif /* LOOP_H */
