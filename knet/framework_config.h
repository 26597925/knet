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
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FRAMEWORK_CONFIG_H
#define FRAMEWORK_CONFIG_H

#include "config.h"
#include "framework_config_api.h"

/**
 * �������������
 * @return kframework_config_tʵ��
 */
kframework_config_t* framework_config_create();

/**
 * ���ٿ��������
 * @param c kframework_config_tʵ��
 */
void framework_config_destroy(kframework_config_t* c);

/**
 * ȡ�ù����߳�����
 * @param c kframework_config_tʵ��
 * @return �����߳�����
 */
int framework_config_get_worker_thread_count(kframework_config_t* c);

/**
 * ȡ�ù����߳��ڶ�ʱ���ֱ���
 * @param c kframework_config_tʵ��
 * @return �����߳��ڶ�ʱ���ֱ��ʣ����룩
 */
time_t framework_config_get_worker_timer_freq(kframework_config_t* c);

/**
 * ȡ�ù����߳��ڶ�ʱ����λ����
 * @param c kframework_config_tʵ��
 * @return ��ʱ����λ����
 */
int framework_config_get_worker_timer_slot(kframework_config_t* c);

/**
 * ȡ�ü�������������
 * @param c kframework_config_tʵ��
 * @return ��������������
 */
kdlist_t* framework_config_get_acceptor_config(kframework_config_t* c);

/**
 * ȡ����������������
 * @param c kframework_config_tʵ��
 * @return ��������������
 */
kdlist_t* framework_config_get_connector_config(kframework_config_t* c);

/**
 * ȡ�ü�����IP
 * @param c kframework_acceptor_config_tʵ��
 * @return ������IP
 */
const char* framework_acceptor_config_get_ip(kframework_acceptor_config_t* c);

/**
 * ȡ�ü������˿�
 * @param c kframework_acceptor_config_tʵ��
 * @return �������˿�
 */
int framework_acceptor_config_get_port(kframework_acceptor_config_t* c);

/**
 * ȡ�ü������ȴ����г���
 * @param c kframework_acceptor_config_tʵ��
 * @return �������ȴ����г���
 */
int framework_acceptor_config_get_backlog(kframework_acceptor_config_t* c);

/**
 * ȡ�ü������ͻ�������(��)
 * @param c kframework_acceptor_config_tʵ��
 * @return �ͻ�������(��)
 */
int framework_acceptor_config_get_client_heartbeat_timeout(kframework_acceptor_config_t* c);

/**
 * ȡ�ü������ͻ��˻ص�����
 * @param c kframework_acceptor_config_tʵ��
 * @return �ͻ��˻ص�����
 */
knet_channel_ref_cb_t framework_acceptor_config_get_client_cb(kframework_acceptor_config_t* c);

/**
 * ȡ�ü������ͻ��˷��Ͷ�����󳤶�
 * @param c kframework_acceptor_config_tʵ��
 * @return �ͻ��˷��Ͷ�����󳤶�
 */
int framework_acceptor_config_get_client_max_send_list_count(kframework_acceptor_config_t* c);

/**
 * ȡ�ü������ͻ��˽��ջ�������󳤶�
 * @param c kframework_acceptor_config_tʵ��
 * @return �ͻ��˽��ջ�������󳤶�
 */
int framework_acceptor_config_get_client_max_recv_buffer_length(kframework_acceptor_config_t* c);

/**
 * ȡ���������Զ�IP
 * @param c kframework_connector_config_tʵ��
 * @return �������Զ�IP
 */
const char* framework_connector_config_get_remote_ip(kframework_connector_config_t* c);

/**
 * ȡ���������Զ˶˿�
 * @param c kframework_connector_config_tʵ��
 * @return �������Զ˶˿�
 */
int framework_connector_config_get_remote_port(kframework_connector_config_t* c);

/**
 * ȡ��������������ʱ(��)
 * @param c kframework_connector_config_tʵ��
 * @return ������������ʱ(��)
 */
int framework_connector_config_get_heartbeat_timeout(kframework_connector_config_t* c);

/**
 * ȡ�����������ӳ�ʱ(��)
 * @param c kframework_connector_config_tʵ��
 * @return ���������ӳ�ʱ(��)
 */
int framework_connector_config_get_connect_timeout(kframework_connector_config_t* c);

/**
 * ȡ���������Զ�������־
 * @param c kframework_connector_config_tʵ��
 * @return �������Զ�������־
 */
int framework_connector_config_get_auto_reconnect(kframework_connector_config_t* c);

/**
 * ȡ���������ص�����
 * @param c kframework_connector_config_tʵ��
 * @return �������ص�����
 */
knet_channel_ref_cb_t framework_connector_config_get_cb(kframework_connector_config_t* c);

/**
 * ȡ������������������󳤶�
 * @param c kframework_connector_config_tʵ��
 * @return ����������������󳤶�
 */
int framework_connector_config_get_max_send_list_count(kframework_connector_config_t* c);

/**
 * ȡ�����������ջ�������󳤶�
 * @param c kframework_connector_config_tʵ��
 * @return ���������ջ�������󳤶�
 */
int framework_connector_config_get_max_recv_buffer_length(kframework_connector_config_t* c);

/**
 * �����û��Զ�������ָ��
 * @param c kframework_acceptor_config_tʵ��
 * @param user_data �û��Զ�������ָ��
 */
void framework_acceptor_config_set_user_data(kframework_acceptor_config_t* c, void* user_data);

/**
 * ȡ���û��Զ�������ָ��
 * @param c kframework_acceptor_config_tʵ��
 * @return �û��Զ�������ָ��
 */
void* framework_acceptor_config_get_user_data(kframework_acceptor_config_t* c);

/**
 * �����û��Զ�������ָ��
 * @param c kframework_connector_config_tʵ��
 * @param user_data �û��Զ�������ָ��
 */
void framework_connector_config_set_user_data(kframework_connector_config_t* c, void* user_data);

/**
 * �����û��Զ�������ָ��
 * @param c kframework_connector_config_tʵ��
 * @return �û��Զ�������ָ��
 */
void* framework_connector_config_get_user_data(kframework_connector_config_t* c);

#endif /* FRAMEWORK_CONFIG_H */
