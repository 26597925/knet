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

#ifndef THREAD_API_H
#define THREAD_API_H

#include "config.h"

/**
 * @defgroup thread �߳�
 * �߳����
 *
 * <pre>
 * �߳�
 *
 * �߳�API�ṩ�˻������߳���ز���:
 *
 * 1. �߳̽�������
 * 2. TLS
 * 3. ԭ�Ӳ���
 *
 * thread_runner_start_loop����ֱ����loop_t��Ϊ�������߳�������loop_run
 * thread_runner_start_timer_loop����ֱ����ktimer_loop_t��Ϊ�������߳�������ktimer_loop_run
 *
 * </pre>
 * @{
 */

/**
 * ����һ���߳�
 * @param func �̺߳���
 * @param params ����
 * @return thread_runner_tʵ��
 */
extern thread_runner_t* thread_runner_create(thread_func_t func, void* params);

/**
 * ����һ���߳�
 * @param runner thread_runner_tʵ��
 */
extern void thread_runner_destroy(thread_runner_t* runner);

/**
 * �����߳�
 * @param runner thread_runner_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start(thread_runner_t* runner, int stack_size);

/**
 * ֹͣ�߳�
 * @param runner thread_runner_tʵ��
 */
extern void thread_runner_stop(thread_runner_t* runner);

/**
 * ���߳�������loop_run()
 * @param runner thread_runner_tʵ��
 * @param loop loop_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start_loop(thread_runner_t* runner, loop_t* loop, int stack_size);

/**
 * ���߳�������timer_loop_run()
 * @param runner thread_runner_tʵ��
 * @param timer_loop ktimer_loop_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start_timer_loop(thread_runner_t* runner, ktimer_loop_t* timer_loop, int stack_size);

/**
 * �ȴ��߳���ֹ
 * @param runner thread_runner_tʵ��
 */
extern void thread_runner_join(thread_runner_t* runner);

/**
 * ����߳��Ƿ���������
 * @param runner thread_runner_tʵ��
 * @retval 0 δ����
 * @retval ���� ��������
 */
extern int thread_runner_check_start(thread_runner_t* runner);

/**
 * ȡ���߳����в�����thread_runner_create()�ڶ�������
 * @param runner thread_runner_tʵ��
 * @return �߳����в���
 */
extern void* thread_runner_get_params(thread_runner_t* runner);

/**
 * ȡ���߳�ID
 * @return �߳�ID
 */
extern thread_id_t thread_get_self_id();

/**
 * ˯��
 * @param ms ˯��ʱ�䣨���룩
 */
extern void thread_sleep_ms(int ms);

/**
 * �����̱߳��ش洢
 * @param runner thread_runner_tʵ��
 * @param data �Զ�������ָ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int thread_set_tls_data(thread_runner_t* runner, void* data);

/**
 * ȡ���̱߳��ش洢
 * @param runner thread_runner_tʵ��
 * @retval 0 ��ȡʧ�ܻ򲻴���
 * @retval ��Чָ��
 */
void* thread_get_tls_data(thread_runner_t* runner);

/**
 * ԭ�Ӳ��� - ����
 * @param counter atomic_counter_tʵ��
 * @return �������ֵ
 */
extern atomic_counter_t atomic_counter_inc(atomic_counter_t* counter);

/**
 * ԭ�Ӳ��� - �ݼ�
 * @param counter atomic_counter_tʵ��
 * @return �ݼ����ֵ
 */
extern atomic_counter_t atomic_counter_dec(atomic_counter_t* counter);

/**
 * ԭ�Ӳ��� - �Ƿ�Ϊ��
 * @param counter atomic_counter_tʵ��
 * @retval 0 ����
 * @retval ���� ��
 */
extern int atomic_counter_zero(atomic_counter_t* counter);

/** @} */

#endif /* THREAD_API_H */
