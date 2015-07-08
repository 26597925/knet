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
 * DISCLAIMED. IN NO EVENT SHALL dennis wang BE LIABLE FOR ANY
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
 * �����㲥��
 * @return broadcast_tʵ��
 */
extern broadcast_t* broadcast_create();

/**
 * ���ٹ㲥��
 * @param broadcast broadcast_tʵ��
 */
extern void broadcast_destroy(broadcast_t* broadcast);

/**
 * ����㲥��
 * ����ɹ�������һ���µ�����
 * @param broadcast broadcast_tʵ��
 * @param channel_ref channel_ref_t
 * @return channel_ref_tʵ�����µ��ڹ㲥���ڵ�����
 */
extern channel_ref_t* broadcast_join(broadcast_t* broadcast, channel_ref_t* channel_ref);

/**
 * �뿪�㲥��
 * @param broadcast broadcast_tʵ��
 * @param channel_ref channel_ref_tʵ������broadcast_join()����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int broadcast_leave(broadcast_t* broadcast, channel_ref_t* channel_ref);

/**
 * ȡ�ù㲥���ڹܵ�����
 * @param broadcast broadcast_tʵ��
 * @return �ܵ�����
 */
extern int broadcast_get_count(broadcast_t* broadcast);

/**
 * �㲥
 * @param broadcast broadcast_tʵ��
 * @param buffer ������ָ��
 * @param size ����������
 * @return ���ͳɹ��ܵ�������
 */
extern int broadcast_write(broadcast_t* broadcast, char* buffer, uint32_t size);

#endif /* BROADCAST_API_H */
