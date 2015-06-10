#ifndef TIMER_API_H
#define TIMER_API_H

#include "config.h"

/*
 * WARNING δ�����ԣ���Ҫ�Ȳ������
 */

/*
 * ������ʱ��ѭ��
 * @param freq ��С�ֱ��ʣ����룩
 * @param slot ʱ���ֲ�λ����
 * @return timer_loop_tʵ��
 */
timer_loop_t* timer_loop_create(time_t freq, int slot);

/*
 * ���ٶ�ʱ��ѭ��
 * @return timer_loop_tʵ��
 */
void timer_loop_destroy(timer_loop_t* timer_loop);

/*
 * ��鶨ʱ����ʱ�������ʱ���ö�ʱ���ص�
 * @return timer_loop_tʵ��
 * @return ��ʱ����ʱ������
 */
int timer_loop_run_once(timer_loop_t* timer_loop);

/*
 * ����һ����ʱ��
 * @param timer_loop_tʵ��
 * @return timer_tʵ��
 */
timer_t* timer_create(timer_loop_t* timer_loop);

/*
 * ֹͣ�����ٶ�ʱ��
 * @param timer_loop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int timer_stop(timer_t* timer);

/*
 * ����һ�����޴����Ķ�ʱ��
 * @param timer timer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int timer_start(timer_t* timer, timer_cb_t cb, void* data, time_t ms);

/*
 * ����һ��ֻ��ʱһ�εĶ�ʱ������ʱ���Զ�����
 * @param timer timer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int timer_start_once(timer_t* timer, timer_cb_t cb, void* data, time_t ms);

/*
 * ����һ�����޴����Ķ�ʱ�����ﵽtimes�������Զ�����
 * @param timer timer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @param times ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int timer_start_times(timer_t* timer, timer_cb_t cb, void* data, time_t ms, int times);

/*
 * ��鶨ʱ���Ƿ��ڻص��������ؼ���������
 * @param timer timer_tʵ��
 * @retval 0 ����
 * @retval ���� ��
 */
int timer_check_dead(timer_t* timer);

#endif /* TIMER_API_H */
