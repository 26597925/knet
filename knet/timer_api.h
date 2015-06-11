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
 * @return ktimer_loop_tʵ��
 */
extern ktimer_loop_t* ktimer_loop_create(time_t freq, int slot);

/*
 * ���ٶ�ʱ��ѭ��
 * @return ktimer_loop_tʵ��
 */
extern void ktimer_loop_destroy(ktimer_loop_t* ktimer_loop);

/*
 * ��鶨ʱ����ʱ�������ʱ���ö�ʱ���ص�
 * @return ktimer_loop_tʵ��
 * @return ��ʱ����ʱ������
 */
extern int ktimer_loop_run_once(ktimer_loop_t* ktimer_loop);

/*
 * ѭ����鶨ʱ����ʱ������ktimer_loop_exit()�˳�
 * @return ktimer_loop_tʵ��
 */
extern void ktimer_loop_run(ktimer_loop_t* ktimer_loop);

/*
 * �˳�ktimer_loop_run()
 * @return ktimer_loop_tʵ��
 */
extern void ktimer_loop_exit(ktimer_loop_t* ktimer_loop);

/*
 * ����һ����ʱ��
 * @param ktimer_loop_tʵ��
 * @return kktimer_tʵ��
 */
extern kktimer_t* ktimer_create(ktimer_loop_t* ktimer_loop);

/*
 * ֹͣ�����ٶ�ʱ��
 * @param ktimer_loop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ktimer_stop(kktimer_t* timer);

/*
 * ȡ��ktimer_loop_tʵ��
 * @param timer kktimer_tʵ��
 * @return ktimer_loop_tʵ��
 */
extern ktimer_loop_t* ktimer_get_loop(kktimer_t* timer);

/*
 * ����һ�����޴����Ķ�ʱ��
 * @param timer kktimer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ktimer_start(kktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms);

/*
 * ����һ��ֻ��ʱһ�εĶ�ʱ������ʱ���Զ�����
 * @param timer kktimer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ktimer_start_once(kktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms);

/*
 * ����һ�����޴����Ķ�ʱ�����ﵽtimes�������Զ�����
 * @param timer kktimer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @param times ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ktimer_start_times(kktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms, int times);

/*
 * ��鶨ʱ���Ƿ��ڻص��������ؼ���������
 * @param timer kktimer_tʵ��
 * @retval 0 ����
 * @retval ���� ��
 */
extern int ktimer_check_dead(kktimer_t* timer);

#endif /* TIMER_API_H */
