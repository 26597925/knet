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

#ifndef FRAMEWORK_CONFIG_API_H
#define FRAMEWORK_CONFIG_API_H

/**
 * @defgroup framework_config �������
 * �������
 *
 * <pre>
 * 1. �ṩframework_t�ڽ����ļ����������������ýӿ�
 * 2. ���ù����̵߳������������߳̽�ʵ�ʸ��عܵ�
 * 
 * ������ - ����ǰ����:
 *     framework_acceptor_config_t* ac = framework_config_new_acceptor(c);
 *     framework_acceptor_config_set_local_address(ac, "127.0.0.1", 80);
 *     framework_acceptor_config_set_client_cb(ac, cb);
 *     ......
 *     framework_start(...);
 *     ......
 *
 * ������ - ����ǰ����:
 *     framework_connector_config_t* cc = framework_config_new_connector(c);
 *     framework_connector_config_set_remote_address(cc, "127.0.0.1", 80);
 *     framework_connector_config_set_cb(cc, cb);
 *     ......
 *     framework_start(...);
 *     ......
 *
 * ������ - ��������:
 *     framework_acceptor_config_t* ac = framework_config_new_acceptor(c);
 *     framework_acceptor_config_set_local_address(ac, "127.0.0.1", 80);
 *     framework_acceptor_config_set_client_cb(ac, cb);
 *     framework_acceptor_start(..., ac);
 *
 * ������ - ��������:
 *     framework_connector_config_t* cc = framework_config_new_connector(c);
 *     framework_connector_config_set_remote_address(cc, "127.0.0.1", 80);
 *     framework_connector_config_set_cb(cc, cb);
 *     framework_connector_start(..., cc);
 *
 * </pre>
 * @{
 */

/**
 * ���ù����߳�������Ĭ��Ϊ���߳�
 * @param c framework_config_tʵ��
 * @param worker_thread_count �����߳�����
 */
extern void framework_config_set_worker_thread_count(framework_config_t* c, int worker_thread_count);

/**
 * ��������������
 * @param c framework_config_tʵ��
 * @return framework_acceptor_config_tʵ��
 */
extern framework_acceptor_config_t* framework_config_new_acceptor(framework_config_t* c);

/**
 * ��������������
 * @param c framework_config_tʵ��
 * @return framework_connector_config_tʵ��
 */
extern framework_connector_config_t* framework_config_new_connector(framework_config_t* c);

/**
 * ���ü��������ص�ַ
 * @param c framework_acceptor_config_tʵ��
 * @param ip IP
 * @param port ��ַ
 */
extern void framework_acceptor_config_set_local_address(framework_acceptor_config_t* c, const char* ip, int port);

/**
 * ���ü������ȴ����г���
 * @param c framework_acceptor_config_tʵ��
 * @param backlog �ȴ����г���
 */
extern void framework_acceptor_config_set_backlog(framework_acceptor_config_t* c, int backlog);

/**
 * ���ÿͻ���������ʱ
 * @param c framework_acceptor_config_tʵ��
 * @param timeout �ͻ���������ʱ(��)
 */
extern void framework_acceptor_config_set_client_heartbeat_timeout(framework_acceptor_config_t* c, int timeout);

/**
 * ���ÿͻ��˻ص�����
 * @param c framework_acceptor_config_tʵ��
 * @param cb �ͻ��˻ص�����
 */
extern void framework_acceptor_config_set_client_cb(framework_acceptor_config_t* c, channel_ref_cb_t cb);

/**
 * ���ÿͻ��˷���������󳤶�
 * @param c framework_acceptor_config_tʵ��
 * @param max_send_list_count ����������󳤶�(�ֽ�)
 */
extern void framework_acceptor_config_set_client_max_send_list_count(framework_acceptor_config_t* c, int max_send_list_count);

/**
 * ���ÿͻ��˽��ջ�������󳤶�
 * @param c framework_acceptor_config_tʵ��
 * @param max_recv_buffer_length ���ջ�������󳤶�(�ֽ�)
 */
extern void framework_acceptor_config_set_client_max_recv_buffer_length(framework_acceptor_config_t* c, int max_recv_buffer_length);

/**
 * ������������Ҫ���ӵĵ�ַ
 * @param c framework_connector_config_tʵ��
 * @param ip IP
 * @param port �˿�
 */
extern void framework_connector_config_set_remote_address(framework_connector_config_t* c, const char* ip, int port);

/**
 * ����������������ʱ
 * @param c framework_connector_config_tʵ��
 * @param timeout �ͻ���������ʱ(��)
 */
extern void framework_connector_config_set_heartbeat_timeout(framework_connector_config_t* c, int timeout);

/**
 * �������������ӳ�ʱ
 * @param c framework_connector_config_tʵ��
 * @param timeout ���ӳ�ʱ(��)
 */
extern void framework_connector_config_set_connect_timeout(framework_connector_config_t* c, int timeout);

/**
 * �����������ص�����
 * @param c framework_connector_config_tʵ��
 * @param cb �������ص�����
 */
extern void framework_connector_config_set_cb(framework_connector_config_t* c, channel_ref_cb_t cb);

/**
 * ��������������������󳤶�
 * @param c framework_connector_config_tʵ��
 * @param max_send_list_count ����������󳤶�(�ֽ�)
 */
extern void framework_connector_config_set_client_max_send_list_count(framework_connector_config_t* c, int max_send_list_count);

/**
 * �������������ջ�������󳤶�
 * @param c framework_connector_config_tʵ��
 * @param max_recv_buffer_length ���ջ�������󳤶�(�ֽ�)
 */
extern void framework_connector_config_set_client_max_recv_buffer_length(framework_connector_config_t* c, int max_recv_buffer_length);

/** @} */

#endif /* FRAMEWORK_CONFIG_API_H */
