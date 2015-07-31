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

#ifndef NODE_API_H
#define NODE_API_H

#include "config.h"

/**
 * ����һ���µĽڵ�
 * @return knode_tʵ��
 */
extern knode_t* knet_node_create();

/**
 * ���ٽڵ�
 * @param node knode_tʵ��
 */
extern void knet_node_destroy(knode_t* node);

/**
 * ���ٽڵ�
 * @param node knode_tʵ��
 */
extern knode_config_t* knet_node_get_config(knode_t* node);

/**
 * �����ڵ�
 * @param node knode_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_start(knode_t* node);

/**
 * �رսڵ�
 * @param node knode_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_stop(knode_t* node);

/**
 * �ȴ��ڵ�ر�
 * @param node knode_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern void knet_node_wait_for_stop(knode_t* node);

/**
 * �㲥���ݵ������뱾�ڵ������ӵĽڵ�
 * @param node knode_tʵ��
 * @param msg ���ݰ�
 * @param size ���ݳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_broadcast(knode_t* node, const void* msg, int size);

/**
 * �㲥���ݵ������뱾�ڵ������ӵĽڵ��ָ�����ͽڵ�
 * @param node knode_tʵ��
 * @param type �ڵ�����
 * @param msg ���ݰ�
 * @param size ���ݳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_broadcast_by_type(knode_t* node, uint32_t type, const void* msg, int size);

/**
 * �������ݵ�ָ��ID�Ľڵ�
 * @param node knode_tʵ��
 * @param id �ڵ�ID
 * @param msg ���ݰ�
 * @param size ���ݳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_write(knode_t* node, uint32_t id, const void* msg, int size);

/**
 * ȡ�ÿ��
 * @param node knode_tʵ��
 * @return kframework_tʵ��
 */
extern kframework_t* knet_node_get_framework(knode_t* node);

/**
 * ȡ��IP������
 * @param node knode_tʵ��
 * @return kip_filter_tʵ��
 */
extern kip_filter_t* knet_node_get_black_ip_filter(knode_t* node);

/**
 * ȡ��IP������
 * @param node knode_tʵ��
 * @return kip_filter_tʵ��
 */
extern kip_filter_t* knet_node_get_white_ip_filter(knode_t* node);

/**
 * ȡ�ýڵ����ID
 *
 * �ڵ����ID��Զ�̽ڵ��ID
 * @param proxy knode_proxy_tʵ��
 * @return �ڵ����ID
 */
extern uint32_t knet_node_proxy_get_id(knode_proxy_t* proxy);

/**
 * ȡ�ýڵ��������
 *
 * �ڵ����ID��Զ�̽ڵ������
 * @param proxy knode_proxy_tʵ��
 * @return �ڵ����ID
 */
extern uint32_t knet_node_proxy_get_type(knode_proxy_t* proxy);

/**
 * ȡ�ýڵ�����ο��Զ�ȡ�����ݳ��ȣ��˳��ȴ�����һ�νڵ㷢��
 * @param proxy knode_proxy_tʵ��
 * @return ���ο��Զ�ȡ�����ݳ���
 */
extern uint32_t knet_node_proxy_get_data_length(knode_proxy_t* proxy);

#endif /* NODE_API_H */
