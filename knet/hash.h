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

#ifndef HASH_H
#define HASH_H

#include "config.h"

/*
 * �ڲ�ʹ�ã���ϣ��ͬʱ֧�����ֻ��ַ�����Ϊkey
 */

/*
 * ������ϣ��
 * @param size ��ϣ��Ͱ����, 0��ʹ��Ĭ��Ͱ����
 * @param dtor �û��Զ���ֵ���ٺ���
 * @return hash_tʵ��
 */
hash_t* hash_create(uint32_t size, hash_dtor_t dtor);

/*
 * ���ٹ�ϣ��
 * @param hash hash_tʵ��
 */
void hash_destroy(hash_t* hash);

/*
 * ���Ԫ��
 * @param hash hash_tʵ��
 * @param key ��
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int hash_add(hash_t* hash, uint32_t key, void* value);

/*
 * ���Ԫ��
 * @param hash hash_tʵ��
 * @param key �ַ�����
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int hash_add_string_key(hash_t* hash, const char* key, void* value);

/*
 * �Ƴ�Ԫ��
 * @param hash hash_tʵ��
 * @param key ��
 * @retval 0 δ�ҵ�
 * @retval ��Чָ�� ֵ
 */
void* hash_remove(hash_t* hash, uint32_t key);

/*
 * �Ƴ�Ԫ��
 * @param hash hash_tʵ��
 * @param key �ַ�����
 * @retval 0 δ�ҵ�
 * @retval ��Чָ�� ֵ
 */
void* hash_remove_string_key(hash_t* hash, const char* key);

/*
 * ����Ԫ��
 * @param hash hash_tʵ��
 * @param key ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int hash_delete(hash_t* hash, uint32_t key);

/*
 * ����Ԫ��
 * @param hash hash_tʵ��
 * @param key �ַ�����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int hash_delete_string_key(hash_t* hash, const char* key);

/*
 * ��ȡԪ��
 * @param hash hash_tʵ��
 * @param key ��
 * @retval 0 δ�ҵ�
 * @retval ��Чָ��
 */
void* hash_get(hash_t* hash, uint32_t key);

/*
 * ��ȡԪ��
 * @param hash hash_tʵ��
 * @param key �ַ�����
 * @retval 0 δ�ҵ�
 * @retval ��Чָ��
 */
void* hash_get_string_key(hash_t* hash, const char* key);

/*
 * ȡ��Ԫ������
 * @param hash hash_tʵ��
 * @return Ԫ������
 */
uint32_t hash_get_size(hash_t* hash);

/*
 * ���ñ�������ȡ��һ��Ԫ��
 * @param hash hash_tʵ��
 * @retval 0 û��Ԫ��
 * @retval hash_value_tʵ��
 */
hash_value_t* hash_get_first(hash_t* hash);

/*
 * ��ϣ�����������һ��Ԫ��
 * @param hash hash_tʵ��
 * @retval 0 û��Ԫ��
 * @retval hash_value_tʵ��
 */
hash_value_t* hash_next(hash_t* hash);

/* ������ϣ�������ڱ���������ɾ�������ٵ�ǰԪ�� */
#define hash_for_each_safe(hash, value) \
    for (value = hash_get_first(hash); (value); value = hash_get_next(hash))

#endif /* HASH_H */
