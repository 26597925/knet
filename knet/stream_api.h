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

#ifndef STREAM_API_H
#define STREAM_API_H

#include "config.h"

/**
 * @defgroup stream ��
 * �ܵ���
 *
 * <pre>
 * �ܵ���
 *
 * stream_tͨ�����ú���channel_ref_get_streamȡ��. �ܵ����ṩ�˻����������ݲ���
 * �Լ����������Եķ���������߲���Ч��.
 * 
 * 1. stream_available   ��ȡ���ڿɶ��ֽ���
 * 2. stream_eat_all     �����������пɶ��ֽ�
 * 3. stream_eat         ��������ָ���������ֽ�
 * 4. stream_pop         �����ڶ�ȡ����
 * 5. stream_push        ������д����
 * 6. stream_copy        �����ڿ���ָ�������Ŀɶ��ֽڣ����������Щ�ֽڣ�ͨ������Э����
 * 7. stream_push_stream ���������пɶ��ֽ�д����һ����������Ҫ���⿽��, ���������ص�������ת
 * 8. stream_copy_stream ���������пɶ��ֽ�д����һ����������Ҫ���⿽��, ���������Щ�ֽڣ������ڹ㲥
 *
 * ������Щ��������Ƴ��˻�����������Ĺ������⣬���������ض������Ӧ�ã�ͬʱ�����Ч��.
 *
 * </pre>
 * @{
 */

/**
 * ȡ���������ڿɶ��ֽ���
 * @param stream stream_tʵ��
 * @return �ɶ��ֽ���
 */
extern int stream_available(stream_t* stream);

/**
 * ���������
 * @param stream stream_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int stream_eat_all(stream_t* stream);

/**
 * ɾ��ָ����������
 * @param stream stream_tʵ��
 * @param size ��Ҫɾ���ĳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int stream_eat(stream_t* stream, int size);

/**
 * ���������ڶ�ȡ���ݲ��������
 * @param stream stream_tʵ��
 * @param buffer ������
 * @param size ��������С
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int stream_pop(stream_t* stream, void* buffer, int size);

/**
 * ����������д����
 * @param stream stream_tʵ��
 * @param buffer ������
 * @param size ��������С
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int stream_push(stream_t* stream, const void* buffer, int size);

/**
 * ��������д���ݣ��ɱ�����ַ���
 *
 * һ��д��ĳ��Ȳ��ܳ���1024
 * @param stream stream_tʵ��
 * @param format �ַ�����ʽ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int stream_push_varg(stream_t* stream, const char* format, ...);

/**
 * ���������ڿ������ݣ��������������������
 * @param stream stream_tʵ��
 * @param buffer ������
 * @param size ��������С
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int stream_copy(stream_t* stream, void* buffer, int size);

/**
 * ��stream������д��target, �����stream������
 * @param stream stream_tʵ��
 * @param target stream_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int stream_push_stream(stream_t* stream, stream_t* target);

/**
 * ��stream������д��target, �������stream������
 * @param stream stream_tʵ��
 * @param target stream_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int stream_copy_stream(stream_t* stream, stream_t* target);

/**
 * ��ȡ�������Ĺܵ�����
 * @param stream stream_tʵ��
 * @return channel_ref_tʵ��
 */
extern channel_ref_t* stream_get_channel_ref(stream_t* stream);

/** @} */

#endif /* STREAM_API_H */
