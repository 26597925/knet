/*
 * Copyright (c) 2014-2016, dennis wang
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

#ifndef TRIE_API_H
#define TRIE_API_H

#include "config.h"

/**
 * @defgroup trie �ַ���KV��
 * �ַ�����
 * <pre>
 * �ṩһ����·���ṹ���ڿ��ٲ����ַ�������·���ֱ�Ϊ{left, center, right}��
 * ����left < center < right�����ң�ɾ��������Ч��ΪO(n)��nΪ�ַ�������.
 * �ַ�����ʹ���ַ�����Ϊ����void*������Ϊֵ��Ҳ������Ϊ��ϣ��ʹ�ã��û������ṩ
 * һ��ֵ���ٺ�������trie������ʱ���Զ���ֵ����ص�.
 * </pre>
 * @{
 */

/**
 * ����trie
 * @return ktrie_tʵ��
 */
extern ktrie_t* trie_create();

/**
 * ����trie
 * @param trie ktrie_tʵ��
 * @param dtor ���ٺ���
 */
extern void trie_destroy(ktrie_t* trie, knet_trie_dtor_t dtor);

/**
 * ����trie
 * @param trie ktrie_tʵ��
 * @param s ��
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int trie_insert(ktrie_t* trie, const char* s, void* value);

/**
 * ����
 * @param trie ktrie_tʵ��
 * @param s ��
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int trie_find(ktrie_t* trie, const char* s, void** value);

/**
 * ɾ��
 * @param trie ktrie_tʵ��
 * @param s ��
 * @param value ֵ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int trie_remove(ktrie_t* trie, const char* s, void** value);

/**
 * ����
 * @param trie ktrie_tʵ��
 * @param func ��������
 * @param param ������������
 */
extern int trie_for_each(ktrie_t* trie, knet_trie_for_each_func_t func, void* param);

/** @} */

#endif /* TRIE_API_H */
