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

#include <stdarg.h>
#include "node_config.h"
#include "framework.h"
#include "node.h"

#define MAX_CONCERN_SIZE 64

struct _node_config_t {
    int                    root;                           /* �Ƿ��Ǹ��ڵ� */
    int                    worker_count;                   /* �����߳����� */
    knode_t*               node;                           /* �ڵ� */
    uint32_t               id;                             /* �ڵ�ID */
    uint32_t               type;                           /* �ڵ����� */
    int                    concern_pos;                    /* ��ע�������鵱ǰ�±� */
    uint32_t               concern[MAX_CONCERN_SIZE];      /* ��ע�������� */
    char                   ip[32];                         /* ����IP */
    int                    port;                           /* �����˿� */
    char                   root_ip[32];                    /* ���ڵ�IP */
    int                    root_port;                      /* ���ڵ�˿� */
    char                   monitor_ip[32];                 /* ��ؼ���IP */
    int                    monitor_port;                   /* ��ؼ����˿� */
    char                   manage_ip[32];                  /* �������IP */
    int                    manage_port;                    /* ��������˿� */
    knet_node_cb_t         node_cb;                        /* �ڵ�ص����� */
    knet_node_manage_cb_t  manage_cb;                      /* ��������ص����� */
    knet_node_monitor_cb_t monitor_cb;                     /* �ڵ�Կջص����� */
    int                    black_ip_filter_auto_save;      /* �Ƿ��Զ�����IP������ */
    char                   black_ip_filter_path[PATH_MAX]; /* IP�������ļ�·�� */
    int                    white_ip_filter_auto_save;      /* �Ƿ��Զ�����IP������ */
    char                   white_ip_filter_path[PATH_MAX]; /* IP�������ļ�·�� */
    int                    idle_timeout;                   /* �ڵ�ܵ����� */
    int                    max_recv_buffer_length;         /* �ڵ�ܵ����ջ�������󳤶� */
    int                    max_send_list_count;            /* �ڵ�ܵ�����������󳤶� */
    int                    max_output_buffer_length;       /* ������������������󳤶� */
};

void knet_node_config_set_node_channel_max_recv_buffer_length(knode_config_t* c, int max_recv_buffer_length) {
    verify(c);
    c->max_recv_buffer_length = max_recv_buffer_length;
}

int knet_node_config_get_node_channel_max_recv_buffer_length(knode_config_t* c) {
    verify(c);
    return c->max_recv_buffer_length;
}

void knet_node_config_set_node_channel_max_send_list_count(knode_config_t* c, int max_send_list_count) {
    verify(c);
    c->max_send_list_count = max_send_list_count;
}

int knet_node_config_get_node_channel_max_send_list_count(knode_config_t* c) {
    verify(c);
    return c->max_send_list_count;
}

void knet_node_config_set_node_channel_idle_timeout(knode_config_t* c, int timeout) {
    verify(c);
    c->idle_timeout = timeout;
}

int knet_node_config_get_node_channel_idle_timeout(knode_config_t* c) {
    verify(c);
    return c->idle_timeout;
}

knode_config_t* knet_node_config_create(knode_t* node) {
    knode_config_t* c = 0;
    verify(node);
    c = create(knode_config_t);
    verify(c);
    memset(c, 0, sizeof(knode_config_t));
    c->node                     = node;
    c->worker_count             = 1;
    c->max_recv_buffer_length   = 16 * 1024;
    c->max_send_list_count      = INT_MAX;
    c->max_output_buffer_length = 1024;
    return c;
}

void knet_node_config_destroy(knode_config_t* c) {
    verify(c);
    destroy(c);
}

int knet_node_config_set_identity(knode_config_t* c, uint32_t type, uint32_t id) {
    verify(c);
    verify(type);
    verify(id);
    c->id   = id;
    c->type = type;
    return error_ok;
}

int knet_node_config_set_concern_type(knode_config_t* c, ...) {
    va_list  arg_ptr;
    uint32_t type = 0;
    verify(c);
    va_start(arg_ptr, c);
    type = va_arg(arg_ptr, uint32_t);
    for (; type; ) {
        c->concern[c->concern_pos++] = type;
        type = va_arg(arg_ptr, uint32_t);
    }
    va_end(arg_ptr);
    return error_ok;
}

int knet_node_config_concern(knode_config_t* c, int type) {
    int i = 0;
    verify(c);
    verify(type);
    if (!c->concern_pos) { /* δ���ù�ע�ڵ����ͣ�Ĭ�Ϲ�עȫ�� */
        return 1;
    }
    for (; i < c->concern_pos; i++) {
        if (c->concern[i] == (uint32_t)type) {
            return 1;
        }
    }
    return 0;
}

uint32_t knet_node_config_get_type(knode_config_t* c) {
    verify(c);
    return c->type;
}

void knet_node_config_set_worker_thread_count(knode_config_t* c, int worker_count) {
    verify(c);
    verify(worker_count > 0);
    c->worker_count = worker_count;
}

int knet_node_config_get_worker_thread_count(knode_config_t* c) {
    verify(c);
    return c->worker_count;
}

uint32_t knet_node_config_get_id(knode_config_t* c) {
    verify(c);
    return c->id;
}

