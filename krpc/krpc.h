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
    bool krpc_gen_t::get_option(int pos, int argc, char** argv, const char* detail, const char* brief);

private:
    option_map_t   _options; // ������
    int            _argc;    // �����и���
    char**         _argv;    // ������
    krpc_parser_t* _parser;  // �﷨������
};

#endif // KRPC_H
