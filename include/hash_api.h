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

#ifndef HASH_API_H
#define HASH_API_H

#include "config.h"

/*
 * ��ϣ��ͬʱ֧�����ֻ��ַ�����Ϊkey
 */

/**
 * ȡ���Զ���ֵ
 * @param hash_value khash_value_tʵ��
 * @return �Զ���ֵ
 */
extern void* hash_value_get_value(khash_value_t* hash_value);

/**
 * ȡ�����ּ�
 * @param hash_value khash_value_tʵ��
 * @return ���ּ�
 */
extern uint32_t hash_value_get_key(khash_value_t* hash_value);

/**
 * ȡ���ַ�����
 * @param hash_value khash_value_tʵ��
 * @return �ַ�����
 */
extern const char* hash_value_get_string_key(khash_value_t* hash_value);

/**
 * ������ϣ��
 * @param size ��ϣ��Ͱ����, 0��ʹ��Ĭ��Ͱ����
 * @param dtor �û��Զ���ֵ���ٺ���
 * @return khash_tʵ��
 */
extern khash_t* hash_create(uint32_t size, knet_hash_dtor_t dtor);

/**
 * ���ٹ�ϣ��
 * @param hash khash_tʵ��
 */
extern void hash_destroy(khash_t* hash);

/**
 * ���Ԫ��
 * @param hash khash_tʵ��
 * @param key ��
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int hash_add(khash_t* hash, uint32_t key, void* value);

/**
 * ���Ԫ��
 * @param hash khash_tʵ��
 * @param key �ַ�����
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int hash_add_string_key(khash_t* hash, const char* key, void* value);

/**
 * �Ƴ�Ԫ��
 * @param hash khash_tʵ��
 * @param key ��
 * @retval 0 δ�ҵ�
 * @retval ��Чָ�� ֵ
 */
extern void* hash_remove(khash_t* hash, uint32_t key);

/**
 * �Ƴ�Ԫ��
 * @param hash khash_tʵ��
 * @param key �ַ�����
 * @retval 0 δ�ҵ�
 * @retval ��Чָ�� ֵ
 */
extern void* hash_remove_string_key(khash_t* hash, const char* key);

/**
 * ����Ԫ��
 * @param hash khash_tʵ��
 * @param key ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int hash_delete(khash_t* hash, uint32_t key);

/**
 * �滻
 * @param hash khash_tʵ��
 * @param key ��
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int hash_replace(khash_t* hash, uint32_t key, void* value);

/**
 * �滻
 * @param hash khash_tʵ��
 * @param key �ַ�����
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int hash_replace_string_key(khash_t* hash, const char* key, void* value);

/**
 * ����Ԫ��
 * @param hash khash_tʵ��
 * @param key �ַ�����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int hash_delete_string_key(khash_t* hash, const char* key);

/**
 * ��ȡԪ��
 * @param hash khash_tʵ��
 * @param key ��
 * @retval 0 δ�ҵ�
 * @retval ��Чָ��
 */
extern void* hash_get(khash_t* hash, uint32_t key);

/**
 * ��ȡԪ��
 * @param hash khash_tʵ��
 * @param key �ַ�����
 * @retval 0 δ�ҵ�
 * @retval ��Чָ��
 */
extern void* hash_get_string_key(khash_t* hash, const char* key);

/**
 * ȡ��Ԫ������
 * @param hash khash_tʵ��
 * @return Ԫ������
 */
extern uint32_t hash_get_size(khash_t* hash);

/**
 * ���ñ�������ȡ��һ��Ԫ��
 * @param hash khash_tʵ��
 * @retval 0 û��Ԫ��
 * @retval khash_value_tʵ��
 */
extern khash_value_t* hash_get_first(khash_t* hash);

/**
 * ��ϣ�����������һ��Ԫ��
 * @param hash khash_tʵ��
 * @retval 0 û��Ԫ��
 * @retval khash_value_tʵ��
 */
extern khash_value_t* hash_next(khash_t* hash);

/* ������ϣ�������ڱ���������ɾ�������ٵ�ǰԪ��, �����겻���̰߳�ȫ�� */
#define hash_for_each_safe(hash, value) \
    for (value = hash_get_first(hash); (value); value = hash_next(hash))

#endif /* HASH_API_H */
