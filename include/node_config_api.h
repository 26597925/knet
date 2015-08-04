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

#ifndef NODE_CONFIG_API_H
#define NODE_CONFIG_API_H

#include "config.h"

/**
 * ���ýڵ����
 * @param c knode_config_tʵ��
 * @param type �ڵ�����
 * @param id �ڵ�ID
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_identity(knode_config_t* c, uint32_t type, uint32_t id);

/**
 * ���ýڵ��ע�Ľڵ�����
 *
 * <pre>
 * �ڵ�����Ϊuint32_t���͵���Ч�����޷�������ֵ���ɱ���������һ����������Ϊ0
 * </pre>
 * @param c knode_config_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_concern_type(knode_config_t* c, ...);

/**
 * ���ýڵ㹤���߳�����
 * @param c knode_config_tʵ��
 * @param worker_count �����߳�������Ĭ��Ϊһ�������߳�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern void knet_node_config_set_worker_thread_count(knode_config_t* c, int worker_count);

/**
 * ���ýڵ㱾�ؼ�����ַ�������ڵ����ͨ�������ַ�������ӱ��ڵ�
 * @param c knode_config_tʵ��
 * @param ip IP
 * @param port �˿�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_address(knode_config_t* c, const char* ip, int port);

/**
 * ���ø��ڵ�ļ�����ַ��������ؼ�����ַ����ڵ������ַ��ͬ�򱾽ڵ�Ϊ���ڵ�
 *
 * <pre>
 * Ҳ����ͨ������knet_node_config_set_root�����ڵ�����Ϊ���ڵ㣬ͬһ����Ⱥ�ڿ����ж�����ڵ㣬��ÿ��
 * ���ڵ㶼��Ϊ�Լ���Ψһ�ĸ��ڵ�
 * </pre>
 * @param c knode_config_tʵ��
 * @param ip IP
 * @param port �˿�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_root_address(knode_config_t* c, const char* ip, int port);

/**
 * ���ýڵ�Ϊ���ڵ�
 * @param c knode_config_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_root(knode_config_t* c);

/**
 * ���ñ��ڵ��Ƿ�Ϊ���ڵ�
 * @param c knode_config_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_check_root(knode_config_t* c);

/**
 * ���ýڵ��¼�������
 * @param c knode_config_tʵ��
 * @param cb �¼�������
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_node_cb(knode_config_t* c, knet_node_cb_t cb);

/**
 * ���ýڵ��ص�ַ���������ӵ����������ַ�����Ӷ����յ�һ���ı��㱨��Ϣ�������Ͽ�����
 * @param c knode_config_tʵ��
 * @param ip IP
 * @param port �˿�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_monitor_address(knode_config_t* c, const char* ip, int port);

/**
 * ���ýڵ���������ַ�����ӵ���������ַ�����ӽ����ֳ�����
 * @param c knode_config_tʵ��
 * @param ip IP
 * @param port �˿�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_manage_address(knode_config_t* c, const char* ip, int port);

/**
 * ���ýڵ�����������
 * @param c knode_config_tʵ��
 * @param cb �������
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_manage_cb(knode_config_t* c, knet_node_manage_cb_t cb);

/**
 * ���ýڵ��ػص�
 * @param c knode_config_tʵ��
 * @param cb �ڵ��ػص�����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_monitor_cb(knode_config_t* c, knet_node_monitor_cb_t cb);

/**
 * ����/�رսڵ��˳��Զ�����IP������
 * @param c knode_config_tʵ��
 * @param on ���ʾ�رգ������ʾ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_black_ip_filter_auto_save_at_exit(knode_config_t* c, int on);

/**
 * ����IP�������ļ�·��
 * @param c knode_config_tʵ��
 * @param path �������ļ�·��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_black_ip_filter_file_path(knode_config_t* c, const char* path);

/**
 * ����/�رսڵ��˳��Զ�����IP������
 * @param c knode_config_tʵ��
 * @param on ���ʾ�رգ������ʾ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_white_ip_filter_auto_save_at_exit(knode_config_t* c, int on);

/**
 * ����IP�������ļ�·��
 * @param c knode_config_tʵ��
 * @param path �������ļ�·��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_config_set_white_ip_filter_file_path(knode_config_t* c, const char* path);

/**
 * ���ýڵ�ܵ����ջ�������󳤶�
 * @param c knode_config_tʵ��
 * @param max_recv_buffer_length �ܵ����ջ�������󳤶�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern void knet_node_config_set_node_channel_max_recv_buffer_length(knode_config_t* c, int max_recv_buffer_length);

/**
 * ���ýڵ�ܵ����ͻ���������󳤶�
 * @param c knode_config_tʵ��
 * @param max_send_list_count ���ͻ���������󳤶�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern void knet_node_config_set_node_channel_max_send_list_count(knode_config_t* c, int max_send_list_count);

/**
 * ���ýڵ�ܵ����г�ʱ���룩
 * @param c knode_config_tʵ��
 * @param timeout �ܵ����г�ʱ���룩
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern void knet_node_config_set_node_channel_idle_timeout(knode_config_t* c, int timeout);

/**
 * ȡ�ÿ������
 * @param c knode_config_tʵ��
 * @return kframework_config_tʵ��
 */
extern kframework_config_t* knet_node_config_get_framework_config(knode_config_t* c);

/**
 * ���ù����������Ļ�������󳤶�
 * @param c knode_config_tʵ��
 * @param max_output_buffer_length ��������󳤶�
 */
extern void knet_node_config_set_manage_max_output_buffer_length(knode_config_t* c, int max_output_buffer_length);

#endif /* NODE_CONFIG_API_H */
