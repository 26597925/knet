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

/* TODO δ������ */

#include "rpc_api.h"
#include "hash.h"
#include "channel_ref.h"
#include "stream.h"
#include "rpc_object.h"

#if defined(_MSC_VER )
    #pragma pack(push)
    #pragma pack(1)
#else
    #pragma pack(1) 
#endif /* defined(_MSC_VER) */

typedef struct krpc_header_t {
    uint16_t length;       /* �����ȣ��������ṹ�峤�� */
    uint16_t rpcid;        /* ��Ҫ���õķ���ID/���÷��ط���ID */
    uint8_t  type;         /* ���ͣ�����/����) */
    uint8_t  padding__[3]; /* 3���ֽ���䣬�ܳ���Ϊ8�ֽ� */
} krpc_header_t;

#if defined(_MSC_VER )
    #pragma pack(pop)
#else
    #pragma pack()
#endif /* defined(_MSC_VER) */

typedef enum _krpc_call_type_e {
    krpc_call_type_result = 1, /* ���� */
    krpc_call_type_call   = 2, /* ���� */
} krpc_call_type_e;

struct _krpc_t {
    hash_t* cb_table;
};

krpc_t* krpc_create() {
    krpc_t* rpc = create(krpc_t);
    assert(rpc);
    memset(rpc, 0, sizeof(krpc_t));
    rpc->cb_table = hash_create(0, 0);
    assert(rpc->cb_table);
    return rpc;
}

void krpc_destroy(krpc_t* rpc) {
    assert(rpc);
    hash_destroy(rpc->cb_table);
    destroy(rpc);
}

int krpc_add_cb(krpc_t* rpc, uint16_t rpcid, krpc_cb_t cb) {
    assert(rpc);
    assert(rpcid);
    assert(cb);
    if (hash_get(rpc->cb_table, rpcid)) {
        return error_rpc_dup_id;
    }
    return hash_add(rpc->cb_table, rpcid, cb);
}

int krpc_del_cb(krpc_t* rpc, uint16_t rpcid) {
    assert(rpc);
    assert(rpcid);
    return hash_delete(rpc->cb_table, rpcid);
}

krpc_cb_t krpc_get_cb(krpc_t* rpc, uint16_t rpcid) {
    assert(rpc);
    assert(rpcid);
    return (krpc_cb_t)hash_get(rpc->cb_table, rpcid);
}

int krpc_proc(krpc_t* rpc, stream_t* stream) {
    int            available = 0;         /* �ܵ��ڿɶ��ֽ��� */
    uint16_t       length    = 0;         /* unmarshal�ֽ���*/
    krpc_object_t* o         = 0;         /* unmarshal�õ��Ķ��� */
    krpc_cb_t      cb        = 0;         /* �ص����� */
    int            error_cb  = 0;         /* �ص���������ֵ */
    int            error     = error_ok;  /* ����������ֵ */
    krpc_header_t  header; /* RPCЭ��ͷ */
    assert(rpc);
    assert(stream);
    memset(&header, 0, sizeof(krpc_header_t));
    available = stream_available(stream);
    if (available < sizeof(krpc_header_t)) {
        /* �ֽ������� */
        return error_rpc_not_enough_bytes;
    }
    if (error_ok != stream_copy(stream, &header, sizeof(header))) {
        return error_rpc_unmarshal_fail;
    }
    if (header.length <= available) {
        if (error_ok != stream_eat(stream, sizeof(header))) {
            return error_rpc_unmarshal_fail;
        }
    }
    /* unmarshal */
    error = krpc_object_unmarshal(stream, &o, &length);
    if (error_ok != error) {
        goto error_return;
    }
    /* ���ûص� */
    if ((header.type == krpc_call_type_call) || (header.type == krpc_call_type_result)) {
        /* ����/���� */
        cb = krpc_get_cb(rpc, header.rpcid);
        if (cb == 0) {
            error = error_rpc_unknown_id;
            goto error_return;
        }
        error_cb = cb(o);
        if (error_cb == rpc_error) {
            /* ���� */
            error = error_rpc_cb_fail;
            goto error_return;
        } else if (error_cb == rpc_error_close) {
            /* ���󲢹ر� */
            error = error_rpc_cb_fail_close;
            goto error_return;
        } else if (error_cb == rpc_close) {
            /* Ҫ��ر� */
            error = error_rpc_cb_close;
            goto error_return;
        } else if (error_cb == rpc_ok) {
            /* ok */
            goto error_return;
        } else {
            /* δ֪����ֵ������ */
        }
    } else {
        /* �������� */
        error = error_rpc_unknown_type;
    }
error_return:
    if (o) {
        krpc_object_destroy(o);
    }
    return error;
}

int krpc_call(krpc_t* rpc, stream_t* stream, uint16_t rpcid, krpc_object_t* o) {
    krpc_header_t header; /* RPCЭ��ͷ */
    assert(rpc);
    assert(stream);
    assert(rpcid);
    assert(o);
    memset(&header, 0, sizeof(krpc_header_t));
    header.rpcid  = rpcid;
    header.type   = krpc_call_type_call;
    header.length = sizeof(krpc_header_t) + krpc_object_get_marshal_size(o);
    /* ����Э��ͷ */
    if (error_ok != stream_push(stream, &header, sizeof(header))) {
        return error_rpc_marshal_fail;
    }
    /* marshal */
    return krpc_object_marshal(o, stream, 0);
}
