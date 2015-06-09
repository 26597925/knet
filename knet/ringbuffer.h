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

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

#include "config.h"

/*
 * ����һ��ringbuffer
 * @param size ��󳤶�
 * @return ringbuffer_tʵ��
 */
ringbuffer_t* ringbuffer_create(uint32_t size);

/*
 * ����ringbuffer
 * @param rb ringbuffer_tʵ��
 */
void ringbuffer_destroy(ringbuffer_t* rb);

/*
 * ��ȡ�����
 * @param rb ringbuffer_tʵ��
 * @param buffer д�뻺����ָ��
 * @param size д�뻺��������
 * @return ʵ�ʶ����ֽ���
 */
uint32_t ringbuffer_read(ringbuffer_t* rb, char* buffer, uint32_t size);

/*
 * ��ȡ�������
 * @param rb ringbuffer_tʵ��
 * @param buffer д�뻺����ָ��
 * @param size д�뻺��������
 * @return ʵ�ʶ����ֽ���
 */
uint32_t ringbuffer_copy(ringbuffer_t* rb, char* buffer, uint32_t size);

/*
 * ȡ�ÿɶ��ֽ���
 * @param rb ringbuffer_tʵ��
 * @return �ɶ��ֽ���
 */
uint32_t ringbuffer_available(ringbuffer_t* rb);

/*
 * ������пɶ��ֽ�
 * @param rb ringbuffer_tʵ��
 */
void ringbuffer_eat(ringbuffer_t* rb);

/*
 * ȡ�÷��ƻ�������ַ�����ɶ��ֽ���
 * @param rb ringbuffer_tʵ��
 * @return ���ƻ�������ַ�����ɶ��ֽ���
 */
uint32_t ringbuffer_read_lock_size(ringbuffer_t* rb);

/*
 * ȡ�ÿɶ�������ָֹ��
 * @param rb ringbuffer_tʵ��
 * @return �ɶ�������ָֹ��
 */
char* ringbuffer_read_lock_ptr(ringbuffer_t* rb);

/*
 * �ύ������Ѿ��������ֽ�
 * @param rb ringbuffer_tʵ��
 * @param size �Ѿ��������ֽ���
 */
void ringbuffer_read_commit(ringbuffer_t* rb, uint32_t size);

/*
 * ȡ�÷��ƻؿ�����д�����󳤶�
 * @param rb ringbuffer_tʵ��
 * @return ���ƻؿ�����д�����󳤶�
 */
uint32_t ringbuffer_write_lock_size(ringbuffer_t* rb);

/*
 * ȡ�ÿ�д��ָֹ��
 * @param rb ringbuffer_tʵ��
 * @return ��д��ָֹ��
 */
char* ringbuffer_write_lock_ptr(ringbuffer_t* rb);

/*
 * �ύ�ɹ�д����ֽ���
 * @param rb ringbuffer_tʵ��
 * @param size �ɹ�д����ֽ���
 */
void ringbuffer_write_commit(ringbuffer_t* rb, uint32_t size);

/*
 * ��
 * @param rb ringbuffer_tʵ��
 * @retval 0 δ��
 * @retval ���� ��
 */
int ringbuffer_full(ringbuffer_t* rb);

/*
 * ��
 * @param rb ringbuffer_tʵ��
 * @retval 0 �ǿ�
 * @retval ���� ��
 */
int ringbuffer_empty(ringbuffer_t* rb);

/*
 * ȡ����󳤶�
 * @param rb ringbuffer_tʵ��
 * @return ��󳤶�
 */
uint32_t ringbuffer_get_max_size(ringbuffer_t* rb);

#endif /* RINGBUFFER_H */
