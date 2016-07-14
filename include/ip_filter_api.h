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

#ifndef IP_FILTER_API_H
#define IP_FILTER_API_H

#include "config.h"

/**
 * @defgroup ip_filter IP����
 * IP����
 * <pre>
 * �ṩ�˿����ж�ָ��IP�Ƿ�����IP���Ͻӿڣ���������IP���������߰�����.
 * ip_filter_t���Լ����Ѿ����ڵ�IP�����ļ���ͬʱҲ���Ա���IP�����ļ���
 * IP�����ļ��ĸ�ʽΪ��
 * IP ����
 * IP ����
 * ......
 * ����ʹ���κ��ı��༭���ֹ��༭.
 * Ҳ����ʹ�ýӿڷ���ʵʱ���������������µ�IP���ɾ��IP�����������
 * ͨ�����淽���������滻�ɵ�IP��.
 * </pre>
 * @{
 */

/**
 * ����IP������
 * @return kip_filter_tʵ��
 */
extern kip_filter_t* knet_ip_filter_create();

/**
 * ����IP������
 * @param ip_filter kip_filter_tʵ��
 */
extern void knet_ip_filter_destroy(kip_filter_t* ip_filter);

/**
 * ����IP�����ļ�
 *
 * <pre>
 * �ļ���ʽΪ:
 * [IP]\n
 * [IP]\n
 * ......
 * </pre>
 * @param ip_filter kip_filter_tʵ��
 * @param path �ļ�·��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_ip_filter_load_file(kip_filter_t* ip_filter, const char* path);

/**
 * ��ӵ���IP
 * @param ip_filter kip_filter_tʵ��
 * @param ip IP
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_ip_filter_add(kip_filter_t* ip_filter, const char* ip);

/**
 * ɾ������IP
 * @param ip_filter kip_filter_tʵ��
 * @param ip IP
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_ip_filter_remove(kip_filter_t* ip_filter, const char* ip);

/**
 * ���浽�ļ�
 * @param ip_filter kip_filter_tʵ��
 * @param path �ļ�·��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int knet_ip_filter_save(kip_filter_t* ip_filter, const char* path);

/**
 * ���IP�Ƿ񱻹���
 * @param ip_filter kip_filter_tʵ��
 * @param ip IP
 * @retval 0 δ������
 * @retval ���� ������
 */
extern int knet_ip_filter_check(kip_filter_t* ip_filter, const char* ip);

/**
 * ���IP�Ƿ񱻹���
 * @param ip_filter kip_filter_tʵ��
 * @param address ��ַ
 * @retval 0 δ������
 * @retval ���� ������
 */
extern int knet_ip_filter_check_address(kip_filter_t* ip_filter, kaddress_t* address);

/**
 * ���IP�Ƿ񱻹���
 *
 * ���˶Զ˵�ַ(peer address);
 * @param ip_filter kip_filter_tʵ��
 * @param channel kchannel_ref_tʵ��
 * @retval 0 δ������
 * @retval ���� ������
 */
extern int knet_ip_filter_check_channel(kip_filter_t* ip_filter, kchannel_ref_t* channel);

/** @} */

#endif /* IP_FILTER_API_H */
