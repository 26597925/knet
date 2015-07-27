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

#ifndef BROADCAST_API_H
#define BROADCAST_API_H

#include "config.h"

/**
 * @defgroup broadcast �㲥
 * �㲥��
 *
 * <pre>
 * �ܵ����Լ���㲥�򣬼����ͨ��knet_broadcast_write�������Է������ݵ������Ѿ��������ڵĹܵ�.
 * ����knet_broadcast_create����һ���㲥��knet_broadcast_destroy���ٹ㲥��.
 *
 * knet_broadcast_join����һ���㲥��knet_broadcast_join��������ʱ������һ���µĹܵ�����.
 *
 * ����knet_broadcast_leaveʱӦ��ʹ���������ֵ������ʹ��knet_broadcast_join�ĵڶ����������´���
 * �Ĺܵ����û������ܵ������ü����������ر�������ܵ������ͨ������knet_broadcast_leave���ٹ�
 * �������ü������Ӷ�������kloop_t�������ٹܵ�.
 *
 * ����knet_broadcast_get_count���Ե�֪�㲥���ڵĹܵ���������������knet_broadcast_write����һ��
 * �㲥�������������ڹܵ������յ���㲥������.
 * </pre>
 * @{
 */

/**
 * �����㲥��
 * @return kbroadcast_tʵ��
 */
extern kbroadcast_t* knet_broadcast_create();

/**
 * ���ٹ㲥��
 *
 * ���ٵ�ͬʱ�Ὣ���л������ڵĹܵ���������
 * @param broadcast kbroadcast_tʵ��
 */
extern void knet_broadcast_destroy(kbroadcast_t* broadcast);

/**
 * ����㲥��
 *
 * ����ɹ�������һ���µ�����
 * @param broadcast kbroadcast_tʵ��
 * @param channel_ref kchannel_ref_t
 * @return kchannel_ref_tʵ�����µ��ڹ㲥���ڵ�����
 */
extern kchannel_ref_t* knet_broadcast_join(kbroadcast_t* broadcast, kchannel_ref_t* channel_ref);

/**
 * �뿪�㲥��
 *
 * �������غ�ܵ������Ѿ������٣���Ҫ�����ٴη����������
 * @param broadcast kbroadcast_tʵ��
 * @param channel_ref kchannel_ref_tʵ������knet_broadcast_join()����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_broadcast_leave(kbroadcast_t* broadcast, kchannel_ref_t* channel_ref);

/**
 * ȡ�ù㲥���ڹܵ�����
 * @param broadcast kbroadcast_tʵ��
 * @return �ܵ�����
 */
extern int knet_broadcast_get_count(kbroadcast_t* broadcast);

/**
 * �㲥
 * @param broadcast kbroadcast_tʵ��
 * @param buffer ������ָ��
 * @param size ����������
 * @return ���ͳɹ��ܵ�������
 */
extern int knet_broadcast_write(kbroadcast_t* broadcast, char* buffer, uint32_t size);

/** @} */

#endif /* BROADCAST_API_H */
