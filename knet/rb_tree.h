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

#ifndef RB_TREE_H
#define RB_TREE_H

#include "config.h"

/**
 * ����������ڵ�
 * @param key �ڵ��
 * @param ptr �ڵ��û�����ָ��
 * @param cb ���ٻص�����ָ��
 * @return �½����Ľڵ�
 */
krbnode_t* krbnode_create(uint64_t key, void* ptr, knet_rb_node_destroy_cb_t cb);

/**
 * ���ٺ�����ڵ�
 * @param node �ڵ�
 */
void krbnode_destroy(krbnode_t* node);

/**
 * ��ȡ�ڵ��
 * @param node �ڵ�
 * @return ��
 */
uint64_t krbnode_get_key(krbnode_t* node);

/**
 * ��ȡ�ڵ��û�����ָ��
 * @param node �ڵ�
 * @return �û�����ָ��
 */
void* krbnode_get_ptr(krbnode_t* node);

/**
 * ���������
 * @return �����
 */
krbtree_t* krbtree_create();

/**
 * ���ٺ����
 * @param tree �����
 */
void krbtree_destroy(krbtree_t* tree);

/**
 * ���������ڵ�
 * @param tree �����
 * @param node �ڵ�
 */
void krbtree_insert(krbtree_t* tree, krbnode_t* node);

/**
 * ���ҽڵ�
 * @param tree �����
 * @param key ��
 * @return �ڵ�
 */
krbnode_t* krbtree_find(krbtree_t* tree, uint64_t key);

/**
 * ���ٽڵ�
 * @param tree �����
 * @param node �ڵ�
 */
void krbtree_delete(krbtree_t* tree, krbnode_t* node);

/**
 * ������С���Ľڵ�
 * @param tree �����
 * @return �ڵ�
 */
krbnode_t* krbtree_min(krbtree_t* tree);

/**
 * ���������Ľڵ�
 * @param tree �����
 * @return �ڵ�
 */
krbnode_t* krbtree_max(krbtree_t* tree);

#endif /* RB_TREE_H */
