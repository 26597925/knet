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
 * thread_runner_start_loop����ֱ����kloop_t��Ϊ�������߳�������knet_loop_run_once
 * thread_runner_start_timer_loop����ֱ����ktimer_loop_t��Ϊ�������߳�������ktimer_loop_run_once
 * thread_runner_start_multi_loop_varg����ͬʱ���ж��knet_loop_run_once����ktimer_loop_run_once
 * </pre>
 * @{
 */

/**
 * ����һ���߳�
 * @param func �̺߳���
 * @param params ����
 * @return kthread_runner_tʵ��
 */
extern kthread_runner_t* thread_runner_create(knet_thread_func_t func, void* params);

/**
 * ����һ���߳�
 * @param runner kthread_runner_tʵ��
 */
extern void thread_runner_destroy(kthread_runner_t* runner);

/**
 * �����߳�
 * @param runner kthread_runner_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start(kthread_runner_t* runner, int stack_size);

/**
 * ֹͣ�߳�
 * @param runner kthread_runner_tʵ��
 */
extern void thread_runner_stop(kthread_runner_t* runner);

/**
 * ��ȡ�߳�ID
 * @param runner kthread_runner_tʵ��
 * @return �߳�ID
 */
extern thread_id_t thread_runner_get_id(kthread_runner_t* runner);

/**
 * ���߳�������knet_loop_run()
 * @param runner kthread_runner_tʵ��
 * @param loop kloop_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start_loop(kthread_runner_t* runner, kloop_t* loop, int stack_size);

/**
 * ���߳�������timer_loop_run()
 * @param runner kthread_runner_tʵ��
 * @param timer_loop ktimer_loop_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start_timer_loop(kthread_runner_t* runner, ktimer_loop_t* timer_loop, int stack_size);

/**
 * ���߳����������kloop_t��ktimer_loop_t
 *
 * format�ڿ����ж��kloop_t��l������ktimer_loop_t��t����Ʃ�磺lt����ʶһ��kloop_t��һ��ktimer_loop_t
 * @param runner kthread_runner_tʵ��
 * @param stack_size ջ��С
 * @param format �����ַ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start_multi_loop_varg(kthread_runner_t* runner, int stack_size, const char* format, ...);

/**
 * �ȴ��߳���ֹ
 * @param runner kthread_runner_tʵ��
 */
extern void thread_runner_join(kthread_runner_t* runner);

/**
 * ��ֹ�߳�
 * @param runner kthread_runner_tʵ��
 */
extern void thread_runner_exit(kthread_runner_t* runner);

/**
 * ����߳��Ƿ���������
 * @param runner kthread_runner_tʵ��
 * @retval 0 δ����
 * @retval ���� ��������
 */
extern int thread_runner_check_start(kthread_runner_t* runner);

/**
 * ȡ���߳����в�����thread_runner_create()�ڶ�������
 * @param runner kthread_runner_tʵ��
 * @return �߳����в���
 */
extern void* thread_runner_get_params(kthread_runner_t* runner);

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
 * @param runner kthread_runner_tʵ��
 * @param data �Զ�������ָ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int thread_set_tls_data(kthread_runner_t* runner, void* data);

/**
 * ȡ���̱߳��ش洢
 * @param runner kthread_runner_tʵ��
 * @retval 0 ��ȡʧ�ܻ򲻴���
 * @retval ��Чָ��
 */
void* thread_get_tls_data(kthread_runner_t* runner);

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
 * ԭ�Ӳ��� - CAS(check and swap)
 * @param counter atomic_counter_tʵ��
 * @param target Ŀ��ֵ
 * @param value ��ֵ
 * @return �������ֵ
 */
extern atomic_counter_t atomic_counter_cas(atomic_counter_t* counter,
    atomic_counter_t target, atomic_counter_t value);

/**
 * ԭ�Ӳ��� - ��ֵ
 * @param counter atomic_counter_tʵ��
 * @param value ��ֵ
 * @return �������ֵ
 */
extern atomic_counter_t atomic_counter_set(atomic_counter_t* counter,
    atomic_counter_t value);

/**
 * ԭ�Ӳ��� - �Ƿ�Ϊ��
 * @param counter atomic_counter_tʵ��
 * @retval 0 ����
 * @retval ���� ��
 */
extern int atomic_counter_zero(atomic_counter_t* counter);

/**
 * ����������ʵ��
 * @return klock_tʵ��
 */
extern klock_t* lock_create();

/**
 * ���ٻ�����
 * @param lock klock_tʵ��
 */
extern void lock_destroy(klock_t* lock);

/**
 * ��
 * @param lock klock_tʵ��
 */
extern void lock_lock(klock_t* lock);

/**
 * ������
 * @param lock klock_tʵ��
 * @sa pthread_mutex_trylock
 */
extern int lock_trylock(klock_t* lock);

/**
 * ����
 * @param lock klock_tʵ��
 */
extern void lock_unlock(klock_t* lock);

/**
 * ������д��
 * @return krwlock_tʵ��
 */
extern krwlock_t* rwlock_create();

/**
 * ���ٶ�д��
 * @param rwlock krwlock_tʵ��
 */
extern void rwlock_destroy(krwlock_t* rwlock);

/**
 * ������
 * @param rwlock krwlock_tʵ��
 */
extern void rwlock_rdlock(krwlock_t* rwlock);

/**
 * ���߽���
 * @param rwlock krwlock_tʵ��
 */
extern void rwlock_rdunlock(krwlock_t* rwlock);

/**
 * д����
 * @param rwlock krwlock_tʵ��
 */
extern void rwlock_wrlock(krwlock_t* rwlock);

/**
 * д�߽���
 * @param rwlock krwlock_tʵ��
 */
extern void rwlock_wrunlock(krwlock_t* rwlock);

/**
 * ������������
 * @return kcond_tʵ��
 */
extern kcond_t* cond_create();

/**
 * ������������
 * @param cond kcond_tʵ��
 */
extern void cond_destroy(kcond_t* cond);

/**
 * �ȴ�����
 * @param cond kcond_tʵ��
 * @param lock ��
 */
extern void cond_wait(kcond_t* cond, klock_t* lock);

/**
 * �ȴ�����
 * @param cond kcond_tʵ��
 * @param lock ��
 * @param ms �ȴ�ʱ�䣨���룩
 */
extern void cond_wait_ms(kcond_t* cond, klock_t* lock, int ms);

/**
 * ����
 * @param cond kcond_tʵ��
 */
extern void cond_signal(kcond_t* cond);

/** @} */

#endif /* THREAD_API_H */
