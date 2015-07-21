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
 * Ϊ����ʹ���ṩ��kframework_t�ӿڣ��Զ��߳�ģʽ(Ҳ�������߼��߳�)�ṩ�˰�װ��
 *
 * 1. �����ļ����̣߳�����channel_cb_event_accept�¼��������̲߳�����ܵ���д
 * 2. �ṩ��һ�������̳߳أ�ʹ��kloop_balancer_t(���ؾ�����)�����ɹܵ�
 * 3. �ṩ��ͳһ�����ýӿڷ��㽨��������������߼�����
 *
 * Ĭ������¹����̳߳���ֻ��һ���̣߳�����ͨ�����ýӿں���knet_framework_config_set_worker_thread_count
 * ��������. ���Ĭ�ϻ����������̣߳�һ�������̣߳�һ�������߳�(�����̳߳���Ψһ�߳�)������accept����
 * connect�Ĺܵ����ᱻ���ɵ���ͬ�Ĺ����̴߳��������߳�ֻ�������ӵĽ����������д.
 *
 * kframework_config_t�ṩ��ͳһ�����ýӿڣ���kframework_t��������Ի�ȡkframework_config_t
 * �ӿڽ������ã�����knet_framework_start�����ɹ��󽫲��ܸ����Ѿ����������ã��������������������µļ�������������.
 *
 * ��ܵĻص����������̳߳��ڱ��ص�������ж�������̵߳�����£�Ӧ�ñ�֤�ص������ڵĴ������̰߳�ȫ�ģ�
 * Ϊ�˷���ʹ�ã���ܵĻص�����Ҳ��֪ͨchannel_cb_event_accept�¼�.
 *
 * �����ڹ����߳��ڵ���knet_framework_create_worker_timer������ʱ���������ڹ����߳��ⴴ�������̶߳�ʱ��.
 * </pre>
 * @{
 */

/**
 * �������
 * @return kframework_tʵ��
 */
extern kframework_t* knet_framework_create();

/**
 * ���ٿ��
 * @param f kframework_tʵ��
 */
extern void knet_framework_destroy(kframework_t* f);

/**
 * �������
 * @param f kframework_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_framework_start(kframework_t* f);

/**
 * ������ܲ��ȴ���ܹر�
 * @param f kframework_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_framework_start_wait(kframework_t* f);

/**
 * ������ܲ��ȴ���ܹرգ��������ʧ�ܻ��߿�ܹر�������
 * @param f kframework_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_framework_start_wait_destroy(kframework_t* f);

/**
 * �ȴ����ֹͣ
 * @param f kframework_tʵ��
 */
extern void knet_framework_wait_for_stop(kframework_t* f);

/**
 * �ȴ����ֹͣ������
 * @param f kframework_tʵ��
 */
extern void knet_framework_wait_for_stop_destroy(kframework_t* f);

/**
 * �رտ��
 * @param f kframework_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_framework_stop(kframework_t* f);

/**
 * ȡ�ÿ������
 * @param f kframework_tʵ��
 * @return kframework_config_tʵ��
 */
extern kframework_config_t* knet_framework_get_config(kframework_t* f);

/**
 * ����������
 * @param f kframework_tʵ��
 * @param c kframework_acceptor_config_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_framework_acceptor_start(kframework_t* f, kframework_acceptor_config_t* c);

/**
 * ����������
 * @param f kframework_tʵ��
 * @param c kframework_connector_config_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_framework_connector_start(kframework_t* f, kframework_connector_config_t* c);

/**
 * ����һ�������̶߳�ʱ��
 * ֻ���ڹ����߳��ڽ�����ʱ��������ڷǹ����߳��ڽ�����ʱ����ʧ��
 * @param f kframework_tʵ��
 * @return ktimer_tʵ��
 */
extern ktimer_t* knet_framework_create_worker_timer(kframework_t* f);

/** @} */

#endif /* FRAMEWORK_API_H */
