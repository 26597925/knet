#ifndef BROADCAST_API_H
#define BROADCAST_API_H

#include "config.h"

/*
 * �����㲥��
 * @return broadcast_tʵ��
 */
broadcast_t* broadcast_create();

/*
 * ���ٹ㲥��
 * @param broadcast broadcast_tʵ��
 */
void broadcast_destroy(broadcast_t* broadcast);

/*
 * ����㲥��
 * ����ɹ�������һ���µ�����
 * @param broadcast broadcast_tʵ��
 * @param channel_ref channel_ref_t
 * @return channel_ref_tʵ�����µ��ڹ㲥���ڵ�����
 */
channel_ref_t* broadcast_join(broadcast_t* broadcast, channel_ref_t* channel_ref);

/*
 * �뿪�㲥��
 * @param broadcast broadcast_tʵ��
 * @param channel_ref channel_ref_tʵ������broadcast_join()����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int broadcast_leave(broadcast_t* broadcast, channel_ref_t* channel_ref);

/*
 * ȡ�ù㲥���ڹܵ�����
 * @param broadcast broadcast_tʵ��
 * @return �ܵ�����
 */
int broadcast_get_count(broadcast_t* broadcast);

/*
 * �㲥
 * @param broadcast broadcast_tʵ��
 * @param buffer ������ָ��
 * @param size ����������
 * @return ���ͳɹ��ܵ�������
 */
int broadcast_write(broadcast_t* broadcast, char* buffer, uint32_t size);

#endif /* BROADCAST_API_H */
