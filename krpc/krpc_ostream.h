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

#ifndef KRPC_OSTREAM_H
#define KRPC_OSTREAM_H

#include <iostream>
#include <fstream>
#include <sstream>

/*
 * ��׼�ļ�������װ��
 */
class krpc_ostream_t {
public:
    /*
     * ���캯��
     * @param file_name ��Ҫд����ļ�·��
     */
    krpc_ostream_t(const std::string& file_name);

    /*
     * ����
     */
    ~krpc_ostream_t();

    /*
     * std::string
     */
    krpc_ostream_t& operator<<(const std::string& s) {
        _ofs << s;
        return *this;
    }

    /*
     * int
     */
    krpc_ostream_t& operator<<(int i) {
        std::stringstream ss;
        ss << i;
        _ofs << ss.str();
        return *this;
    }

    /*
     * const char*
     */
    krpc_ostream_t& operator<<(const char* s) {
        _ofs << s;
        return *this;
    }
    
    /*
     * �ɱ����ģ���滻��ֻ֧���ַ�������
     */
    const krpc_ostream_t& write(const char* fmt, ...);

    /*
     * �滻����ģ��
     */
    const krpc_ostream_t& replace(const char* fmt, const std::string& source);

private:
    std::ofstream _ofs; // �ļ������
};

#endif // KRPC_OSTREAM_H
