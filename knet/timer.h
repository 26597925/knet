#ifndef TIMER_H
#define TIMER_H

#include "config.h"
#include "timer_api.h"

/*
 * ���ٶ�ʱ��
 * @param timer ktimer_tʵ��
 */
void ktimer_destroy(ktimer_t* timer);

/*
 * ��鶨ʱ���Ƿ�ʱ
 * @param timer ktimer_tʵ��
 * @param ms ��ǰʱ���
 * @retval 0 û�г�ʱ
 * @retval ���� ��ʱ
 */
int ktimer_check_timeout(ktimer_t* timer, time_t ms);

/*
 * ���ö�ʱ�����ڵĵ�ǰ����
 * @param timer ktimer_tʵ��
 * @param list ����
 */
void ktimer_set_current_list(ktimer_t* timer, dlist_t* list);

/*
 * ȡ�õ�ǰ��������
 * @param timer ktimer_tʵ��
 * @return dlist_tʵ��
 */
dlist_t* ktimer_get_current_list(ktimer_t* timer);

/*
 * ���ö�ʱ�����ڵĵ�ǰ���������ڵ�
 * @param timer ktimer_tʵ��
 * @param node ����ڵ�
 */
void ktimer_set_current_list_node(ktimer_t* timer, dlist_node_t* node);

/*
 * ȡ�õ�ǰ����ڵ�
 * @param timer ktimer_tʵ��
 * @return dlist_node_tʵ��
 */
dlist_node_t* ktimer_get_current_list_node(ktimer_t* timer);

/*
 * ȡ�õδ���
 * @param ktimer_loop ktimer_loop_tʵ��
 * @return �δ���
 */
time_t ktimer_loop_get_tick_intval(ktimer_loop_t* ktimer_loop);

#endif /* TIMER_H */
