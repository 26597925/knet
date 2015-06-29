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

#ifndef KRPC_PARSER_H
#define KRPC_PARSER_H

#include <list>
#include <map>
#include <exception>
#include <string>
#include "krpc_lexer.h"

class krpc_field_t;

/*
 * �ֶ�����
 */
enum {
    krpc_field_type_i8        = 1,
    krpc_field_type_i16       = 2,
    krpc_field_type_i32       = 4,
    krpc_field_type_i64       = 8,
    krpc_field_type_ui8       = 16,
    krpc_field_type_ui16      = 32,
    krpc_field_type_ui32      = 64,
    krpc_field_type_ui64      = 128,
    krpc_field_type_f32       = 256,
    krpc_field_type_f64       = 512,
    krpc_field_type_string    = 1024,
    krpc_field_type_array     = 2048,
    krpc_field_type_attribute = 4096,
    krpc_field_type_rpc       = 8192,
};

/*
 * ����
 */
class krpc_attribute_t {
public:
    typedef std::list<krpc_field_t*> field_list_t;
    typedef field_list_t::iterator   iterator;

public:
    /*
     * ����
     * @param name ������
     */
    krpc_attribute_t(const std::string& name);

    /*
     * ����
     */
    ~krpc_attribute_t();
    
    /*
     * ���������ֶ�
     * @param field krpc_field_tʵ��
     */
    void push_field(krpc_field_t* field);

    /*
     * ��ȡ������
     * @return ������
     */
    const std::string& get_name();

    /*
     * ��ȡ�ֶ��б�
     * @return �ֶ��б�
     */
    field_list_t& get_field_list();

private:
    field_list_t _fields; // �ֶ��б�
    std::string  _name;   // ������
};

/*
 * �ֶ�
 */
class krpc_field_t {
public:
    /*
     * ����
     * @param type �ֶ�����
     */
    krpc_field_t(int type);

    /*
     * ����
     */
    ~krpc_field_t();

    /*
     * �����ֶ�����
     * @param type �ֶ�����
     */
    void set_type(int type);

    /*
     * ����ֶ��Ƿ�������
     * @retval true ������
     * @retval false ��������
     */
    bool check_array();

    /*
     * ����ֶ�����
     * @param type �ֶ�����
     * @retval true ��
     * @retval false ����
     */
    bool check_type(int type);

    /*
     * �����ֶ���
     * @param field_name �ֶ���
     */
    void set_field_name(const std::string& field_name);

    /*
     * �����ֶ�������
     * @param field_type �ֶ�������
     */
    void set_field_type(const std::string& field_type);

    /*
     * ȡ���ֶ���
     * @return �ֶ���
     */
    const std::string& get_field_name();

    /*
     * ȡ���ֶ�������
     * @return �ֶ�������
     */
    const std::string& get_field_type();

private:
    /*
     * ת��token���͵��ֶ�����
     * @return �ֶ�����
     */
    int convert(int type);

private:
    std::string _field_name; // �ֶ���
    std::string _field_type; // �ֶ�������
    int         _type;       // �ֶ�����
};

/*
 * RPC����
 */
class krpc_rpc_call_t {
public:
    /*
     * ����
     * @param rpc_name ��������
     */
    krpc_rpc_call_t(const std::string& rpc_name);

    /*
     * ����
     */
    ~krpc_rpc_call_t();

    /*
     * ȡ�ú�����
     * @return ������
     */
    const std::string& get_name();

    /*
     * ȡ�ò�����
     * @return krpc_attribute_tʵ��
     */
    krpc_attribute_t* get_attribute();

private:
    std::string       _name;      // ������
    krpc_attribute_t* _attribute; // ������
};

/*
 * �﷨������
 */
class krpc_parser_t {
public:
    typedef std::map<std::string, krpc_attribute_t*> object_map_t;
    typedef std::map<std::string, krpc_rpc_call_t*>  rpc_call_map_t;

public:
    /*
     * ����
     * @param parent ��������
     * @param dir �ļ�����Ŀ¼
     * @param file_name �ļ���
     */
    krpc_parser_t(krpc_parser_t* parent, const char* dir,
        const char* file_name);

    /*
     * ����
     */
    ~krpc_parser_t();

    /*
     * ����
     */
    void parse() throw(std::exception);

    /*
     * ��ȡ�����б�
     * @return �����б�
     */
    object_map_t& get_attributes();

    /*
     * ��ȡRPC�����б�
     * @return RPC�����б�
     */
    rpc_call_map_t& get_rpc_calls();

private:
    /*
     * ȡ����һ��token
     * @return krpc_token_tʵ��
     */
    krpc_token_t* next_token();

    /*
     * ����chunk
     * @param token ��ǰtoken
     */
    void parse_trunk(krpc_token_t* token);

    /*
     * ��������
     * @param token ��ǰtoken
     * @return krpc_attribute_tʵ��
     */
    krpc_attribute_t* parse_attribute(krpc_token_t* token);

    /*
     * ����RPC����
     * @param token ��ǰtoken
     * @return krpc_rpc_call_tʵ��
     */
    krpc_rpc_call_t* parse_rpc_call(krpc_token_t* token);

    /*
     * ���������ļ�
     * @param token ��ǰtoken
     */
    void parse_import(krpc_token_t* token);

    /*
     * �����ֶ�
     * @param token ��ǰtoken
     * @return krpc_field_tʵ��
     */
    krpc_field_t* parse_field(krpc_token_t* token);

private:
    object_map_t   _objects;        // ���Ա�
    rpc_call_map_t _rpc_calls;      // RPC������
    std::string    _file_name;      // �ļ���
    std::string    _dir;            // ��ǰĿ¼
    krpc_lexer_t*  _lexer;          // token������
    krpc_parser_t* _parent;         // ��������
    krpc_parser_t* _current_parser; // ��ǰ������
};

#endif // KRPC_PARSER_H
