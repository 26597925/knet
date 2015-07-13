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

#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "framework_api.h"

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
 * ��ȡIP
 * @param c framework_config_tʵ��
 * @return IP
 */
const char* framework_config_get_ip(framework_config_t* c);

/**
 * ��ȡ�����˿�
 * @param c framework_config_tʵ��
 * @return �����˿�
 */
int framework_config_get_port(framework_config_t* c);

/**
 * ��ȡbacklog
 * @param c framework_config_tʵ��
 * @return backlog
 */
int framework_config_get_backlog(framework_config_t* c);

/**
 * ��ȡ�����߳�����
 * @param c framework_config_tʵ��
 * @return �����߳�����
 */
int framework_config_get_worker_thread_count(framework_config_t* c);

/**
 * ��ȡ�����������Ԫ����
 * @param c framework_config_tʵ��
 * @return �����������Ԫ����
 */
int framework_config_get_max_send_list(framework_config_t* c);

/**
 * ��ȡ���ջ�������󳤶�
 * @param c framework_config_tʵ��
 * @return ���ջ�������󳤶�
 */
int framework_config_get_max_recv_buffer(framework_config_t* c);

/**
 * ��ȡ���ܵ����ӵ�������ʱʱ��
 * @param c framework_config_tʵ��
 * @return ���ܵ����ӵ�������ʱʱ��
 */
int framework_config_get_max_idle_timeout(framework_config_t* c);

/**
 * �¼�channel_cb_event_accept������
 * @param channel �����ܵ���channel_ref_tʵ��
 * @param e �ܵ��¼�
 */
void acceptor_cb(channel_ref_t* channel, channel_cb_event_e e);

/**
 * ��ȡ���ؾ�����
 * @param f framework_tʵ��
 * @return loop_balancer_tʵ��
 */
loop_balancer_t* framework_get_balancer(framework_t* f);

/**
 * ��ȡ�ܵ��ص�
 * @param f framework_tʵ��
 * @return �ܵ��ص�����ָ��
 */
channel_ref_cb_t framework_get_cb(framework_t* f);

#endif /* FRAMEWORK_H */
