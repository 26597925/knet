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

#ifndef RPC_API_H
#define RPC_API_H

/**
 * RPC����ṩ��һ�׵ײ�RPC���л��������л��Ļ����������߲�Ӧ��ֱ�ӵ�����ЩAPI��Ӧʹ�ô������ɹ���
 * �ṩ�Ĵ�����������RPC���������ɵĴ��������������з��˵�ϸ�ڣ�ʹ������Ҳ���ֱ�ӵ�����ЩAPI��
 * ����.
 */

#include "config.h"

/**
 * ����RPC
 * @return krpc_tʵ��
 */
extern krpc_t* krpc_create();

/**
 * ����RPC
 * @param rpc krpc_tʵ��
 */
extern void krpc_destroy(krpc_t* rpc);

/**
 * ע��RPC���ûص�����
 * @param rpc krpc_tʵ��
 * @param rpcid �ص�ID
 * @param cb �ص�����ָ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int krpc_add_cb(krpc_t* rpc, uint16_t rpcid, krpc_cb_t cb);

/**
 * ɾ��ע�����RPC���ûص�����
 * @param rpc krpc_tʵ��
 * @param rpcid �ص�ID
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int krpc_del_cb(krpc_t* rpc, uint16_t rpcid);

/**
 * ȡ��ע�����RPC���ûص�����
 * @param rpc krpc_tʵ��
 * @param rpcid �ص�ID
 * @return �ص�����ָ��
 */
extern krpc_cb_t krpc_get_cb(krpc_t* rpc, uint16_t rpcid);

/**
 * ����RPC���ã��������������л�RPC���ã������ûص�����
 * @param rpc krpc_tʵ��
 * @param stream ������
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int krpc_proc(krpc_t* rpc, kstream_t* stream);

/**
 * ����RPC����
 * @param rpc krpc_tʵ��
 * @param stream ������
 * @param rpcid �ص�ID
 * @param o ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int krpc_call(krpc_t* rpc, kstream_t* stream, uint16_t rpcid, krpc_object_t* o);

/**
 * ����ǩ�����ܻص�
 * @param rpc krpc_tʵ��
 * @param func �ص�����ָ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int krpc_set_encrypt_cb(krpc_t* rpc, krpc_encrypt_t func);

/**
 * ����ǩ�����ܻص�
 * @param rpc krpc_tʵ��
 * @param func �ص�����ָ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int krpc_set_decrypt_cb(krpc_t* rpc, krpc_decrypt_t func);

#endif /* RPC_API_H */
