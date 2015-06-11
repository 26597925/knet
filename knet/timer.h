#ifndef TIMER_H
#define TIMER_H

#include "config.h"
#include "timer_api.h"

/*
 * ���ٶ�ʱ��
 * @param timer timer_tʵ��
 */
void timer_destroy(timer_t* timer);

/*
 * ��鶨ʱ���Ƿ�ʱ
 * @param timer timer_tʵ��
 * @param ms ��ǰʱ���
 * @retval 0 û�г�ʱ
 * @retval ���� ��ʱ
 */
int timer_check_timeout(timer_t* timer, time_t ms);

/*
 * ���ö�ʱ�����ڵĵ�ǰ����
 * @param timer timer_tʵ��
 * @param list ����
 */
void timer_set_current_list(timer_t* timer, dlist_t* list);

/*
 * ȡ�õ�ǰ��������
 * @param timer timer_tʵ��
 * @return dlist_tʵ��
 */
dlist_t* timer_get_current_list(timer_t* timer);

/*
 * ���ö�ʱ�����ڵĵ�ǰ���������ڵ�
 * @param timer timer_tʵ��
 * @param node ����ڵ�
 */
void timer_set_current_list_node(timer_t* timer, dlist_node_t* node);

/*
 * ȡ�õ�ǰ����ڵ�
 * @param timer timer_tʵ��
 * @return dlist_node_tʵ��
 */
dlist_node_t* timer_get_current_list_node(timer_t* timer);

/*
 * ȡ�õδ���
 * @param timer_loop timer_loop_tʵ��
 * @return �δ���
 */
time_t timer_loop_get_tick_intval(timer_loop_t* timer_loop);

#endif /* TIMER_H */
