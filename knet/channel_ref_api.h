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

/*
 * ���ӹܵ����ü�������������ܵ��������µ�channel_ref_tʵ��
 * channel_ref_share������ɺ󣬿����ڵ�ǰ�߳��ڷ��������߳�(loop_t)�����еĹܵ�
 * @param channel_ref channel_ref_tʵ��
 * @return channel_ref_tʵ��
 */
extern channel_ref_t* channel_ref_share(channel_ref_t* channel_ref);

/*
 * ���ٹܵ����ü�����������channel_ref_tʵ��
 * @param channel_ref channel_ref_tʵ��
 */
extern void channel_ref_leave(channel_ref_t* channel_ref);

/*
 * ��������
 * ����channel_ref_connect�Ĺܵ����ᱻ���ؾ��⣬���ڵ�ǰloop_t�����е��߳�����
 * @param channel_ref channel_ref_tʵ��
 * @param ip IP
 * @param port �˿�
 * @param timeout ���ӳ�ʱ���룩
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int channel_ref_connect(channel_ref_t* channel_ref, const char* ip, int port, int timeout);

/*
 * ���ܵ�ת��Ϊ�����ܵ�
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

/*
 * ��������ܵ�����input�����������Զ�д��output, output���������ݻ��Զ�д��input
 * �ʺ������Զ��ַ����ݰ����������ϵĿͻ��˹ܵ����Ӧ�������ܵ����
 * @param channel_ref channel_ref_tʵ��
 * @param partner channel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int channel_ref_tie(channel_ref_t* channel_ref, channel_ref_t* partner);

/*
 * ����ܵ����
 * @param channel_ref channel_ref_tʵ��
 * @param partner channel_ref_tʵ��
 * @retval error_ok �ɹ�
 * @retval ���� ʧ��
 */
extern int channel_ref_untie(channel_ref_t* channel_ref, channel_ref_t* partner);

/*
 * ���ܵ��Ƿ���ͨ�����ؾ����������ǰ��loop_t
 * @param channel_ref channel_ref_tʵ��
 * @retval 0 ����
 * @retval ��0 ��
 */
extern int channel_ref_check_balance(channel_ref_t* channel_ref);

/*
 * ���ܵ���ǰ״̬
 * @param channel_ref channel_ref_tʵ��
 * @param state ��Ҫ���Ե�״̬
 * @retval 1 ��
 * @retval 0 ����
 */
extern int channel_ref_check_state(channel_ref_t* channel_ref, channel_state_e state);

/*
 * �رչܵ�
 * @param channel_ref channel_ref_tʵ��
 */
extern void channel_ref_close(channel_ref_t* channel_ref);

/*
 * ȡ�ùܵ��׽���
 * @param channel_ref channel_ref_tʵ��
 * @return �׽���
 */
extern socket_t channel_ref_get_socket_fd(channel_ref_t* channel_ref);

/*
 * ȡ�ùܵ�������
 * @param channel_ref channel_ref_tʵ��
 * @return stream_tʵ��
 */
extern stream_t* channel_ref_get_stream(channel_ref_t* channel_ref);

/*
 * ȡ�ùܵ����������¼�ѭ��
 * @param channel_ref channel_ref_tʵ��
 * @return loop_tʵ��
 */
extern loop_t* channel_ref_get_loop(channel_ref_t* channel_ref);

/*
 * ���ùܵ��¼��ص�
 * �¼��ص����ڹ�����loop_tʵ�������߳��ڱ��ص�
 * @param channel_ref channel_ref_tʵ��
 * @paramn cb �ص�����
 */
extern void channel_ref_set_cb(channel_ref_t* channel_ref, channel_ref_cb_t cb);

/*
 * ���ùܵ����г�ʱ
 * �ܵ����г�ʱ������������Ϊ�жϣ���timeout�����δ�пɶ����ݼȴ�����ʱ
 * @param channel_ref channel_ref_tʵ��
 * @param timeout ��ʱ���룩
 */
extern void channel_ref_set_timeout(channel_ref_t* channel_ref, int timeout);

/*
 * ȡ�öԶ˵�ַ
 * @param channel_ref channel_ref_tʵ��
 * @return address_tʵ��
 */
extern address_t* channel_ref_get_peer_address(channel_ref_t* channel_ref);

/*
 * ȡ�ñ��ص�ַ
 * @param channel_ref channel_ref_tʵ��
 * @return address_tʵ��
 */
extern address_t* channel_ref_get_local_address(channel_ref_t* channel_ref);

#endif /* CHANNEL_REF_API_H */
