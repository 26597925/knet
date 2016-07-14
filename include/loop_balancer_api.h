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

#ifndef LOOP_BALANCER_API_H
#define LOOP_BALANCER_API_H

#include "config.h"

/**
 * @defgroup balancer ���ؾ�����
 * ���ؾ�����
 *
 * <pre>
 * ���ؾ���������������������kloop_t�������������kloop_t�ڼ��������ܵ����¹ܵ�
 * �����븺�ؾ��⣬���ؾ���Ĳ�����kloop_t�ڻ�Ծ�ܵ�������kloop_balancer_tѡ��
 * ��Ծ�ܵ����ٵ�kloop_t�����½��ܵĹܵ�.
 *
 * ����knet_loop_balancer_attach��kloop_balancer_t��kloop_t����������knet_loop_balancer_detach
 * ȡ������.
 * </pre>
 * @{
 */

/**
 * �������ؾ�����
 * @return kloop_balancer_tʵ��
 */
extern kloop_balancer_t* knet_loop_balancer_create();

/**
 * ���ٸ��ؾ�����
 * @param balancer kloop_balancer_tʵ��
 */
extern void knet_loop_balancer_destroy(kloop_balancer_t* balancer);

/**
 * ����¼�ѭ�������ؾ�����
 * @param balancer kloop_balancer_tʵ��
 * @param loop kloop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_loop_balancer_attach(kloop_balancer_t* balancer, kloop_t* loop);

/**
 * �Ӹ��ؾ�������ɾ���¼�ѭ��
 * @param balancer kloop_balancer_tʵ��
 * @param loop kloop_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_loop_balancer_detach(kloop_balancer_t* balancer, kloop_t* loop);

/** @} */

#endif /* LOOP_BALANCER_API_H */
