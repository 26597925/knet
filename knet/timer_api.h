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

#ifndef TIMER_API_H
#define TIMER_API_H

#include "config.h"

/**
 * @defgroup timer ��ʱ��
 * ��ʱ��
 *
 * <pre>
 * ��ʱ��
 *
 * ��ʱ����û�з���kloop_t�ڴ��������ṩ�˶�����ktimer_loop_t������ʱ��.
 * ��3�ֶ�ʱ������:
 *
 * 1. �����Զ�ʱ��     ktimer_start����
 * 2. ����һ�εĶ�ʱ��  ktimer_start_once����
 * 3. ���ж�εĶ�ʱ��  ktimer_start_times����
 *
 * ��ʱ���Ĵ���ʽͨ���ص��������봫ͳ�Ķ�ʱ��������ʽ��ͬ���ڲ�ʵ�ֲ�����
 * ���������ʱ���ļ����ɾ����ʱ�临�Ӷȶ���O(logn)
 *
 * ktimer_loop_run�ڲ�ʹ�ò���ϵͳ�ṩ�ĺ��뼶˯�ߺ�����ģ��������ֹCPU��ת��
 * ������ϵͳ�ṩ��˯�ߺ���ͨ���ǲ�׼ȷ�ģ����˯��>=����ʱ��Ƭ��ͨ�����Ϊ�ٷ�֮2����,
 * ����ڷǺ��뼶��ȷ��ͨ���ǹ��õģ����ǵ���10����ֱ��ʵĶ�ʱ�����зǳ�����������Ҫ
 * ��ȷ�Ķ�ʱ������Ҫ���ò���ϵͳ�߷ֱ���ʱ�亯�������д���.
 *
 * </pre>
 * @{
 */

/**
 * ������ʱ��ѭ��
 * @param freq ��С�ֱ��ʣ����룩
 * @return ktimer_loop_tʵ��
 */
extern ktimer_loop_t* ktimer_loop_create(time_t freq);

/**
 * ���ٶ�ʱ��ѭ��
 * @return ktimer_loop_tʵ��
 */
extern void ktimer_loop_destroy(ktimer_loop_t* timer_loop);

/**
 * ��鶨ʱ����ʱ�������ʱ���ö�ʱ���ص�
 * @param timer_loop ktimer_loop_tʵ��
 * @return ��ʱ����ʱ������
 */
extern int ktimer_loop_run_once(ktimer_loop_t* timer_loop);

/**
 * ѭ����鶨ʱ����ʱ������ktimer_loop_exit()�˳�
 * @param timer_loop ktimer_loop_tʵ��
 */
extern void ktimer_loop_run(ktimer_loop_t* timer_loop);

/**
 * �˳�ktimer_loop_run()
 * @param timer_loop ktimer_loop_tʵ��
 */
extern void ktimer_loop_exit(ktimer_loop_t* timer_loop);

/**
 * ����һ����ʱ��
 * @param timer_loop ktimer_loop_tʵ��
 * @return ktimer_tʵ��
 */
extern ktimer_t* ktimer_create(ktimer_loop_t* timer_loop);

/**
 * ֹͣ�����ٶ�ʱ��
 * @param timer ktimer_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ktimer_stop(ktimer_t* timer);

/**
 * ȡ��ktimer_loop_tʵ��
 * @param timer ktimer_tʵ��
 * @return ktimer_loop_tʵ��
 */
extern ktimer_loop_t* ktimer_get_loop(ktimer_t* timer);

/**
 * ����һ�����޴����Ķ�ʱ��
 * @param timer ktimer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ktimer_start(ktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms);

/**
 * ����һ��ֻ��ʱһ�εĶ�ʱ������ʱ���Զ�����
 * @param timer ktimer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ktimer_start_once(ktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms);

/**
 * ����һ�����޴����Ķ�ʱ�����ﵽtimes�������Զ�����
 * @param timer ktimer_tʵ��
 * @param cb ��ʱ�ص�����
 * @param data �ص���������
 * @param ms ��ʱ����ʱ���
 * @param times ����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ktimer_start_times(ktimer_t* timer, ktimer_cb_t cb, void* data, time_t ms, int times);

/**
 * ��鶨ʱ���Ƿ��ڻص��������ؼ���������
 * @param timer ktimer_tʵ��
 * @retval 0 ����
 * @retval ���� ��
 */
extern int ktimer_check_dead(ktimer_t* timer);

/**
 * ȡ�õδ���
 * @param timer_loop ktimer_loop_tʵ��
 * @return �δ���
 */
extern time_t ktimer_loop_get_tick_intval(ktimer_loop_t* timer_loop);

/** @} */

#endif /* TIMER_API_H */
