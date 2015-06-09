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

#ifndef BUFFER_H
#define BUFFER_H

#include "config.h"

/*
 * ����һ���̶����ȵĻ�����
 * @param size ���������ȣ��ֽڣ�
 * @return buffer_tʵ��
 */
buffer_t* buffer_create(uint32_t size);

/*
 * ���ٻ�����
 * @param sb buffer_tʵ��
 */
void buffer_destroy(buffer_t* sb);

/*
 * д��
 * @param sb buffer_tʵ��
 * @param temp �ֽ�����ָ��
 * @param size �ֽ����鳤��
 * @retval 0 д��ʧ��
 * @retval >0 ʵ��д����ֽ���
 */
uint32_t buffer_put(buffer_t* sb, const char* temp, uint32_t size);

/*
 * ȡ�û����������ݳ���
 * @param sb buffer_tʵ��
 * @return ���ݳ���
 */
uint32_t buffer_get_length(buffer_t* sb);

/*
 * ȡ�û�����������ʼ��ַ
 * @param sb buffer_tʵ��
 * @return ���ݳ���
 */
char* buffer_get_ptr(buffer_t* sb);

/*
 * ����������ʼ��ַ
 * @param sb buffer_tʵ��
 * @param gap �����ĳ���
 */
void buffer_adjust(buffer_t* sb, uint32_t gap);

#endif /* BUFFER_H */
