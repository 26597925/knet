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

#ifndef MISC_H
#define MISC_H

#include "config.h"
#include "thread_api.h"

/**
 * ����һ���׽���
 * @return �׽���
 */
socket_t socket_create();

/**
 * �����첽connect
 * @param socket_fd �׽���
 * @param ip IP
 * @param port �˿�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int socket_connect(socket_t socket_fd, const char* ip, int port);

/**
 * bind & listen
 * @param socket_fd �׽���
 * @param ip IP
 * @param port �˿�
 * @param backlog ����listen()����
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int socket_bind_and_listen(socket_t socket_fd, const char* ip, int port, int backlog);

/**
 * accept
 * @param socket_fd �׽���
 * @retval 0 ʧ��
 * @retval ��Ч���׽���
 */
socket_t socket_accept(socket_t socket_fd);

/**
 * �ر��׽��֣�ǿ�ƹرգ�
 * @param socket_fd �׽���
 * @retval 0 �ɹ�
 * @retval ���� ʧ��
 */
int socket_close(socket_t socket_fd);

int socket_set_reuse_addr_on(socket_t socket_fd);
int socket_set_non_blocking_on(socket_t socket_fd);
int socket_set_nagle_off(socket_t socket_fd);
int socket_set_linger_off(socket_t socket_fd);
int socket_set_keepalive_off(socket_t socket_fd);
int socket_set_donot_route_on(socket_t socket_fd);
int socket_set_recv_buffer_size(socket_t socket_fd, int size);
int socket_set_send_buffer_size(socket_t socket_fd, int size);
int socket_send(socket_t socket_fd, const char* data, uint32_t size);
int socket_recv(socket_t socket_fd, char* data, uint32_t size);

/**
 * socketpair
 * @sa socketpair
 */
int socket_pair(socket_t pair[2]);

/**
 * getpeername
 * @sa getpeername
 */
int socket_getpeername(channel_ref_t* channel_ref, address_t* address);

/**
 * getsockname
 * @sa getsockname
 */
int socket_getsockname(channel_ref_t* channel_ref, address_t* address);

/**
 * ����׽����Ƿ��д
 * @retval 0 ����д
 * @retval 1 ��д
 */
int socket_check_send_ready(socket_t socket_fd);

/**
 * ����������ʵ��
 * @return lock_tʵ��
 */
lock_t* lock_create();

/**
 * ���ٻ�����
 * @param lock lock_tʵ��
 */
void lock_destroy(lock_t* lock);

/**
 * ��
 * @param lock lock_tʵ��
 */
void lock_lock(lock_t* lock);

/**
 * ������
 * @param lock lock_tʵ��
 * @sa pthread_mutex_trylock
 */
int lock_trylock(lock_t* lock);

/**
 * ����
 * @param lock lock_tʵ��
 */
void lock_unlock(lock_t* lock);

/**
 * ��ȡ��ǰ����
 */
uint32_t time_get_milliseconds();

/**
 * ��ȡ��ǰ΢��
 */
uint64_t time_get_microseconds();

/**
 * gettimeofday
 * @sa gettimeofday
 */
int time_gettimeofday(struct timeval *tp, void *tzp);

/**
 * ȡ�õ�ǰ���Ķ�ʱ���ַ���
 * @param buffer ���������
 * @param size ��������С
 * @return ��ʽΪYYYY-MM-DD HH:mm:SS:MS
 */
char* time_get_string(char* buffer, int size);

/**
 * ����һ��αUUID��ֻ��֤�������ڲ��ظ�
 * @return αUUID
 */
uint64_t uuid_create();

/**
 * ȡ�õ�ǰ����Ŀ¼
 * @param buffer ·��������ָ��
 * @param size ��������С
 * @retval 0 ʧ��
 * @retval ·��������ָ��
 */
char* path_getcwd(char* buffer, int size);

/**
 * ��ȡ���µ�ϵͳ������
 * @return ϵͳ������
 */
sys_error_t sys_get_errno();

/**
 * �ֽ���ת�� - ������������
 * @param ui64 64λ�޷�������
 * @return 64λ�޷�������
 */
uint64_t htonll(uint64_t ui64);

/**
 * �ֽ���ת�� - ������������
 * @param ui64 64λ�޷�������
 * @return 64λ�޷�������
 */
uint64_t ntohll(uint64_t ui64);

#endif /* MISC_H */
