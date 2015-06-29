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

#ifndef CHANNEL_REF_H
#define CHANNEL_REF_H

#include "config.h"
#include "channel_ref_api.h"

/**
 * �����ܵ�����
 * @param loop loop_tʵ��
 * @param channel channel_tʵ��
 * @return channel_ref_tʵ��
 */
channel_ref_t* channel_ref_create(loop_t* loop, channel_t* channel);

/**
 * ���ٹܵ�����
 * �ܵ����ü���Ϊ��ʱ���ܱ�ʵ������
 * @param channel_ref channel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_ref_destroy(channel_ref_t* channel_ref);

/**
 * д��
 * �ܵ����ü���Ϊ��ʱ���ܱ�ʵ������
 * @param channel_ref channel_ref_tʵ��
 * @param data д������ָ��
 * @param size ���ݳ���
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_ref_write(channel_ref_t* channel_ref, const char* data, int size);

/**
 * Ϊͨ��accept()���ص��׽��ִ����ܵ�����
 * @param channel_ref channel_ref_tʵ��
 * @param loop loop_tʵ��
 * @param client_fd ͨ��accept()�õ����׽���
 * @param event �Ƿ�Ͷ���¼������ùܵ�״̬
 * @return channel_ref_tʵ��
 */
channel_ref_t* channel_ref_accept_from_socket_fd(channel_ref_t* channel_ref, loop_t* loop, socket_t client_fd, int event);

/**
 * ȡ�ùܵ��������loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 * @return loop_tʵ��
 */
loop_t* channel_ref_choose_loop(channel_ref_t* channel_ref);

/**
 * ���ùܵ�����ڵ�
 * @param channel_ref channel_ref_tʵ��
 * @param node ����ڵ�
 */
void channel_ref_set_loop_node(channel_ref_t* channel_ref, dlist_node_t* node);

/**
 * ȡ�ùܵ�����ڵ�
 * @param channel_ref channel_ref_tʵ��
 * @return dlist_node_tʵ��
 */
dlist_node_t* channel_ref_get_loop_node(channel_ref_t* channel_ref);

/**
 * ��loop_t�����е��߳��������������
 * @param channel_ref channel_ref_tʵ��
 * @param ip IP
 * @param port �˿�
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
int channel_ref_connect_in_loop(channel_ref_t* channel_ref, const char* ip, int port);

/**
 * ��loop_t�����е��߳�����ɽ�������������
 * ͨ�����ؾ��ⴥ��
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void channel_ref_update_accept_in_loop(loop_t* loop, channel_ref_t* channel_ref);

/**
 * ��loop_t�����е��߳�����ɹر�����
 * ͨ�����̹߳رմ���
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
void channel_ref_update_close_in_loop(loop_t* loop, channel_ref_t* channel_ref);

/**
 * ��loop_t�����е��߳��ڷ���
 * ͨ�����̷߳��ʹ���
 * @param loop loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 * @param send_buffer buffer_tʵ��
 */
void channel_ref_update_send_in_loop(loop_t* loop, channel_ref_t* channel_ref, buffer_t* send_buffer);

/**
 * ���ùܵ��Զ����־
 * @param channel_ref channel_ref_tʵ��
 * @param flag �Զ����־
 */
void channel_ref_set_flag(channel_ref_t* channel_ref, int flag);

/**
 * ȡ�ùܵ��Զ����־
 * @param channel_ref channel_ref_tʵ��
 * @return �Զ����־
 */
int channel_ref_get_flag(channel_ref_t* channel_ref);

/**
 * ���ùܵ��Զ�������
 * @param channel_ref channel_ref_tʵ��
 * @param data �Զ�������ָ��
 */
void channel_ref_set_data(channel_ref_t* channel_ref, void* data);

/**
 * ȡ�ùܵ��Զ�������
 * @param channel_ref channel_ref_tʵ��
 * @return �Զ�������ָ��
 */
void* channel_ref_get_data(channel_ref_t* channel_ref);

/**
 * ���ùܵ��������������loop_tʵ��
 * @param channel_ref channel_ref_tʵ��
 * @param loop loop_tʵ��
 */
void channel_ref_set_loop(channel_ref_t* channel_ref, loop_t* loop);

/**
 * Ͷ�ݹܵ��¼�
 * @param channel_ref channel_ref_tʵ��
 * @param e �ܵ��¼�
 */
void channel_ref_set_event(channel_ref_t* channel_ref, channel_event_e e);

/**
 * ��ȡ�ܵ��Ѿ�Ͷ�ݵ��¼�����
 * @param channel_ref channel_ref_tʵ��
 * @return �ܵ��¼�����
 */