int knet_node_config_set_address(knode_config_t* c, const char* ip, int port) {
    verify(c);
    verify(ip);
    verify(port);
    strcpy(c->ip, ip);
    c->port = port;
    return error_ok;
}

const char* knet_node_config_get_ip(knode_config_t* c) {
    verify(c);
    return c->ip;
}

int knet_node_config_get_port(knode_config_t* c) {
    verify(c);
    return c->port;
}

int knet_node_config_set_root_address(knode_config_t* c, const char* ip, int port) {
    verify(c);
    verify(ip);
    verify(port);
    strcpy(c->root_ip, ip);
    c->root_port = port;
    return error_ok;
}

const char* knet_node_config_get_root_ip(knode_config_t* c) {
    verify(c);
    return c->root_ip;
}

int knet_node_config_get_root_port(knode_config_t* c) {
    verify(c);
    return c->root_port;
}

int knet_node_config_set_root(knode_config_t* c) {
    verify(c);
    c->root = 1;
    return error_ok;
}

int knet_node_config_check_root(knode_config_t* c) {
    verify(c);
    return (c->root || (!strcmp(c->ip, c->root_ip) && (c->port == c->root_port)));
}

int knet_node_config_set_node_cb(knode_config_t* c, knet_node_cb_t cb) {
    verify(c);
    c->node_cb = cb;
    return error_ok;
}

knet_node_cb_t knet_node_config_get_node_cb(knode_config_t* c) {
    verify(c);
    return c->node_cb;
}

int knet_node_config_set_monitor_address(knode_config_t* c, const char* ip, int port) {
    verify(c);
    verify(ip);
    verify(port);
    strcpy(c->monitor_ip, ip);
    c->monitor_port = port;
    return error_ok;
}

const char* knet_node_config_get_monitor_ip(knode_config_t* c) {
    verify(c);
    return c->monitor_ip;
}

int knet_node_config_get_monitor_port(knode_config_t* c) {
    verify(c);
    return c->monitor_port;
}

int knet_node_config_set_manage_address(knode_config_t* c, const char* ip, int port) {
    verify(c);
    verify(ip);
    verify(port);
    strcpy(c->manage_ip, ip);
    c->manage_port = port;
    return error_ok;
}

const char* knet_node_config_get_manage_ip(knode_config_t* c) {
    verify(c);
    return c->manage_ip;
}

int knet_node_config_get_manage_port(knode_config_t* c) {
    verify(c);
    return c->manage_port;
}

int knet_node_config_set_manage_cb(knode_config_t* c, knet_node_manage_cb_t cb) {
    verify(c);
    c->manage_cb = cb;
    return error_ok;
}

int knet_node_config_set_monitor_cb(knode_config_t* c, knet_node_monitor_cb_t cb) {
    verify(c);
    c->monitor_cb = cb;
    return error_ok;
}

knet_node_monitor_cb_t knet_node_config_get_monitor_cb(knode_config_t* c) {
    verify(c);
    return c->monitor_cb;
}

knet_node_manage_cb_t knet_node_config_get_manage_cb(knode_config_t* c) {
    verify(c);
    return c->manage_cb;
}

int knet_node_config_set_black_ip_filter_auto_save_at_exit(knode_config_t* c, int on) {
    verify(c);
    c->black_ip_filter_auto_save = on;
    return error_ok;
}

int knet_node_config_set_black_ip_filter_file_path(knode_config_t* c, const char* path) {
    verify(c);
    verify(path);
    strcpy(c->black_ip_filter_path, path);
    return error_ok;
}

int knet_node_config_get_black_ip_filter_auto_save_at_exit(knode_config_t* c) {
    verify(c);
    return c->black_ip_filter_auto_save;
}

const char* knet_node_config_get_black_ip_filter_file_path(knode_config_t* c) {
    verify(c);
    if (c->black_ip_filter_path[0]) {
        return c->black_ip_filter_path;
    }
    return 0;
}

kframework_config_t* knet_node_config_get_framework_config(knode_config_t* c) {
    verify(c);
    return knet_framework_get_config(knet_node_get_framework(c->node));
}

void knet_node_config_set_manage_max_output_buffer_length(knode_config_t* c, int max_output_buffer_length) {
    verify(c);
    c->max_output_buffer_length = max_output_buffer_length;
}

int knet_node_config_get_manage_max_output_buffer_length(knode_config_t* c) {
    verify(c);
    return c->max_output_buffer_length;
}

int knet_node_config_set_white_ip_filter_auto_save_at_exit(knode_config_t* c, int on) {
    verify(c);
    c->white_ip_filter_auto_save = on;
    return error_ok;
}

int knet_node_config_set_white_ip_filter_file_path(knode_config_t* c, const char* path) {
    verify(c);
    verify(path);
    strcpy(c->white_ip_filter_path, path);
    return error_ok;
}

int knet_node_config_get_white_ip_filter_auto_save_at_exit(knode_config_t* c) {
    verify(c);
    return c->white_ip_filter_auto_save;
}

const char* knet_node_config_get_white_ip_filter_file_path(knode_config_t* c) {
    verify(c);
    if (c->white_ip_filter_path[0]) {
        return c->white_ip_filter_path;
    }
    return 0;
}

