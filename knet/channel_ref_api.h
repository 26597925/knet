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

#ifndef CHANNEL_REF_API_H
#define CHANNEL_REF_API_H

#include "config.h"

/**
 * @defgroup �ܵ����� �ܵ�����
 * �ܵ�����
 *
 * <pre>
 * channel_ref_t��Ϊchannel_t�İ�װ���������û�͸�����˹ܵ����ڲ�ʵ�֣�ͬʱ�ṩ�����ü�������
 * �ܵ����������ڹ���.
 *
 * �ܵ���3�����ͣ�
 * 
 * 1. ������
 * 2. ������
 * 3. �ɼ��������ܵ��¹ܵ�
 *
 * �ܵ���3��״̬:
 * 
 * 1. �½��� �ս�������ȷ������Ϊ���������߼���������
 * 2. ��Ծ   �Ѿ�ȷ�����Լ��Ľ�ɫ
 * 3. �ر�   �Ѿ��رգ�����δ���٣����ü�����Ϊ��
 *
 * ��û�и��ؾ��������ڵ������(loop_tû��ͨ��loop_balancer_attach������loop_balancer_t),
 * �����������ܵ������ڵ�ǰloop_t�����У������ɼ��������ܵĹܵ�Ҳ����loop_t������.
 * ���loop_t�Ѿ����������ؾ�������������/���������ܵĹܵ����ܲ��ڵ�ǰloop_t��
 * ���У����ؾ���������ݻ�Ծ�ܵ�������������ܵ����䵽����loop_t���У�������Ȼ�ڵ�ǰloop_t�����У�
 * ���ȡ���ڵ�ǰ����loop_t���ص��������Ծ�ܵ���������.
 *
 * ���Ե��ú���channel_ref_check_balanceȷ���ܵ��Ƿ񱻸��ؾ�����䣬����channel_ref_check_state
 * ���ܵ���ǰ������״̬��channel_ref_close�رչܵ������۴�ʱ�ܵ������ü����Ƿ�Ϊ�㣬�ܵ����׽��ֶ���
 * ���رգ����ܵ����ü���Ϊ��ʱ��loop_t�Ż�����������.����channel_ref_equal�����ж������ܵ������Ƿ�
 * ָ��ͬһ���ܵ�.
 * 
 * ����ͨ������channel_ref_set_timeout���ùܵ��Ķ����г�ʱ���룩������������������Ĵ�������
 * channel_ref_connectʱ���һ����������һ������ֵ�������������������ӳ�ʱ���룩���������������.
 * ����channel_ref_get_socket_fd�õ��ܵ��׽��֣�����channel_ref_get_uuid�ĵ��ܵ�UUID.
 * </pre>
 * @{
 */

/**
 * ���ӹܵ����ü�������������ܵ��������µ�channel_ref_tʵ��
 *
 * channel_ref_share������ɺ󣬿����ڵ�ǰ�߳��ڷ��������߳�(loop_t)�����еĹܵ�
 * @param channel_ref channel_ref_tʵ��
 * @return channel_ref_tʵ��
 */
extern channel_ref_t* channel_ref_share(channel_ref_t* channel_ref);

/**
 * ���ٹܵ����ü�����������channel_ref_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
extern void channel_ref_leave(channel_ref_t* channel_ref);

/**
 * ���ܵ�ת��Ϊ�����ܵ�
 *
 * ����������ܵ����ܵ������ӽ�ʹ��������ܵ���ͬ�ķ��ͻ���������������ƺͽ��ܻ�������������,
 * channel_ref_accept�����ܵ������ӽ������ؾ��⣬ʵ���������ĸ�loop_t��������ʵ�����е����
 * @param channel_ref channel_ref_tʵ��
 * @param ip IP
 * @param port �˿�
 * @param backlog �ȴ��������ޣ�listen())
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int channel_ref_accept(channel_ref_t* channel_ref, const char* ip, int port, int backlog);

/**
 * ��������
 *
 * ����channel_ref_connect�Ĺܵ��ᱻ���ؾ��⣬ʵ���������ĸ�loop_t��������ʵ�����е����
 * @param channel_ref channel_ref_tʵ��
 * @param ip IP
 * @param port �˿�
 * @param timeout ���ӳ�ʱ���룩
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int channel_ref_connect(channel_ref_t* channel_ref, const char* ip, int port, int timeout);

/**
 * ���·�������
 *
 * <pre>
 * ��ʱ�Ĺܵ������رգ������¹ܵ��������¹ܵ���ʹ��ԭ�йܵ������ԣ������ص��������û�ָ��
 * ���timeout����Ϊ0����ʹ��ԭ�е����ӳ�ʱ�����timeout>0��ʹ���µ����ӳ�ʱ
 * </pre>
 * @param channel_ref channel_ref_tʵ��
 * @param timeout ���ӳ�ʱ���룩
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int channel_ref_reconnect(channel_ref_t* channel_ref, int timeout);

/**
 * ���ùܵ��Զ�����
 * <pre>
 * auto_reconnectΪ����ֵ�����Զ�����
 * </pre>
 * @param channel_ref channel_ref_tʵ��
 * @param auto_reconnect �Զ�������־
 */
