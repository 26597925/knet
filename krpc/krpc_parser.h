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
    krpc_parser_t(krpc_parser_t* parent, const char* dir, const char* file_name);\

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

    /*
     * ��Ļ����ļ��ṹ
     */
    void print();

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