channel_event_e channel_ref_get_event(channel_ref_t* channel_ref);

/**
 * ȡ���ܵ��¼�
 * @param channel_ref channel_ref_tʵ��
 * @param e �ܵ��¼�
 */
void channel_ref_clear_event(channel_ref_t* channel_ref, channel_event_e e);

/**
 * ����Ƿ�Ͷ�����¼�
 * @param channel_ref channel_ref_tʵ��
 * @param event �ܵ��¼�
 * @retval 0 û��Ͷ��
 * @retval ���� �Ѿ�Ͷ��
 */
int channel_ref_check_event(channel_ref_t* channel_ref, channel_event_e event);

/**
 * ���ùܵ�״̬
 * @param channel_ref channel_ref_tʵ��
 * @param state �ܵ�״̬
 */
void channel_ref_set_state(channel_ref_t* channel_ref, channel_state_e state);

/**
 * �ܵ��¼�֪ͨ
 * @param channel_ref channel_ref_tʵ��
 * @param e �ܵ��¼�
 * @param ts ��ǰʱ������룩
 */
void channel_ref_update(channel_ref_t* channel_ref, channel_event_e e, time_t ts);

/**
 * �ܵ��¼�����-����������������
 * @param channel_ref channel_ref_tʵ��
 */
void channel_ref_update_accept(channel_ref_t* channel_ref);

/**
 * �ܵ��¼�����-�����������
 * @param channel_ref channel_ref_tʵ��
 */
void channel_ref_update_connect(channel_ref_t* channel_ref);

/**
 * �ܵ��¼�����-�����ݿɶ�
 * @param channel_ref channel_ref_tʵ��
 */
void channel_ref_update_recv(channel_ref_t* channel_ref);

/**
 * �ܵ��¼�����-���Է�������
 * @param channel_ref channel_ref_tʵ��
 */
void channel_ref_update_send(channel_ref_t* channel_ref);

/**
 * ���ܵ���������Ӳ����Ƿ�ʱ
 * @param channel_ref channel_ref_tʵ��
 * @param ts ��ǰʱ������룩
 * @retval 0 û�г�ʱ
 * @retval ���� ��ʱ
 */
int channel_ref_check_connect_timeout(channel_ref_t* channel_ref, time_t ts);

/**
 * ���ܵ��Ƿ���г�ʱ
 * @param channel_ref channel_ref_tʵ��
 * @param ts ��ǰʱ������룩
 * @retval 0 û�г�ʱ
 * @retval ���� ��ʱ
 */
int channel_ref_check_timeout(channel_ref_t* channel_ref, time_t ts);

/**
 * ȡ�ùܵ���������
 * @param channel_ref channel_ref_tʵ��
 * @return ringbuffer_tʵ��
 */
ringbuffer_t* channel_ref_get_ringbuffer(channel_ref_t* channel_ref);

/**
 * ȡ�ùܵ��¼��ص�
 * @param channel_ref channel_ref_tʵ��
 * @return �ص�����ָ��
 */
channel_ref_cb_t channel_ref_get_cb(channel_ref_t* channel_ref);

/**
 * ����������ڵ�
 * @param channel_ref channel_ref_tʵ��
 * @param node ������ڵ�
 */
void channel_ref_set_domain_node(channel_ref_t* channel_ref, dlist_node_t* node);

/**
 * ȡ��������ڵ�
 * @param channel_ref channel_ref_tʵ��
 * @return dlist_node_tʵ��
 */
dlist_node_t* channel_ref_get_domain_node(channel_ref_t* channel_ref);

/**
 * ���ܵ������Ƿ�ͨ������channel_ref_share()����
 * @param channel_ref channel_ref_tʵ��
 * @retval 0 ����
 * @retval ���� ��
 */
int channel_ref_check_share(channel_ref_t* channel_ref);

/**
 * ������ID
 * @param channel_ref channel_ref_tʵ��
 * @param domain_id ��ID
 */
void channel_ref_set_domain_id(channel_ref_t* channel_ref, uint64_t domain_id);

/**
 * ȡ����ID
 * @param channel_ref channel_ref_tʵ��
 * @return ��ID
 */
uint64_t channel_ref_get_domain_id(channel_ref_t* channel_ref);

/**
 * ������ǰ�ܵ����ü���
 * @param channel_ref channel_ref_tʵ��
 */
void channel_ref_incref(channel_ref_t* channel_ref);

/**
 * �ݼ���ǰ�ܵ����ü���
 * @param channel_ref channel_ref_tʵ��
 */
void channel_ref_decref(channel_ref_t* channel_ref);

#endif /* CHANNEL_REF_H */
