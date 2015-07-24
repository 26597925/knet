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

#ifndef FRAMEWORK_CONFIG_API_H
#define FRAMEWORK_CONFIG_API_H

/**
 * @defgroup framework_config �������
 * �������
 *
 * <pre>
 * 1. �ṩkframework_t�ڽ����ļ����������������ýӿ�
 * 2. ���ù����̵߳������������߳̽�ʵ�ʸ��عܵ�
 * 
 * ������ - ����ǰ����:
 *     kframework_acceptor_config_t* ac = knet_framework_config_new_acceptor(c);
 *     knet_framework_acceptor_config_set_local_address(ac, "127.0.0.1", 80);
 *     knet_framework_acceptor_config_set_client_cb(ac, cb);
 *     ......
 *     knet_framework_start(...);
 *     ......
 *
 * ������ - ����ǰ����:
 *     kframework_connector_config_t* cc = knet_framework_config_new_connector(c);
 *     knet_framework_connector_config_set_remote_address(cc, "127.0.0.1", 80);
 *     knet_framework_connector_config_set_cb(cc, cb);
 *     ......
 *     knet_framework_start(...);
 *     ......
 *
 * ������ - ��������:
 *     kframework_acceptor_config_t* ac = knet_framework_config_new_acceptor(c);
 *     knet_framework_acceptor_config_set_local_address(ac, "127.0.0.1", 80);
 *     knet_framework_acceptor_config_set_client_cb(ac, cb);
 *     knet_framework_acceptor_start(..., ac);
 *
 * ������ - ��������:
 *     kframework_connector_config_t* cc = knet_framework_config_new_connector(c);
 *     knet_framework_connector_config_set_remote_address(cc, "127.0.0.1", 80);
 *     knet_framework_connector_config_set_cb(cc, cb);
 *     knet_framework_connector_start(..., cc);
 *
 * </pre>
 * @{
 */

/**
 * ���ļ���������
 * @param c kframework_config_tʵ��
 * @param path �ļ�·��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_framework_config_load_config_file(kframework_config_t* c, const char* path);

/**
 * �������ַ�����������
 * @param c kframework_config_tʵ��
 * @param config_string �����ַ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_framework_config_load_config_string(kframework_config_t* c, const char* config_string);

/**
 * ���ù����߳�������Ĭ��Ϊ���߳�
 * @param c kframework_config_tʵ��
 * @param worker_thread_count �����߳�����
 */
extern void knet_framework_config_set_worker_thread_count(
    kframework_config_t* c, int worker_thread_count);

/**
 * ���ù����߳��ڶ�ʱ���ֱ���
 * @param c kframework_config_tʵ��
 * @param freq �����߳��ڶ�ʱ���ֱ��ʣ����룩
 */
extern void knet_framework_config_set_worker_timer_freq(
    kframework_config_t* c, time_t freq);

/**
 * ���ù����߳��ڶ�ʱ����λ����
 * @param c kframework_config_tʵ��
 * @param slot ��ʱ����λ����
 */
extern void knet_framework_config_set_worker_timer_slot(
    kframework_config_t* c, int slot);

/**
 * ��������������
 * @param c kframework_config_tʵ��
 * @return kframework_acceptor_config_tʵ��
 */
extern kframework_acceptor_config_t* knet_framework_config_new_acceptor(
    kframework_config_t* c);

/**
 * ��������������
 * @param c kframework_config_tʵ��
 * @return kframework_connector_config_tʵ��
 */
extern kframework_connector_config_t* knet_framework_config_new_connector(
    kframework_config_t* c);

/**
 * ���ü��������ص�ַ
 * @param c kframework_acceptor_config_tʵ��
 * @param ip IP
 * @param port ��ַ
 */
extern void knet_framework_acceptor_config_set_local_address(
    kframework_acceptor_config_t* c, const char* ip, int port);

/**
 * ���ü������ȴ����г���
 * @param c kframework_acceptor_config_tʵ��
 * @param backlog �ȴ����г���
 */
extern void knet_framework_acceptor_config_set_backlog(
    kframework_acceptor_config_t* c, int backlog);

/**
 * ���ÿͻ���������ʱ
 * @param c kframework_acceptor_config_tʵ��
 * @param timeout �ͻ���������ʱ(��)
 */
extern void knet_framework_acceptor_config_set_client_heartbeat_timeout(
    kframework_acceptor_config_t* c, int timeout);

/**
 * ���ÿͻ��˻ص�����
 * @param c kframework_acceptor_config_tʵ��
 * @param cb �ͻ��˻ص�����
 */
extern void knet_framework_acceptor_config_set_client_cb(
    kframework_acceptor_config_t* c, knet_channel_ref_cb_t cb);

/**
 * ���ÿͻ��˷���������󳤶�
 * @param c kframework_acceptor_config_tʵ��
 * @param max_send_list_count ����������󳤶�(�ֽ�)
 */
extern void knet_framework_acceptor_config_set_client_max_send_list_count(
    kframework_acceptor_config_t* c, int max_send_list_count);

/**
 * ���ÿͻ��˽��ջ�������󳤶�
 * @param c kframework_acceptor_config_tʵ��
 * @param max_recv_buffer_length ���ջ�������󳤶�(�ֽ�)
 */
extern void knet_framework_acceptor_config_set_client_max_recv_buffer_length(
    kframework_acceptor_config_t* c, int max_recv_buffer_length);

/**
 * ������������Ҫ���ӵĵ�ַ
 * @param c kframework_connector_config_tʵ��
 * @param ip IP
 * @param port �˿�
 */
extern void knet_framework_connector_config_set_remote_address(
    kframework_connector_config_t* c, const char* ip, int port);

/**
 * ����������������ʱ
 * @param c kframework_connector_config_tʵ��
 * @param timeout �ͻ���������ʱ(��)
 */
extern void knet_framework_connector_config_set_heartbeat_timeout(
    kframework_connector_config_t* c, int timeout);

/**
 * �������������ӳ�ʱ
 * @param c kframework_connector_config_tʵ��
 * @param timeout ���ӳ�ʱ(��)
 */
extern void knet_framework_connector_config_set_connect_timeout(
    kframework_connector_config_t* c, int timeout);

/**
 * �����������Զ�����
 * @param c kframework_connector_config_tʵ��
 * @param auto_reconnect �Զ�������־
 */
extern void knet_framework_connector_config_set_auto_reconnect(
    kframework_connector_config_t* c, int auto_reconnect);

/**
 * �����������ص�����
 * @param c kframework_connector_config_tʵ��
 * @param cb �������ص�����
 */
extern void knet_framework_connector_config_set_cb(
    kframework_connector_config_t* c, knet_channel_ref_cb_t cb);

/**
 * ��������������������󳤶�
 * @param c kframework_connector_config_tʵ��
 * @param max_send_list_count ����������󳤶�(�ֽ�)
 */
extern void knet_framework_connector_config_set_client_max_send_list_count(
    kframework_connector_config_t* c, int max_send_list_count);

/**
 * �������������ջ�������󳤶�
 * @param c kframework_connector_config_tʵ��
 * @param max_recv_buffer_length ���ջ�������󳤶�(�ֽ�)
 */
extern void knet_framework_connector_config_set_client_max_recv_buffer_length(
    kframework_connector_config_t* c, int max_recv_buffer_length);

/** @} */

#endif /* FRAMEWORK_CONFIG_API_H */
