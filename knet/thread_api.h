#ifndef THREAD_API_H
#define THREAD_API_H

#include "config.h"

/*
 * ����һ���߳�
 * @param func �̺߳���
 * @param params ����
 * @return thread_runner_tʵ��
 */
extern thread_runner_t* thread_runner_create(thread_func_t func, void* params);

/*
 * ����һ���߳�
 * @param runner thread_runner_tʵ��
 */
extern void thread_runner_destroy(thread_runner_t* runner);

/*
 * �����߳�
 * @param runner thread_runner_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start(thread_runner_t* runner, int stack_size);

/*
 * ֹͣ�߳�
 * @param runner thread_runner_tʵ��
 */
extern void thread_runner_stop(thread_runner_t* runner);

/*
 * ���߳�������loop_run()
 * @param runner thread_runner_tʵ��
 * @param loop loop_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start_loop(thread_runner_t* runner, loop_t* loop, int stack_size);

/*
 * ���߳�������timer_loop_run()
 * @param runner thread_runner_tʵ��
 * @param timer_loop ktimer_loop_tʵ��
 * @param stack_size �߳�ջ��С���ֽڣ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int thread_runner_start_timer_loop(thread_runner_t* runner, ktimer_loop_t* timer_loop, int stack_size);

/*
 * �ȴ��߳���ֹ
 * @param runner thread_runner_tʵ��
 */
extern void thread_runner_join(thread_runner_t* runner);

/*
 * ����߳��Ƿ���������
 * @param runner thread_runner_tʵ��
 * @retval 0 δ����
 * @retval ���� ��������
 */
extern int thread_runner_check_start(thread_runner_t* runner);

/*
 * ȡ���߳����в�����thread_runner_create()�ڶ�������
 * @param runner thread_runner_tʵ��
 * @return �߳����в���
 */
extern void* thread_runner_get_params(thread_runner_t* runner);

/*
 * ȡ���߳�ID
 * @param runner thread_runner_tʵ��
 * @return �߳�ID
 */
extern thread_id_t thread_get_self_id();

/*
 * ˯��
 * @param ms ˯��ʱ�䣨���룩
 */
extern void thread_sleep_ms(int ms);

/*
 * ԭ�Ӳ��� - ����
 * @param counter atomic_counter_tʵ��
 * @return �������ֵ
 */
extern atomic_counter_t atomic_counter_inc(atomic_counter_t* counter);

/*
 * ԭ�Ӳ��� - �ݼ�
 * @param counter atomic_counter_tʵ��
 * @return �ݼ����ֵ
 */
extern atomic_counter_t atomic_counter_dec(atomic_counter_t* counter);

/*
 * ԭ�Ӳ��� - �Ƿ�Ϊ��
 * @param counter atomic_counter_tʵ��
 * @retval 0 ����
 * @retval ���� ��
 */
extern int atomic_counter_zero(atomic_counter_t* counter);

#endif /* THREAD_API_H */
