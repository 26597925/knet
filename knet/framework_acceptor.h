#ifndef FRAMEWORK_ACCEPTOR_H
#define FRAMEWORK_ACCEPTOR_H

#include "config.h"

/**
 * ����������������
 * @param f framework_tʵ��
 * @return framework_acceptor_tʵ��
 */
framework_acceptor_t* framework_acceptor_create(framework_t* f);

/**
 * ���ٿ�����������
 * @param a framework_acceptor_tʵ��
 */
void framework_acceptor_destroy(framework_acceptor_t* a);

/**
 * ����������������
 * @param a framework_acceptor_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int framework_acceptor_start(framework_acceptor_t* a);

/**
 * �رտ�����������
 * @param a framework_acceptor_tʵ��
 */
void framework_acceptor_stop(framework_acceptor_t* a);

/**
 * �ȴ��������������ر�
 * @param a framework_acceptor_tʵ��
 */
void framework_acceptor_wait_for_stop(framework_acceptor_t* a);

#endif /* FRAMEWORK_ACCEPTOR_H */