extern void channel_ref_set_auto_reconnect(channel_ref_t* channel_ref, int auto_reconnect);

/**
 * ���ܵ��Ƿ������Զ�����
 * @param channel_ref channel_ref_tʵ��
 * @retval 0 δ����
 * @retval ���� ����
 */
extern int channel_ref_check_auto_reconnect(channel_ref_t* channel_ref);

/**
 * ���ܵ��Ƿ���ͨ�����ؾ����������ǰ��loop_t
 * @param channel_ref channel_ref_tʵ��
 * @retval 0 ����
 * @retval ��0 ��
 */
extern int channel_ref_check_balance(channel_ref_t* channel_ref);

/**
 * ���ܵ���ǰ״̬
 * @param channel_ref channel_ref_tʵ��
 * @param state ��Ҫ���Ե�״̬
 * @retval 1 ��
 * @retval 0 ����
 */
extern int channel_ref_check_state(channel_ref_t* channel_ref, channel_state_e state);

/**
 * �رչܵ�
 * @param channel_ref channel_ref_tʵ��
 */
extern void channel_ref_close(channel_ref_t* channel_ref);

/**
 * ȡ�ùܵ��׽���
 * @param channel_ref channel_ref_tʵ��
 * @return �׽���
 */
extern socket_t channel_ref_get_socket_fd(channel_ref_t* channel_ref);

/**
 * ȡ�ùܵ�������
 * @param channel_ref channel_ref_tʵ��
 * @return stream_tʵ��
 */
extern stream_t* channel_ref_get_stream(channel_ref_t* channel_ref);

/**
 * ȡ�ùܵ����������¼�ѭ��
 * @param channel_ref channel_ref_tʵ��
 * @return loop_tʵ��
 */
extern loop_t* channel_ref_get_loop(channel_ref_t* channel_ref);

/**
 * ���ùܵ��¼��ص�
 *
 * �¼��ص����ڹ�����loop_tʵ�������߳��ڱ��ص�
 * @param channel_ref channel_ref_tʵ��
 * @param cb �ص�����
 */
extern void channel_ref_set_cb(channel_ref_t* channel_ref, channel_ref_cb_t cb);

/**
 * ���ùܵ����г�ʱ
 *
 * �ܵ����г�ʱ������������Ϊ�жϣ���timeout�����δ�пɶ����ݼȴ�����ʱ
 * @param channel_ref channel_ref_tʵ��
 * @param timeout ��ʱ���룩
 */
extern void channel_ref_set_timeout(channel_ref_t* channel_ref, int timeout);

/**
 * ȡ�öԶ˵�ַ
 * @param channel_ref channel_ref_tʵ��
 * @return address_tʵ��
 */
extern address_t* channel_ref_get_peer_address(channel_ref_t* channel_ref);

/**
 * ȡ�ñ��ص�ַ
 * @param channel_ref channel_ref_tʵ��
 * @return address_tʵ��
 */
extern address_t* channel_ref_get_local_address(channel_ref_t* channel_ref);

/**
 * ��ȡ�ܵ�UUID
 * @param channel_ref channel_tʵ��
 * @return �ܵ�UUID
 */
extern uint64_t channel_ref_get_uuid(channel_ref_t* channel_ref);

/**
 * ���������ܵ������Ƿ�ָ��ͬһ���ܵ�
 * @param a channel_tʵ��
 * @param b channel_tʵ��
 * @retval 0 ��ͬ
 * @retval ���� ��ͬ 
 */
extern int channel_ref_equal(channel_ref_t* a, channel_ref_t* b);

/**
 * ���ùܵ��û�����
 * @param channel_ref channel_ref_tʵ��
 * @param data �û�����ָ��
 */
extern void channel_ref_set_user_data(channel_ref_t* channel_ref, void* data);

/**
 * ��ȡ�ܵ��û�����
 * @param channel_ref channel_ref_tʵ��
 * @return �û�����ָ��
 */
extern void* channel_ref_get_user_data(channel_ref_t* channel_ref);

/** @} */

#endif /* CHANNEL_REF_API_H */
