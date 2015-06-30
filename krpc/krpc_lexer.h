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

#ifndef KRPC_LEXER_H
#define KRPC_LEXER_H

#include <exception>
#include <string>
#include <list>

class krpc_token_t;
class krpc_lexer_t;

/**
 * token����
 */
enum {
    krpc_token_i8 = 1,
    krpc_token_i16,
    krpc_token_i32,
    krpc_token_i64,
    krpc_token_ui8,
    krpc_token_ui16,
    krpc_token_ui32,
    krpc_token_ui64,
    krpc_token_f32,
    krpc_token_f64,
    krpc_token_string,
    krpc_token_array,
    krpc_token_object,
    krpc_token_rpc,
    krpc_token_import,
    krpc_token_text,
    krpc_token_left_brace,
    krpc_token_right_brace,
    krpc_token_left_round,
    krpc_token_right_round,
    krpc_token_right_square,
    krpc_token_comma,
    krpc_token_inline_comment,
};

/**
 * token
 */
class krpc_token_t {
public:
    /**
     * ���캯��
     * @param literal ������
     * @param row ��
     * @param col ��
     * @param type ����
     */
    krpc_token_t(const std::string& literal, int row, int col, int type);

    /**
     * ����
     */
    ~krpc_token_t();

    /**
     * ȡ��token������
     * @return token������
     */
    const std::string& get_literal() const;

    /**
     * ȡ����
     */
    int get_row() const;

    /**
     * ȡ����
     */
    int get_col() const;

    /**
     * ȡ������
     */
    int get_type() const;

private:
    std::string _literal; // ������
    int         _row;     // ��
    int         _col;     // ��
    int         _type;    // ����
};

/**
 * token������
 */
class krpc_lexer_t {
public:
    /**
     * ����
     * @param stream �ַ���
     */
    krpc_lexer_t(const char* stream);

    /**
     * ����
     */
    ~krpc_lexer_t();

    /**
     * ȡ����һ��token
     * @return krpc_token_tʵ��
     */
    krpc_token_t* next_token() throw(std::exception);

    /**
     * ȡ�õ�ǰ��
     */
    int get_col();

    /**
     * ȡ�õ�ǰ��
     */
    int get_row();

private:
    /**
     * ȡ����һ��token
     * @return krpc_token_tʵ��
     */
    krpc_token_t* get_token();

    /**
     * ��������ǰ�հ�
     */
    void eat_whites();

    /**
     * ��������ǰע��
     */
    void eat_comment();

    /**
     * ����Ƿ�Ϊ�հ�
     * @param c ��ǰ�ַ�
     * @retval true ��
     * @retval false ��
     */
    bool check_white(char c);

    /**
     * ����Ƿ�Ϊ�ս��
     * @param c ��ǰ�ַ�
     * @param icomment �Ƿ���Ƕ��ע������
     * @retval true ��
     * @retval false ��
     */
    bool check_terminator(char c, bool icomment);

    /**
     * ������
     * @param step ����
     * @return ��ǰ�ַ�
     */
    char forward(int step);

    /**
     * ������
     * @param cols ��
     */
    void add_col(int cols);

    /**
     * ������
     */
    void inc_row();

    /**
     * ������Ƿ���Ч
     */
    bool verify();

    /**
     * ȡ�õ�ǰ�ַ�
     */
    char current();

    /**
     * ���Ƿ����
     */
    bool has_next();

    /*
     * ȡ��һ���ַ����������ַ���
     */
    char try_next();

    /**
     * ���������Ƿ�Ϸ�
     * @param var_name ������
     * @retval true ��
     * @retval false ��
     */
    bool check_var_name(const char* var_name);

    //
    // �ؼ��ֱȽ�
    //

    bool check_keyword(const char* s, char c1, char c2);
    bool check_keyword(const char* s, char c1, char c2, char c3);
    bool check_keyword(const char* s, char c1, char c2, char c3, char c4);
    bool check_keyword(const char* s, char c1, char c2, char c3, char c4, char c5);
    bool check_keyword(const char* s, char c1, char c2, char c3, char c4, char c5, char c6);

private:
    typedef std::list<krpc_token_t*> token_list_t;
    token_list_t _tokens;   // token����
    int          _row;      // ��ǰ��
    int          _col;      // ��ǰ��
    char*        _stream;   // �ַ���
    bool         _icomment; // �Ƿ���Ƕ��ע������
};

#endif // KRPC_LEXER_H
