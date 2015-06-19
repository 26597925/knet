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

#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>
#include <limits.h>
#include <assert.h>

#if defined(WIN32)
    #define _WIN32_WINNT 0X0500 /* TryEnterCriticalSection */
    #if defined(FD_SETSIZE)
        #undef FD_SETSIZE
        #define FD_SETSIZE 1024
    #else
        #define FD_SETSIZE 1024
    #endif /* defined(FD_SETSIZE) */
    #include <winsock2.h>
    #include <mswsock.h>
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
    #include <process.h>
    #if defined(_MSC_VER )
        #pragma comment(lib,"wsock32.lib")
    #endif /* defined(_MSC_VER) */
    typedef SOCKET socket_t;
    typedef int socket_len_t;
    typedef uintptr_t thread_id_t;
    typedef DWORD sys_error_t;
    typedef volatile LONG atomic_counter_t;
    typedef signed char int8_t;
    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef signed short int16_t;
    typedef unsigned int uint32_t;
    typedef signed int int32_t;
    typedef unsigned long long uint64_t ;
    typedef signed long long int64_t;
    #ifndef PATH_MAX
        #define PATH_MAX MAX_PATH
    #endif /* PATH_MAX */
#else
    #include <stdint.h>
    #include <errno.h>
    #include <netdb.h>
    #include <sys/types.h>
    #include <sys/time.h>
    #include <netinet/in.h>
    #include <sys/socket.h>
    #include <arpa/inet.h>
    #include <fcntl.h>
    #include <unistd.h>
    #include <pthread.h>
    #include <linux/tcp.h>
    #include <sys/epoll.h>
    #define socket_len_t socklen_t
    #define thread_id_t pthread_t
    #define socket_t int
    #define sys_error_t int
    #define atomic_counter_t volatile int
#endif /* defined(WIN32) */

#define float32_t float
#define float64_t double

#ifndef INT_MAX
/* from stdint.h */
#define INT_MAX  2147483647 /* maximum (signed) int value */
#endif /* INT_MAX */

#define create(type)                  (type*)malloc(sizeof(type))
#define create_raw(size)              (char*)malloc(size)
#define create_type(type, size)       (type*)malloc(size)
#define rcreate_raw(ptr, size)        (char*)realloc(ptr, size)
#define rcreate_type(type, ptr, size) (type*)realloc(ptr, size)
#define destroy(ptr)                  free(ptr)

#ifndef min
#define min(a, b) ((a) < (b) ? (a) : (b))
#endif

typedef struct _loop_t loop_t;
typedef struct _channel_t channel_t;
typedef struct _channel_ref_t channel_ref_t;
typedef struct _address_t address_t;
typedef struct _lock_t lock_t;
typedef struct _loop_balancer_t loop_balancer_t;
typedef struct _thread_runner_t thread_runner_t;
typedef struct _stream_t stream_t;
typedef struct _dlist_t dlist_t;
typedef struct _dlist_node_t dlist_node_t;
typedef struct _ringbuffer_t ringbuffer_t;
typedef struct _buffer_t buffer_t;
typedef struct _broadcast_t broadcast_t;
typedef struct _ktimer_loop_t ktimer_loop_t;
typedef struct _ktimer_t ktimer_t;
typedef struct _logger_t logger_t;
typedef struct _krpc_t krpc_t;
typedef enum   _krpc_type_e krpc_type_e;
typedef struct _krpc_number_t krpc_number_t;
typedef struct _krpc_string_t krpc_string_t;
typedef struct _krpc_vector_t krpc_vector_t;
typedef struct _krpc_object_t krpc_object_t;
typedef struct _hash_t hash_t;
typedef struct _hash_value_t hash_value_t;

/* �ܵ���Ͷ���¼� */
typedef enum _channel_event_e {
    channel_event_recv = 1,
    channel_event_send = 2,
} channel_event_e;

/* �ܵ�״̬ */
typedef enum _channel_state_e {
    channel_state_connect = 1, /* �����������ӣ�����δ��� */
    channel_state_accept = 2,  /* ���� */
    channel_state_close = 4,   /* �ܵ��ѹر� */
    channel_state_active = 8,  /* �ܵ��Ѽ�������շ����� */
} channel_state_e;

/* ��ʱ������ */
typedef enum _ktimer_type_e {
    ktimer_type_once   = 1, /* ����һ�� */
    ktimer_type_period = 2, /* ���� */
    ktimer_type_times  = 3, /* ������� */
} ktimer_type_e;

