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

#ifndef FRAMEWORK_CONFIG_H
#define FRAMEWORK_CONFIG_H

#include "config.h"
#include "framework_config_api.h"

/**
 * �������������
 * @return framework_config_tʵ��
 */
framework_config_t* framework_config_create();

/**
 * ���ٿ��������
 * @param c framework_config_tʵ��
 */
void framework_config_destroy(framework_config_t* c);

/**
 * ȡ�ù����߳�����
 * @param c framework_config_tʵ��
 * @return �����߳�����
 */
int framework_config_get_worker_thread_count(framework_config_t* c);

/**
 * ȡ�ü�������������
 * @param c framework_config_tʵ��
 * @return ��������������
 */
dlist_t* framework_config_get_acceptor_config(framework_config_t* c);

/**
 * ȡ����������������
 * @param c framework_config_tʵ��
 * @return ��������������
 */
dlist_t* framework_config_get_connector_config(framework_config_t* c);

/**
 * ȡ�ü�����IP
 * @param c framework_acceptor_config_tʵ��
 * @return ������IP
 */
const char* framework_acceptor_config_get_ip(framework_acceptor_config_t* c);

/**
 * ȡ�ü������˿�
 * @param c framework_acceptor_config_tʵ��
 * @return �������˿�
 */
int framework_acceptor_config_get_port(framework_acceptor_config_t* c);

/**
 * ȡ�ü������ȴ����г���
 * @param c framework_acceptor_config_tʵ��
 * @return �������ȴ����г���
 */
int framework_acceptor_config_get_backlog(framework_acceptor_config_t* c);

/**
 * ȡ�ü������ͻ�������(��)
 * @param c framework_acceptor_config_tʵ��
 * @return �ͻ�������(��)
 */
int framework_acceptor_config_get_client_heartbeat_timeout(framework_acceptor_config_t* c);

/**
 * ȡ�ü������ͻ��˻ص�����
 * @param c framework_acceptor_config_tʵ��
 * @return �ͻ��˻ص�����
 */
channel_ref_cb_t framework_acceptor_config_get_client_cb(framework_acceptor_config_t* c);

/**
 * ȡ�ü������ͻ��˷��Ͷ�����󳤶�
 * @param c framework_acceptor_config_tʵ��
 * @return �ͻ��˷��Ͷ�����󳤶�
 */
int framework_acceptor_config_get_client_max_send_list_count(framework_acceptor_config_t* c);

/**
 * ȡ�ü������ͻ��˽��ջ�������󳤶�
 * @param c framework_acceptor_config_tʵ��
 * @return �ͻ��˽��ջ�������󳤶�
 */
int framework_acceptor_config_get_client_max_recv_buffer_length(framework_acceptor_config_t* c);

/**
 * ȡ���������Զ�IP
 * @param c framework_connector_config_tʵ��
 * @return �������Զ�IP
 */
const char* framework_connector_config_get_remote_ip(framework_connector_config_t* c);

/**
 * ȡ���������Զ˶˿�
 * @param c framework_connector_config_tʵ��
 * @return �������Զ˶˿�
 */
int framework_connector_config_get_remote_port(framework_connector_config_t* c);

/**
 * ȡ��������������ʱ(��)
 * @param c framework_connector_config_tʵ��
 * @return ������������ʱ(��)
 */
int framework_connector_config_get_heartbeat_timeout(framework_connector_config_t* c);

/**
 * ȡ�����������ӳ�ʱ(��)
 * @param c framework_connector_config_tʵ��
 * @return ���������ӳ�ʱ(��)
 */
int framework_connector_config_get_connect_timeout(framework_connector_config_t* c);

/**
 * ȡ���������ص�����
 * @param c framework_connector_config_tʵ��
 * @return �������ص�����
 */
channel_ref_cb_t framework_connector_config_get_cb(framework_connector_config_t* c);

/**
 * ȡ������������������󳤶�
 * @param c framework_connector_config_tʵ��
 * @return ����������������󳤶�
 */
int framework_connector_config_get_max_send_list_count(framework_connector_config_t* c);

/**
 * ȡ�����������ջ�������󳤶�
 * @param c framework_connector_config_tʵ��
 * @return ���������ջ�������󳤶�
 */
int framework_connector_config_get_max_recv_buffer_length(framework_connector_config_t* c);

#endif /* FRAMEWORK_CONFIG_H */
