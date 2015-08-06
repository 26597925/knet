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
 * @defgroup node �ڵ�
 * �ڵ�
 *
 * <pre>
 * �ڵ��ṩ�����¼�����Ĺ��ܣ�
 * 1. ����
 * 2. ��أ�����
 * 3. IP������/������
 * 
 * <b>����</b>
 * �ڵ��Ϊ���ڵ����ͨ�ڵ��������ͣ����ڵ���Ϊ������֪ͨ�ߴ��ڣ������������£�
 * 1. ��ͨ�ڵ����ѡ�����Ӹ��ڵ㣨ͨ�����ã�����ͨ�ڵ���������Լ�����ע�������ڵ������(node-type)
 * 2. ���ӵ����ڵ��㱨�Լ������{IP, port, node-type, node-id}
 * 3. ���ڵ������¼���Ľڵ�������Ϣ�������Ѿ��ڽڵ㼯Ⱥ�ڵ������ڵ�
 * 4. ���յ����ڵ����͹����������Ϣ��������Լ���ע�Ľڵ����ͣ���ôת������5������������
 * 5. ���������¼���Ľڵ㲢�㱨�Լ�����ݣ��¼���Ľڵ�ͬʱҲ�����Լ�����ݸ������Լ��Ľڵ�
 *
 * <b>���</b>
 * ÿ���ڵ��ṩ��һ����ض˿ں�һ������˿�.
 * 1. ��ض˿�
 *    ��ض˿ڿ��Ա��κμ�ؿͻ������ӣ���������ӽ������ڵ��ص��û����õļ�ػص��������ص�����
 *    �˳������ӽ����Ͽ�.
 * 2. ����˿�
 *    ����˿�ͨ��Ӧ�����ڶ������������ϣ����������ܱ����ĵ�ַ�ϣ�����Ӧ�ñ��������ʵ�. ����м��
 *    �ͻ������ӣ���ô��ؿͻ��˿��Է���������û����õĻص�������������Ϊһ���ַ����Բ����Իس����н�β,
 *    ����ͬʱ���Ͷ�������. �ص���������ͨ������ֵ�����߽ڵ�����Ĵ���ʽ: �������ӻ��������ɺ�Ͽ�
 *    ����.
 *
 * <b>IP������/������</b>
 * ����û��ṩ����IP�����ļ���ͨ�����ã�����ô���Զ�������IP�������ˣ����˹���Ϊ��
 * 1. ����������
 * 2. ���ڰ�������IP���Ա�����������
 *
 * �������ÿɲμ��ڵ�����.
 * </pre>
 * @{
 */

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
 * �����ڵ㣬ʹ�������д��ݵĲ���
 *
 * <pre>
 * �����в���Ϊ
 * -root ip:port
 * -self ip:port:node-type:node-id
 * </pre>
 * @param node knode_tʵ��
 * @param argc �����в�������
 * @param argv �����в�������
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_start_argv(knode_t* node, int argc, char** argv);

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

/**
 * ȡ�ñ����ڵ�
 * @param proxy knode_proxy_tʵ��
 * @return �����ڵ�
 */
extern knode_t* knet_node_proxy_get_self(knode_proxy_t* proxy);

/**
 * ���͵��ڵ�
 * @param proxy knode_proxy_tʵ��
 * @param buffer ����
 * @param size ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_proxy_write(knode_proxy_t* proxy, void* buffer, int size);

/**
 * ��ȡ�ڵ�����
 * @param proxy knode_proxy_tʵ��
 * @param buffer ����
 * @param size ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_proxy_read(knode_proxy_t* proxy, void* buffer, int size);

/**
 * ��ȡ�ڵ����ݣ��������
 * @param proxy knode_proxy_tʵ��
 * @param buffer ����
 * @param size ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_proxy_copy(knode_proxy_t* proxy, void* buffer, int size);

/**
 * �ɶ�ȡ���ݵĳ��ȣ��ֽڣ�
 * @param proxy knode_proxy_tʵ��
 * @return �ɶ�ȡ���ݵĳ��ȣ��ֽڣ�
 */
extern int knet_node_proxy_available(knode_proxy_t* proxy);

/**
 * �Ͽ��ڵ�����
 * @param proxy knode_proxy_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_node_proxy_close(knode_proxy_t* proxy);

/** @} */

#endif /* NODE_API_H */
