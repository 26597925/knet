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
     * �ɱ����ģ���滻
     */
    const krpc_ostream_t& write(const char* fmt, ...);
    const krpc_ostream_t& replace(const char* fmt, const std::string& source);

private:
    std::ofstream _ofs; // �ļ������
};

#endif // KRPC_OSTREAM_H
