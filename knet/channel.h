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

#ifndef CHANNEL_H
#define CHANNEL_H

#include "config.h"

/**
 * ����һ��channel_tʵ��
 * @param max_send_list_len ����������󳤶�
 * @param recv_ring_len ���ܻ�������󳤶�
 * @return channel_tʵ��
 */
channel_t* channel_create(uint32_t max_send_list_len, uint32_t recv_ring_len);

/**
 * ����һ��channel_tʵ��
 * @param socket_fd �ѽ������׽���
 * @param max_send_list_len ����������󳤶�
 * @param recv_ring_len ���ܻ�������󳤶�
 * @return channel_tʵ��
 */
channel_t* channel_create_exist_socket_fd(socket_t socket_fd, uint32_t max_send_list_len, uint32_t recv_ring_len);

/**
 * ����channel_tʵ��
 * @param channel channel_tʵ��
 */
void channel_destroy(channel_t* channel);

/**
 * ���Ӽ�����
 * @param channel channel_tʵ��
 * @param ip IP
 * @param port �˿�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_connect(channel_t* channel, const char* ip, int port);

/**
 * ����
 * @param channel channel_tʵ��
 * @param ip IP
 * @param port �˿�
 * @param backlog �ȴ����г���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_accept(channel_t* channel, const char* ip, int port, int backlog);

/**
 * �ر�
 * @param channel channel_tʵ��
 */
void channel_close(channel_t* channel);

/**
 * ����
 * ����������Ϊ�յ�ʱ�򣬻����ȳ���ֱ�ӷ��͵��׽��ֻ�����(zero copy)�������ŵ���������ĩβ�ȴ�
 * �ʵ�ʱ������.
 * @param channel channel_tʵ��
 * @param data ��������ָ��
 * @param size ���ݳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_send(channel_t* channel, const char* data, int size);

/**
 * ����
 * �ŵ���������ĩβ�ȴ��ʵ�ʱ������.
 * @param channel channel_tʵ��
 * @param send_buffer ���ͻ�����buffer_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_send_buffer(channel_t* channel, buffer_t* send_buffer);

/**
 * ��д�¼�֪ͨ
 * @param channel channel_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_update_send(channel_t* channel);

/**
 * �ɶ��¼�֪ͨ
 * @param channel channel_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_update_recv(channel_t* channel);

/**
 * ȡ���׽���
 * @param channel channel_tʵ��
 * @return �׽���
 */
socket_t channel_get_socket_fd(channel_t* channel);

/**
 * ȡ�ö�������
 * @param channel channel_tʵ��
 * @return ringbuffer_tʵ��
 */
ringbuffer_t* channel_get_ringbuffer(channel_t* channel);

/**
 * ȡ�÷���������󳤶�����
 * @param channel channel_tʵ��
 * @return ����������󳤶�����
 */
uint32_t channel_get_max_send_list_len(channel_t* channel);

/**
 * ��ȡ�ܵ�UUID
 * @param channel channel_tʵ��
 * @return �ܵ�UUID
 */
uint64_t channel_get_uuid(channel_t* channel);

/**
 * ���������ڻ����������Ƿ�ﵽ���
 * @param channel channel_tʵ��
 * @retval 0 ����
 * @retval ���� ��
 */
int channel_ref_send_list_reach_max(channel_t* channel);

#endif /* CHANNEL_H */