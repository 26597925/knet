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

#ifndef NODE_H
#define NODE_H

#include "config.h"
#include "node_api.h"

/**
 * ��ӽڵ����
 * @param node knode_tʵ��
 * @param type �ڵ�����
 * @param id �ڵ�ID
 * @param channel �ڵ����ܵ�����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int knet_node_add_node(knode_t* node, uint32_t type, uint32_t id, kchannel_ref_t* channel);

/**
 * ɾ���ڵ����
 * @param node knode_tʵ��
 * @param channel �ڵ����ܵ�����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int knet_node_remove_node_by_channel_ref(knode_t* node, kchannel_ref_t* channel);

/**
 * ɾ���ڵ����
 * @param node knode_tʵ��
 * @param id �ڵ����ID
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int knet_node_remove_node_by_id(knode_t* node, uint32_t id);

/**
 * �����ڵ����
 * @return knode_proxy_tʵ��
 */
knode_proxy_t* node_proxy_create();

/**
 * ���ٽڵ����
 * @param proxy knode_proxy_tʵ��
 */
void node_proxy_destroy(knode_proxy_t* proxy);

/**
 * ��ϣ��ֵ���ٺ���
 * @param param �ڵ����ָ��
 */
void hash_node_channel_id_dtor(void* param);

/**
 * �������ڵ������
 * @param node knode_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int node_root_start(knode_t* node);

/**
 * ���Ӹ��ڵ�
 * @param node knode_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int node_connect_root(knode_t* node);

/**
 * �����ڵ������
 * @param node knode_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int node_local_start(knode_t* node);

/**
 * ��ȡIP��/�������ļ�
 * @param node knode_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int node_open_filter_files(knode_t* node);

/**
 * ����IP��/�������ļ�
 * @param node knode_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
void node_save_filter_files(knode_t* node);

/**
 * �ڵ�ܵ��ص�
 * @param channel kchannel_ref_tʵ��
 * @param e �ܵ��¼�ID
 */
void node_channel_cb(kchannel_ref_t* channel, knet_channel_cb_event_e e);

/**
 * ���ͽڵ������֤����
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _node_login_req(kchannel_ref_t* channel);

/**
 * ���ͽڵ������֤Ӧ��
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _node_login_ack(kchannel_ref_t* channel);

/**
 * �������ݵ������ڵ�
 * @param channel kchannel_ref_tʵ��
 * @param data ���ݿ�ָ��
 * @param size ���ݳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _node_send(kchannel_ref_t* channel, const void* data, uint32_t size);

/**
 * ���ڵ�֪ͨ�����ڵ����½ڵ���뼯Ⱥ
 * @param channel kchannel_ref_tʵ��
 * @param ip �¼���ڵ�IP
 * @param port �¼���ڵ�����˿�
 * @param type �¼���ڵ�����
 * @param id �¼���ڵ�ID
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _node_broadcast_join(knode_t* node, const char* ip, int port, uint32_t type, uint32_t id);

/**
 * ��ȡ��ϢID
 * @param channel kchannel_ref_tʵ��
 * @return ��ϢID
 */
uint32_t _proc_msg_id(kchannel_ref_t* channel);

/**
 * ������������
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _node_send_heartbeat_req(kchannel_ref_t* channel);

/**
 * ��������Ӧ��
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _node_send_heartbeat_ack(kchannel_ref_t* channel);

/**
 * �����֤��������
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_login_req(kchannel_ref_t* channel);

/**
 * �����֤Ӧ������
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_login_ack(kchannel_ref_t* channel);

/**
 * �½ڵ����֪ͨ������
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_join(kchannel_ref_t* channel);

/**
 * �ڵ����ݴ�����
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_data(kchannel_ref_t* channel);

/**
 * �ڵ�ܵ��ɹ������� - ��������
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_connect(kchannel_ref_t* channel);

/**
 * �ڵ�ܵ��ɹ������� - ����
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_accept(kchannel_ref_t* channel);

/**
 * �ڵ�ܵ����ݴ�����
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_recv(kchannel_ref_t* channel);

/**
 * �ڵ��ڲ�Э�鴦����ں���
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_disjoin(kchannel_ref_t* channel);

/**
 * �ڵ�ܵ���ʱ������
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_timeout(kchannel_ref_t* channel);

/**
 * �ڵ�������������
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_heartbeat_req(kchannel_ref_t* channel);

/**
 * �ڵ�����Ӧ������
 * @param channel kchannel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int _on_node_heartbeat_ack(kchannel_ref_t* channel);

#endif /* NODE_H */
