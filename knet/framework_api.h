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

#ifndef FRAMEWORK_API_H
#define FRAMEWORK_API_H

#include "config.h"

/**
 * @defgroup framework ���
 * ������
 *
 * <pre>
 * Ϊ����ʹ���ṩ��framework_t�ӿڣ��Զ��߳�ģʽ(Ҳ�������߼��߳�)�ṩ�˰�װ��
 *
 * 1. �����ļ����̣߳�����channel_cb_event_accept�¼��������̲߳�����ܵ���д
 * 2. �ṩ��һ�������̳߳أ�ʹ��loop_balancer_t(���ؾ�����)�����ɹܵ�
 *
 * Ĭ������¹����̳߳���ֻ��һ���̣߳�����ͨ�����ýӿں���framework_config_set_worker_thread_count
 * ��������. ���Ĭ�ϻ����������̣߳�һ�������̣߳�һ�������߳�(�����̳߳���Ψһ�߳�).
 *
 * framework_config_t�ṩ��ͳһ�����ýӿڣ���framework_t��������Ի�ȡframework_config_t
 * �ӿڽ������ã�����framework_start�����ɹ��󽫲��ܸ�������.
 *
 * framework_start�ĵڶ�������Ϊ�ܵ��ص���������channel_ref_set_cb�����õĻص�������ͬ��
 * ����ܵĻص����������̳߳��ڱ��ص�������ж�������̵߳�����£�Ӧ�ñ�֤�ص������ڵĴ������̰߳�ȫ��.
 *
 * </pre>
 * @{
 */

/**
 * �������
 * @return framework_tʵ��
 */
extern framework_t* framework_create();

/**
 * ���ٿ��
 * @param f framework_tʵ��
 */
extern void framework_destroy(framework_t* f);

/**
 * �������
 * @param f framework_tʵ��
 * @param cb ��ܻص�����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int framework_start(framework_t* f, channel_ref_cb_t cb);

/**
 * �رտ��
 * @param f framework_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int framework_stop(framework_t* f);

/**
 * ȡ�ÿ������
 * @param f framework_tʵ��
 * @return framework_config_tʵ��
 */
extern framework_config_t* framework_get_config(framework_t* f);

/**
 * ����IP��ַ�ͼ����˿�
 * @param c framework_config_tʵ��
 * @param ip IP
 * @param port �˿�
 */
extern void framework_config_set_address(framework_config_t* c, const char* ip, int port);

/**
 * ����backlog
 * @param c framework_config_tʵ��
 * @param backlog �ȴ����г���
 */
extern void framework_config_set_backlog(framework_config_t* c, int backlog);

/**
 * ���ù����߳�������Ĭ��Ϊ���߳�
 * @param c framework_config_tʵ��
 * @param worker_thread_count �����߳�����
 */
extern void framework_config_set_worker_thread_count(framework_config_t* c, int worker_thread_count);

/**
 * ���ý��ܵ����ӵķ��Ͷ�����󳤶�
 * @param c framework_config_tʵ��
 * @param max_send_list ���ܵ����ӵķ��Ͷ�����󳤶�
 */
extern void framework_config_set_max_send_list(framework_config_t* c, int max_send_list);

/**
 * ���ý��ܵ����ӵĽ��ջ�������󳤶�
 * @param c framework_config_tʵ��
 * @param max_recv_buffer ���ܵ����ӵĽ��ջ�������󳤶�
 */
extern void framework_config_set_max_recv_buffer(framework_config_t* c, int max_recv_buffer);

/**
 * ���ý��ܵ����ӵ�������ʱʱ��
 * @param c framework_config_tʵ��
 * @param max_idle_timeout ���ܵ����ӵ�������ʱʱ��
 */
extern void framework_config_set_max_idle_timeout(framework_config_t* c, int max_idle_timeout);

/** @} */

#endif /* FRAMEWORK_API_H */
