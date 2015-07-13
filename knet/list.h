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

#ifndef LIST_H
#define LIST_H

#include "config.h"

/**
 * ��������ڵ�
 * @return dlist_node_tʵ��
 */
dlist_node_t* dlist_node_create();

/**
 * ��ʼ������ڵ�
 * @param node dlist_node_tʵ��
 * @return dlist_node_tʵ��
 */
dlist_node_t* dlist_node_init(dlist_node_t* node);

/**
 * ��������ڵ�
 * @param node dlist_node_tʵ��
 */
void dlist_node_destroy(dlist_node_t* node);

/**
 * ���ýڵ��Զ�������
 * @param node dlist_node_tʵ��
 * @param data �Զ�������ָ��
 * @return dlist_node_tʵ��
 */
dlist_node_t* dlist_node_set_data(dlist_node_t* node, void* data);

/**
 * ȡ�ýڵ��Զ�������
 * @param node dlist_node_tʵ��
 * @return �Զ�������ָ��
 */
void* dlist_node_get_data(dlist_node_t* node);

/**
 * ��������
 * @return dlist_tʵ��
 */
dlist_t* dlist_create();

/**
 * ��ʼ������
 * @param dlist dlist_tʵ��
 * @return dlist_tʵ��
 */
dlist_t* dlist_init(dlist_t* dlist);

/**
 * ���������������������нڵ㣨�����ٽڵ����Զ������ݣ�
 * @param dlist dlist_tʵ��
 */
void dlist_destroy(dlist_t* dlist);

/**
 * ���ڵ���ӵ�����ͷ��
 * @param dlist dlist_tʵ��
 * @param node dlist_node_tʵ��
 */
void dlist_add_front(dlist_t* dlist, dlist_node_t* node);

/**
 * ���ڵ���ӵ�����β��
 * @param dlist dlist_tʵ��
 * @param node dlist_node_tʵ��
 */
void dlist_add_tail(dlist_t* dlist, dlist_node_t* node);

/**
 * �����½ڵ㲢��ӵ�����ͷ����ͬʱ���ýڵ��Զ�������
 * @param dlist dlist_tʵ��
 * @param data �Զ�������ָ��
 * @return dlist_node_tʵ��
 */
dlist_node_t* dlist_add_front_node(dlist_t* dlist, void* data);

/**
 * �����½ڵ㲢��ӵ�����β����ͬʱ���ýڵ��Զ�������
 * @param dlist dlist_tʵ��
 * @param data �Զ�������ָ��
 * @return dlist_node_tʵ��
 */
dlist_node_t* dlist_add_tail_node(dlist_t* dlist, void* data);

/**
 * ȡ������ڵ�����
 * @param dlist dlist_tʵ��
 * @return �ڵ�����
 */
int dlist_get_count(dlist_t* dlist);

/**
 * ��
 * @param dlist dlist_tʵ��
 * @retval 0 �ǿ�
 * @retval ���� ��
 */
int dlist_empty(dlist_t* dlist);

/**
 * ���ڵ���������Ƴ���������
 * @param dlist dlist_tʵ��
 * @param node ��ǰ�ڵ�
 * @retval dlist_node_tʵ��
 */
dlist_node_t* dlist_remove(dlist_t* dlist, dlist_node_t* node);

/**
 * ��������ڵ�
 * @param dlist dlist_tʵ��
 * @param node ��ǰ�ڵ�
 */
void dlist_delete(dlist_t* dlist, dlist_node_t* node);

/**
 * ȡ����ͷ��ǰ�ڵ����һ���ڵ�
 * @param dlist dlist_tʵ��
 * @param node ��ǰ�ڵ�
 * @retval dlist_node_tʵ��
 * @retval 0 û�и���ڵ�
 */
dlist_node_t* dlist_next(dlist_t* dlist, dlist_node_t* node);

/**
 * ȡ����ͷ�ڵ�
 * @param dlist dlist_tʵ��
 * @retval dlist_node_tʵ��
 * @retval 0 ����Ϊ��
 */
dlist_node_t* dlist_get_front(dlist_t* dlist);

/**
 * ȡ������β�ڵ�
 * @param dlist dlist_tʵ��
 * @retval dlist_node_tʵ��
 * @retval 0 ����Ϊ��
 */
dlist_node_t* dlist_get_back(dlist_t* dlist);

/* ���������ڱ�����ͬʱ����ɾ������������ڵ� */
#define dlist_for_each(list, node) \
    for (node = dlist_get_front(list); (node); node = dlist_next(list, node))

/* �������������ڱ���ͬʱ����ɾ������������ڵ� */
#define dlist_for_each_safe(list, node, temp) \
    for (node = dlist_get_front(list), temp = dlist_next(list, node); (node); node = temp, temp = dlist_next(list, node))

#define dlist_for_each_break() \
    break

#endif /* LIST_H */
