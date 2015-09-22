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

#ifndef NODE_CONFIG_H
#define NODE_CONFIG_H

#include "config.h"
#include "node_config_api.h"

/**
 * �����ڵ�����
 * @param node knode_tʵ��
 * @return knode_config_tʵ��
 */
knode_config_t* knet_node_config_create(knode_t* node);

/**
 * ���ٽڵ�����
 * @param c knode_config_tʵ��
 */
void knet_node_config_destroy(knode_config_t* c);

/**
 * ȡ�ñ��ڵ�����
 * @param c knode_config_tʵ��
 * @return �ڵ�����
 */
uint32_t knet_node_config_get_type(knode_config_t* c);

/**
 * ȡ�ñ��ڵ�����
 * @param c knode_config_tʵ��
 * @return �ڵ�����
 */
uint32_t knet_node_config_get_id(knode_config_t* c);

/**
 * ȡ�ýڵ㹤���߳�����
 * @param c knode_config_tʵ��
 * @return �����߳�����
 */
int knet_node_config_get_worker_thread_count(knode_config_t* c);

/**
 * ȡ�ýڵ����IP
 * @param c knode_config_tʵ��
 * @return ����IP
 */
const char* knet_node_config_get_ip(knode_config_t* c);

/**
 * ȡ�ýڵ�����˿�
 * @param c knode_config_tʵ��
 * @return �����˿�
 */
int knet_node_config_get_port(knode_config_t* c);

/**
 * ȡ�ø��ڵ����IP
 * @param c knode_config_tʵ��
 * @return ���ڵ����IP
 */
const char* knet_node_config_get_root_ip(knode_config_t* c);

/**
 * ȡ�ø��ڵ�����˿�
 * @param c knode_config_tʵ��
 * @return ���ڵ�����˿�
 */
int knet_node_config_get_root_port(knode_config_t* c);

/**
 * ȡ�ýڵ��¼�������
 * @param c knode_config_tʵ��
 * @return �ڵ��¼�������
 */
knet_node_cb_t knet_node_config_get_node_cb(knode_config_t* c);

/**
 * ȡ�ýڵ���IP
 * @param c knode_config_tʵ��
 * @return �ڵ���IP
 */
const char* knet_node_config_get_monitor_ip(knode_config_t* c);

/**
 * ȡ�ýڵ��ض˿�
 * @param c knode_config_tʵ��
 * @return �ڵ��ض˿�
 */
int knet_node_config_get_monitor_port(knode_config_t* c);

/**
 * ȡ�ýڵ����IP
 * @param c knode_config_tʵ��
 * @return �ڵ����IP
 */
const char* knet_node_config_get_manage_ip(knode_config_t* c);

/**
 * ȡ�ýڵ����˿�
 * @param c knode_config_tʵ��
 * @return �ڵ����˿�
 */
int knet_node_config_get_manage_port(knode_config_t* c);

/**
 * ȡ�ýڵ�����������ָ��
 * @param c knode_config_tʵ��
 * @return �����������ָ��
 */
knet_node_manage_cb_t knet_node_config_get_manage_cb(knode_config_t* c);

/**
 * ȡ�ýڵ��ش�����ָ��
 * @param c knode_config_tʵ��
 * @return ��ش�����ָ��
 */
knet_node_monitor_cb_t knet_node_config_get_monitor_cb(knode_config_t* c);

/**
 * ȡ�ýڵ�IP�������˳��Զ����濪��
 * @param c knode_config_tʵ��
 * @return IP�������˳��Զ����濪��
 */
int knet_node_config_get_black_ip_filter_auto_save_at_exit(knode_config_t* c);

/**
 * ȡ�ýڵ�IP�������ļ�·��
 * @param c knode_config_tʵ��
 * @return IP�������ļ�·��
 */
const char* knet_node_config_get_black_ip_filter_file_path(knode_config_t* c);

/**
 * ȡ�ýڵ�IP�������˳��Զ����濪��
 * @param c knode_config_tʵ��
 * @return IP�������˳��Զ����濪��
 */
int knet_node_config_get_white_ip_filter_auto_save_at_exit(knode_config_t* c);

/**
 * ȡ�ýڵ�IP�������ļ�·��
 * @param c knode_config_tʵ��
 * @return IP�������ļ�·��
 */
const char* knet_node_config_get_white_ip_filter_file_path(knode_config_t* c);

/**
 * ���ڵ������Ƿ�Ϊ��ע����
 * @param c knode_config_tʵ��
 * @param type �ڵ�����
 * @retval �� ����
 * @retval ���� ��
 */
int knet_node_config_concern(knode_config_t* c, int type);

/**
 * ȡ�ýڵ�ܵ����ջ�������󳤶ȣ��ֽڣ�
 * @param c knode_config_tʵ��
 * @return �ڵ�ܵ����ջ�������󳤶�
 */
int knet_node_config_get_node_channel_max_recv_buffer_length(knode_config_t* c);

/**
 * ȡ�ýڵ�ܵ����ͻ���������󳤶ȣ��ֽڣ�
 * @param c knode_config_tʵ��
 * @return �ڵ�ܵ����ͻ���������󳤶�
 */
int knet_node_config_get_node_channel_max_send_list_count(knode_config_t* c);

/**
 * ȡ�ýڵ�ܵ����г�ʱ���룩
 * @param c knode_config_tʵ��
 * @return �ڵ�ܵ����г�ʱ���룩
 */
int knet_node_config_get_node_channel_idle_timeout(knode_config_t* c);

/**
 * ȡ�ù�����������������󳤶ȣ��ֽڣ�
 * @param c knode_config_tʵ��
 * @return ������������������󳤶ȣ��ֽڣ�
 */
int knet_node_config_get_manage_max_output_buffer_length(knode_config_t* c);

/**
 * ȡ���û�ָ��
 * @param c knode_config_tʵ��
 * @return �û�ָ��
 */
void* knet_node_config_get_ptr(knode_config_t* c);

#endif /* NODE_CONFIG_H */
