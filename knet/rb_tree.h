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
