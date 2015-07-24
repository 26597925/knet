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

#ifndef RPC_OBJECT_H
#define RPC_OBJECT_H

#include "config.h"
#include "rpc_object_api.h"

/**
 * ��ȡ���ֶ������л�����
 * @param o krpc_object_tʵ��
 * @return ���ֶ������л�����
 */
uint16_t krpc_number_get_marshal_size(krpc_object_t* o);

/**
 * �����ַ�������
 * @param o krpc_object_tʵ��
 * @param size ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int krpc_string_set_size(krpc_object_t* o, uint16_t size);

/**
 * ��չ����
 * @param o krpc_object_tʵ��
 */
void krpc_vector_enlarge(krpc_object_t* o);

/**
 * ��ֵ���ٺ���
 */
void hash_value_dtor(void* v);

#endif /* RPC_OBJECT_H */
