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

#ifndef KRPC_CPP_H
#define KRPC_CPP_H

#include <cstdint>
#include "krpc_ostream.h"

class krpc_gen_t;
class krpc_field_t;
class krpc_attribute_t;

/**
 * C++����������
 */
class krpc_gen_cpp_t {
public:
    /**
     * ����
     * @param rpc_gen krpc_gen_tʵ��
     */
    krpc_gen_cpp_t(krpc_gen_t* rpc_gen);

    /**
     * ����
     */
    ~krpc_gen_cpp_t();

    /**
     * ���ɴ���
     */
    void lang_gen_code();

private:
    /**
     * ����RPC���ÿ����
     */
    void lang_gen_framework(krpc_ostream_t& header, krpc_ostream_t& source);

    /**
     * ����RPC���ÿ���� - ����
     */
    void lang_gen_framework_decls(krpc_ostream_t& header);

    /**
     * ����RPC���ÿ���� - ����
     */
    void lang_gen_framework_impls(krpc_ostream_t& source);

    /**
     * ����ͷ�ļ�
     */
    void lang_gen_includes(krpc_ostream_t& header, krpc_ostream_t& source);

    /**
     * ���Զ���Ԥ������
     */
    void lang_gen_attributes_pre_decls(krpc_ostream_t& header);

    /**
     * ���Զ�����ش�������
     */
    void lang_gen_attributes(krpc_ostream_t& header, krpc_ostream_t& source);

    /**
     * ���Զ�����ش������� - ����
     */
    void lang_gen_attribute_method_decl(krpc_attribute_t* attribute,
        krpc_ostream_t& header);

    /**
     * ���Զ�����ش������� - ����
     */
    void lang_gen_attribute_method_impl(krpc_attribute_t* attribute,
        krpc_ostream_t& source);

    /**
     * �����ֶ� - ����
     */
    void lang_gen_attribute_field_decl(krpc_ostream_t& header,
        krpc_field_t* field);

    /**
     * RPC���� - ����
     */
    void lang_gen_rpc_call_decls(krpc_ostream_t& header);

    /**
     * RPC���� - ����
     */
    void lang_gen_rpc_call_impls(krpc_ostream_t& source);

    /**
     * RPC���� - ����
     */
    void lang_gen_rpc_call_param_decl(krpc_ostream_t& header,
        krpc_field_t* field);

    /**
     * RPC���� - proxy����
     */
    void lang_gen_rpc_call_impl_proxy(krpc_attribute_t* attribute,
        krpc_ostream_t& source);

    /**
     * RPC���� - stub����
     */
    void lang_gen_rpc_call_impl_stub(krpc_attribute_t* attribute,
        krpc_ostream_t& source, const std::string& rpc_name);

    /**
     * �������Զ��� - marshal/unmarshal����
     */
    void lang_gen_attribute_marshal_method_decls(krpc_ostream_t& header);

    /**
     * ���Զ��� - marshal����
     */
    void lang_gen_attribute_marshal_method_decl(krpc_attribute_t* attribute,
        krpc_ostream_t& header);

    /**
     * �������Զ��� - marshal����
     */
    void lang_gen_attribute_marshal_method_impls(krpc_ostream_t& source);

    /**
     * ������Ļ���
     */
    void lang_gen_attribute_method_print_impl(krpc_attribute_t* attribute,
        krpc_ostream_t& source);

    /**
     * ���Զ��� - marshal����
     */
    void lang_gen_attribute_marshal_method_impl(krpc_attribute_t* attribute,
        krpc_ostream_t& source);

    /**
     * �������Զ��� - unmarshal����
     */
    void lang_gen_attribute_unmarshal_method_impls(krpc_ostream_t& source);

    /**
     * ���Զ��� - unmarshal����
     */
    void lang_gen_attribute_unmarshal_method_impl(krpc_attribute_t* attribute,
        krpc_ostream_t& source);

    /**
     * ���Զ��� - ������ - unmarshal����
     */
    void lang_gen_attribute_unmarshal_field_not_array(krpc_field_t* field,
        krpc_ostream_t& source, const std::string& name, int index);

    /**
     * ���Զ��� - �������ȡ - unmarshal����
     */
    void lang_gen_attribute_unmarshal_field_not_array_get(
        krpc_ostream_t& source, const std::string& name,
            const std::string& method_name, int index);

    /**
     * ���Զ��� - ���� - unmarshal����
     */
    void lang_gen_attribute_unmarshal_field_array(krpc_field_t* field,
        krpc_ostream_t& source, const std::string& name, int index);

    /**
     * ���Զ��� �� ����Ԫ�� - unmarshal
     */
    void lang_gen_attribute_unmarshal_field_array_element(
        krpc_ostream_t& source, const std::string& name,
            const std::string& type_name);

    /**
     * �ֶ� - marshal����
     */
    void lang_gen_field_marshal_impl(krpc_field_t* field,
        krpc_ostream_t& source, bool param = false);

    /**
     * �ֶ� - ������ - marshal����
     */
    void lang_gen_field_marshal_impl_not_array(krpc_field_t* field,
        krpc_ostream_t& source, const std::string& holder_name = "",
            const std::string& vector_name = "",
                const std::string& whites = "");

    /**
     * �ֶ� - ���� - marshal����
     */
    void lang_gen_field_marshal_impl_not_array_set(krpc_field_t* field,
        krpc_ostream_t& source, const std::string& holder,
            const std::string& v, const std::string& method_name,
                const std::string& suffix, const std::string& whites);

    /**
     * �ֶ� - ���� - marshal����
     */
    void lang_gen_field_marshal_impl_array(krpc_field_t* field,
        krpc_ostream_t& source, bool param, const std::string& whites = "");

    /**
     * �ֶ� - unmarshal����
     */
    void lang_gen_field_unmarshal_impl(krpc_field_t* field,
        krpc_ostream_t& source, int index);

    /**
     * �ֶ� - ������ - marshal����
     */
    void lang_gen_field_unmarshal_impl_not_array(krpc_field_t* field,
        krpc_ostream_t& source, int index);

    /**
     * �ֶ� - ������, ��Ϊ���������ڵ��� - unmarshal����
     */
    void lang_gen_field_unmarshal_impl_not_array_inline(krpc_field_t* field,
        krpc_ostream_t& source, int index);

    /**
     * �ֶ� - �������ȡ, ��Ϊ���������ڵ��� - unmarshal����
     */
    void lang_gen_field_unmarshal_impl_not_array_inline_get(
        krpc_ostream_t& source, int index,
            const std::string& method_name);

    /**
     * �ֶ� - �������ȡ - unmarshal����
     */
    void lang_gen_field_unmarshal_impl_not_array_get(krpc_ostream_t& source,
        int index, const std::string& method_name);

    /**
     * �ֶ� - ���� - unmarshal����
     */
    void lang_gen_field_unmarshal_impl_array(krpc_field_t* field,
        krpc_ostream_t& source, int index);

    /**
     * ȡ�������ֶ�������
     */
    std::string lang_field_find_type_name(krpc_field_t* field);

    /**
     * ȡ�ò����ֶ�������
     */
    std::string lang_param_find_type_name(krpc_field_t* field);

private:
    krpc_gen_t* _rpc_gen; // �������������
    uint16_t    _rpc_id;  // RPC����ID
};

#endif // KRPC_CPP_H
