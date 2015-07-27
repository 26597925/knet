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

#ifndef VROUTER_API_H
#define VROUTER_API_H

#include "config.h"

/**
 * @defgroup vrouter ����·��
 * ����·��
 *
 * <pre>
 * �ṩһ����Ե㵥���·�ɹ�ϵ������ά���˹ܵ�·�ɵ�{c1, c2}�Ķ�Ӧ��ϵ��
 * �����ת����ϵ�ǵ���ģ���ֻ֧��c1��c2��ת�����������˺�c2��c1��ת����
 * ���Ҫ֧��c2��c1��ת������Ҫ����µ�ת����ϵ{c2, c1}.
 * ����ʹ��Դ�ܵ���UUID��Ϊ��������ͬһ���ܵ���Ϊ��ʼ�ܵ�ֻ�ܳ���һ��,��
 * ��ΪĿ�Ĺܵ����Գ���N��.
 * ���н���ת����ϵ�Ĺܵ��Զ��ᱻ�������ü������Ӷ����ƹܵ����������ڣ���ֹ��
 * �ⲿ�����ڲ�����ʹ�õĹܵ�.
 * </pre>
 * @{
 */

/**
 * ������������·����
 * @return kvrouter_tʵ��
 */
extern kvrouter_t* knet_vrouter_create();

/**
 * ����
 * return kvrouter_tʵ��
 */
extern void knet_vrouter_destroy(kvrouter_t* router);

/**
 * ����һ��ת��ת����ϵ
 * @param router kvrouter_tʵ��
 * @param c1 kchannel_ref_tʵ����Դ�ܵ�
 * @param c2 kchannel_ref_tʵ����Ŀ�Ĺܵ�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_vrouter_add_wire(kvrouter_t* router, kchannel_ref_t* c1, kchannel_ref_t* c2);

/**
 * ɾ��һ��ת����ϵ
 * @param router kvrouter_tʵ��
 * @param c kchannel_ref_tʵ����Դ�ܵ�(knet_vrouter_add_wire�ڶ�������)
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_vrouter_remove_wire(kvrouter_t* router, kchannel_ref_t* c);

/**
 * ת������
 * @param router kvrouter_tʵ��
 * @param c kchannel_ref_tʵ����Դ�ܵ�(knet_vrouter_add_wire�ڶ�������)
 * @param buffer ���ݻ�����
 * @param size ����������
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_vrouter_route(kvrouter_t* router, kchannel_ref_t* c, void* buffer, int size);

/** @} */

#endif /* VROUTER_API_H */
