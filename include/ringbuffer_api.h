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

#ifndef RINGBUFFER_API_H
#define RINGBUFFER_API_H

#include "config.h"


/**
 * ����һ��ringbuffer
 * @param size ��󳤶�
 * @return kringbuffer_tʵ��
 */
extern kringbuffer_t* ringbuffer_create(uint32_t size);

/**
 * ����ringbuffer
 * @param rb kringbuffer_tʵ��
 */
extern void ringbuffer_destroy(kringbuffer_t* rb);

/**
 * ��ȡ�����
 * @param rb kringbuffer_tʵ��
 * @param buffer д�뻺����ָ��
 * @param size д�뻺��������
 * @return ʵ�ʶ����ֽ���
 */
extern uint32_t ringbuffer_read(kringbuffer_t* rb, char* buffer, uint32_t size);

/**
 * д��
 * @param rb kringbuffer_tʵ��
 * @param buffer д�뻺����ָ��
 * @param size д�뻺��������
 * @return ʵ��д���ֽ���
 */
extern uint32_t ringbuffer_write(kringbuffer_t* rb, const char* buffer, uint32_t size);

/**
 * �滻
 * @param rb kringbuffer_tʵ��
 * @param pos �滻����ʼλ��
 * @param buffer д�뻺����ָ��
 * @param size д�뻺��������
 * @return ʵ��д���ֽ���
 */
extern uint32_t ringbuffer_replace(kringbuffer_t* rb, uint32_t pos, const char* buffer, uint32_t size);

/**
 * ��ȡ�������
 * @param rb kringbuffer_tʵ��
 * @param buffer д�뻺����ָ��
 * @param size д�뻺��������
 * @return ʵ�ʶ����ֽ���
 */
extern uint32_t ringbuffer_copy(kringbuffer_t* rb, char* buffer, uint32_t size);

/**
 * ����ָ����Ŀ�꣬������λ��
 * @param rb kringbuffer_tʵ��
 * @param target Ŀ���ַ���
 * @param size λ��
 * @retval error_ok �ҵ�
 * @retval ���� δ�ҵ�
 */
extern uint32_t ringbuffer_find(kringbuffer_t* rb, const char* target, uint32_t* size);

/**
 * ȡ�ÿɶ��ֽ���
 * @param rb kringbuffer_tʵ��
 * @return �ɶ��ֽ���
 */
extern uint32_t ringbuffer_available(kringbuffer_t* rb);

/**
 * ������пɶ��ֽ�
 * @param rb kringbuffer_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ringbuffer_eat_all(kringbuffer_t* rb);

/**
 * ���ָ�����ȵĿɶ��ֽ�
 * @param rb kringbuffer_tʵ��
 * @param size ��Ҫ����ĳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int ringbuffer_eat(kringbuffer_t* rb, uint32_t size);

/**
 * ȡ�÷��ƻ�������ַ�����ɶ��ֽ���
 * @param rb kringbuffer_tʵ��
 * @return ���ƻ�������ַ�����ɶ��ֽ���
 */
extern uint32_t ringbuffer_read_lock_size(kringbuffer_t* rb);

/**
 * ȡ�ÿɶ�������ָֹ��
 * @param rb kringbuffer_tʵ��
 * @return �ɶ�������ָֹ��
 */
extern char* ringbuffer_read_lock_ptr(kringbuffer_t* rb);

/**
 * �ύ������Ѿ��������ֽ�
 * @param rb kringbuffer_tʵ��
 * @param size �Ѿ��������ֽ���
 */
extern void ringbuffer_read_commit(kringbuffer_t* rb, uint32_t size);

/**
 * ���ⴰ�� - ȡ�÷��ƻ�������ַ�����ɶ��ֽ���
 * @param rb kringbuffer_tʵ��
 * @return ���ƻ�������ַ�����ɶ��ֽ���
 */
extern uint32_t ringbuffer_window_read_lock_size(kringbuffer_t* rb);

/**
 * ���ⴰ�� - ȡ�ÿɶ�������ָֹ��
 * @param rb kringbuffer_tʵ��
 * @return �ɶ�������ָֹ��
 */
extern char* ringbuffer_window_read_lock_ptr(kringbuffer_t* rb);

/**
 * ���ⴰ�� - �ύ�Ѿ��������ֽڣ��������
 * @param rb kringbuffer_tʵ��
 * @param size �Ѿ��������ֽ���
 */
void ringbuffer_window_read_commit(kringbuffer_t* rb, uint32_t size);

/**
 * ȡ�÷��ƻؿ�����д�����󳤶�
 * @param rb kringbuffer_tʵ��
 * @return ���ƻؿ�����д�����󳤶�
 */
extern uint32_t ringbuffer_write_lock_size(kringbuffer_t* rb);

/**
 * ȡ�ÿ�д��ʼָ��
 * @param rb kringbuffer_tʵ��
 * @return ��д��ָֹ��
 */
extern char* ringbuffer_write_lock_ptr(kringbuffer_t* rb);

/**
 * �ύ�ɹ�д����ֽ���
 * @param rb kringbuffer_tʵ��
 * @param size �ɹ�д����ֽ���
 */
extern void ringbuffer_write_commit(kringbuffer_t* rb, uint32_t size);

/**
 * ��
 * @param rb kringbuffer_tʵ��
 * @retval 0 δ��
 * @retval ���� ��
 */
extern int ringbuffer_full(kringbuffer_t* rb);

/**
 * ��
 * @param rb kringbuffer_tʵ��
 * @retval 0 �ǿ�
 * @retval ���� ��
 */
extern int ringbuffer_empty(kringbuffer_t* rb);

/**
 * ȡ����󳤶�
 * @param rb kringbuffer_tʵ��
 * @return ��󳤶�
 */
extern uint32_t ringbuffer_get_max_size(kringbuffer_t* rb);

/**
 * �����ݴ�ӡ����Ļ
 * @param rb kringbuffer_tʵ��
 */
extern void ringbuffer_print_stdout(kringbuffer_t* rb);

#endif /* RINGBUFFER_API_H */