/* ���ؾ������� */
typedef enum _loop_balance_option_e {
	loop_balancer_in  = 1, /* ��������loop_t�Ĺܵ��ڵ�ǰloop_t���� */
	loop_balancer_out = 2, /* ������ǰloop_t�Ĺܵ�������loop_t�ڸ��� */
} loop_balance_option_e;

/* ������ */
typedef enum _error_e {
    error_ok = 0,
    error_fail,
    error_recv_fail,
    error_send_fail,
    error_send_patial,
    error_recv_buffer_full,
    error_recv_nothing,
    error_connect_fail,
    error_bind_fail,
    error_listen_fail,
    error_ref_nonzero,
    error_loop_fail,
    error_loop_attached,
    error_loop_not_found,
    error_loop_impl_init_fail,
    error_thread_start_fail,
    error_already_close,
    error_impl_add_channel_ref_fail,
    error_getpeername,
    error_getsockname,
    error_not_correct_domain,
    error_multiple_start,
    error_not_connected,
    error_logger_write,
    error_set_tls_fail,
    error_rpc_dup_id,
    error_rpc_unknown_id,
    error_rpc_unknown_type,
	error_rpc_cb_fail,
    error_rpc_cb_fail_close,
    error_rpc_cb_close,
	error_rpc_next,
    error_rpc_not_enough_bytes,
	error_rpc_vector_out_of_bound,
    error_rpc_marshal_fail,
	error_rpc_unmarshal_fail,
    error_recvbuffer_not_enough,
    error_recvbuffer_locked,
    error_stream_enable,
    error_stream_disable,
    error_stream_flush,
    error_stream_buffer_overflow,
} error_e;

/* �ܵ��ص��¼� */
typedef enum _channel_cb_event_e {
    channel_cb_event_connect = 1,          /* ������� */
    channel_cb_event_accept = 2,           /* �ܵ������������������� */ 
    channel_cb_event_recv = 4,             /* �ܵ������ݿ��Զ� */
    channel_cb_event_send = 8,             /* �ܵ��������ֽڣ����� */
    channel_cb_event_close = 16,           /* �ܵ��ر� */
    channel_cb_event_timeout = 32,         /* �ܵ������� */
    channel_cb_event_connect_timeout = 64, /* �����������ӣ������ӳ�ʱ */
} channel_cb_event_e;

/* ��־�ȼ� */
typedef enum _logger_level_e {
    logger_level_verbose = 1, /* verbose - ������� */
    logger_level_information, /* information - ��ʾ��Ϣ */
    logger_level_warning,     /* warning - ���� */ 
    logger_level_error,       /* error - ���� */
    logger_level_fatal,       /* fatal - �������� */
} logger_level_e;

/* ��־ģʽ */
typedef enum _logger_mode_e {
    logger_mode_file = 1,     /* ������־�ļ� */
    logger_mode_console = 2,  /* ��ӡ��stderr */
    logger_mode_flush = 4,    /* ÿ��д��־ͬʱ��ջ��� */
    logger_mode_override = 8, /* �����Ѵ��ڵ���־�ļ� */
} logger_mode_e;

/* RPC������ */
typedef enum _rpc_error_e {
	rpc_ok = 0,      /* �ɹ� */
    rpc_close,       /* ���Դ��󣬹ر� */
    rpc_error,       /* ���󣬵����ر� */
	rpc_error_close, /* �����ҹر� */
} rpc_error_e;

/* �̺߳��� */
typedef void (*thread_func_t)(thread_runner_t*);
/* �ܵ��¼��ص����� */
typedef void (*channel_ref_cb_t)(channel_ref_t*, channel_cb_event_e);
/* ��ʱ���ص����� */
typedef void (*ktimer_cb_t)(ktimer_t*, void*);
/* RPC�ص����� */
typedef int (*krpc_cb_t)(krpc_object_t*);
/* ��ϣ��Ԫ�����ٺ��� */
typedef void (*hash_dtor_t)(void*);

/* ������Ҫ�� ������ͬѡȡ�� */
#if defined(WIN32)
    #define LOOP_IOCP 1    /* IOCP */
    #define LOOP_SELECT 0  /* select */
#else
    #define LOOP_EPOLL 1   /* epoll */
    #define LOOP_SELECT 0  /* select */
#endif /* defined(WIN32) */

#define LOGGER_ON 1 /* �Ƿ�����־ */
#define LOGGER_MODE (logger_mode_file | logger_mode_console | logger_mode_flush | logger_mode_override) /* ��־ģʽ */
#define LOGGER_LEVEL logger_level_verbose /* ��־�ȼ� */

#endif /* CONFIG_H */
