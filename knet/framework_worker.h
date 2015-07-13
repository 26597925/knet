#ifndef FRAMEWORK_WORKER_H
#define FRAMEWORK_WORKER_H

#include "config.h"

/**
 * ������ܹ����߳�
 * @param f framework_tʵ��
 * @return framework_worker_tʵ��
 */
framework_worker_t* framework_worker_create(framework_t* f);

/**
 * ���ٿ�ܹ����߳�
 * @param w framework_worker_tʵ��
 */
void framework_worker_destroy(framework_worker_t* w);

/**
 * ������ܹ����߳�
 * @param w framework_worker_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int framework_worker_start(framework_worker_t* w);

/**
 * �رտ�ܹ����߳�
 * @param w framework_worker_tʵ��
 */
void framework_worker_stop(framework_worker_t* w);

#endif /* FRAMEWORK_WORKER_H */
