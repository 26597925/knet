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

#ifndef LOGGER_API_H
#define LOGGER_API_H

#include "config.h"

/**
 * ������־
 * @param path ��־�ļ�·��, ���Ϊ0��ʹ�õ�ǰĿ¼
 * @param level ��־�ȼ�
 * @param mode ��־ģʽ
 * @return klogger_tʵ��
 */
extern klogger_t* logger_create(const char* path, int level, int mode);

/**
 * ������־
 * @param logger klogger_tʵ��
 */
extern void logger_destroy(klogger_t* logger);

/**
 * д��־
 * @param logger klogger_tʵ��
 * @param level ��־�ȼ�
 * @param format ��־��ʽ
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int logger_write(klogger_t* logger, int level, const char* format, ...);

#endif /* LOGGER_API_H */
