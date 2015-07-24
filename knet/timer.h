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
 * DISCLAIMED. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef TIMER_H
#define TIMER_H

#include "config.h"
#include "timer_api.h"

/**
 * ���ٶ�ʱ��
 * @param timer ktimer_tʵ��
 */
void ktimer_destroy(ktimer_t* timer);

/**
 * ��鶨ʱ���Ƿ�ʱ
 * @param timer ktimer_tʵ��
 * @param ms ��ǰʱ���
 * @retval 0 û�г�ʱ
 * @retval ���� ��ʱ
 */
int ktimer_check_timeout(ktimer_t* timer, time_t ms);

/**
 * ���ö�ʱ�����ڵĵ�ǰ����
 * @param timer ktimer_tʵ��
 * @param list ����
 */
void ktimer_set_current_list(ktimer_t* timer, kdlist_t* list);

/**
 * ȡ�õ�ǰ��������
 * @param timer ktimer_tʵ��
 * @return kdlist_tʵ��
 */
kdlist_t* ktimer_get_current_list(ktimer_t* timer);

/**
 * ���ö�ʱ�����ڵĵ�ǰ���������ڵ�
 * @param timer ktimer_tʵ��
 * @param node ����ڵ�
 */
void ktimer_set_current_list_node(ktimer_t* timer, kdlist_node_t* node);

/**
 * ȡ�õ�ǰ����ڵ�
 * @param timer ktimer_tʵ��
 * @return kdlist_node_tʵ��
 */
kdlist_node_t* ktimer_get_current_list_node(ktimer_t* timer);

#endif /* TIMER_H */
