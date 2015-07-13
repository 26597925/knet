#ifndef FRAMEWORK_H
#define FRAMEWORK_H

#include "framework_api.h"

/**
 * �������������
 * @return framework_config_tʵ��
 */
framework_config_t* framework_config_create();

/**
 * ���ٿ��������
 * @param c framework_config_tʵ��
 */
void framework_config_destroy(framework_config_t* c);

/**
 * ��ȡIP
 * @param c framework_config_tʵ��
 * @return IP
 */
const char* framework_config_get_ip(framework_config_t* c);

/**
 * ��ȡ�����˿�
 * @param c framework_config_tʵ��
 * @return �����˿�
 */
int framework_config_get_port(framework_config_t* c);

/**
 * ��ȡbacklog
 * @param c framework_config_tʵ��
 * @return backlog
 */
int framework_config_get_backlog(framework_config_t* c);

/**
 * ��ȡ�����߳�����
 * @param c framework_config_tʵ��
 * @return �����߳�����
 */
int framework_config_get_worker_thread_count(framework_config_t* c);

/**
 * ��ȡ�����������Ԫ����
 * @param c framework_config_tʵ��
 * @return �����������Ԫ����
 */
int framework_config_get_max_send_list(framework_config_t* c);

/**
 * ��ȡ���ջ�������󳤶�
 * @param c framework_config_tʵ��
 * @return ���ջ�������󳤶�
 */
int framework_config_get_max_recv_buffer(framework_config_t* c);

/**
 * �¼�channel_cb_event_accept������
 * @param channel �����ܵ���channel_ref_tʵ��
 * @param e �ܵ��¼�
 */
void acceptor_cb(channel_ref_t* channel, channel_cb_event_e e);

/**
 * ��ȡ���ؾ�����
 * @param f framework_tʵ��
 * @return loop_balancer_tʵ��
 */
loop_balancer_t* framework_get_balancer(framework_t* f);

/**
 * ��ȡ�ܵ��ص�
 * @param f framework_tʵ��
 * @return �ܵ��ص�����ָ��
 */
channel_ref_cb_t framework_get_cb(framework_t* f);

#endif /* FRAMEWORK_H */
