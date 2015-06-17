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
 * @retval ��Чָ�� ֵ
 */
void* hash_get(hash_t* hash, uint32_t key);

/*
 * ��ȡԪ��
 * @param hash hash_tʵ��
 * @param key �ַ�����
 * @retval 0 δ�ҵ�
 * @retval ��Чָ�� ֵ
 */
void* hash_get_string_key(hash_t* hash, const char* key);

/*
 * ȡ��Ԫ������
 * @param hash hash_tʵ��
 * @return Ԫ������
 */
uint32_t hash_get_size(hash_t* hash);

#endif /* HASH_H */
