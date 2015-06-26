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

#ifndef KRPC_H
#define KRPC_H

#include <map>
#include <list>

class krpc_parser_t;

/*
 * rpc��ܴ���������
 */
class krpc_gen_t {
public:
    typedef std::map<std::string, std::string> option_map_t;

public:
    /*
     * ���캯��
     * @param argc �����и���
     * @param argv ������
     */
    krpc_gen_t(int argc, char** argv);

    /*
     * ��������
     */
    ~krpc_gen_t();

    /*
     * ���ɴ���
     */
    void lang_gen_code();

    /*
     * ��ȡ������
     * @return ��ȡ������
     */
    option_map_t& get_options();

    /*
     * ��ȡ�﷨������
     * @return krpc_parser_tʵ��
     */
    krpc_parser_t* get_parser() const;

private:
    /*
     * ��ȡ�����в���
     * @param pos ����������λ��
     * @param argc �����и���
     * @param argv ������
     * @param detail ��������
     * @param brief ��д
     * @retval true �ҵ�����
     * @retval false δ�ҵ�����
     */
    bool get_option(int pos, int argc, char** argv, const char* detail, const char* brief);

private:
    option_map_t   _options; // ������
    int            _argc;    // �����и���
    char**         _argv;    // ������
    krpc_parser_t* _parser;  // �﷨������
};

#endif // KRPC_H
