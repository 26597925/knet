#ifndef KRPC_CPP_H
#define KRPC_CPP_H

#include <sstream>
#include <cstdint>

class krpc_gen_t;
class krpc_field_t;
class krpc_attribute_t;

/*
 * C++����������
 */
class krpc_gen_cpp_t {
public:
    /*
     * ����
     * @param rpc_gen krpc_gen_tʵ��
     */
    krpc_gen_cpp_t(krpc_gen_t* rpc_gen);

    /*
     * ����
     */
    ~krpc_gen_cpp_t();

    /*
     * ���ɴ���
     */
    void lang_gen_code();

private:
    /*
     * ����RPC���ÿ����
     */
    void lang_gen_framework(std::stringstream& header, std::stringstream& source);

    /*
     * ����RPC���ÿ���� - ����
     */
    void lang_gen_framework_decls(std::stringstream& header);

    /*
     * ����RPC���ÿ���� - ����
     */
    void lang_gen_framework_impls(std::stringstream& source);

    /*
     * ����ͷ�ļ�
     */
    void lang_gen_includes(std::stringstream& header);

    /*
     * ���Զ���Ԥ������
     */
    void lang_gen_attributes_pre_decls(std::stringstream& header);

    /*
     * ���Զ�����ش�������
     */
    void lang_gen_attributes(std::stringstream& header, std::stringstream& source);

    /*
     * ���Զ�����ش������� - ����
     */
    void lang_gen_attribute_method_decl(krpc_attribute_t* attribute, std::stringstream& header);

    /*
     * ���Զ�����ش������� - ����
     */
    void lang_gen_attribute_method_impl(krpc_attribute_t* attribute, std::stringstream& source);

    /*
     * �����ֶ� - ����
     */
    void lang_gen_attribute_field_decl(std::stringstream& header, krpc_field_t* field);

    /*
     * RPC���� - ����
     */
    void lang_gen_rpc_call_decls(std::stringstream& header);

    /*
     * RPC���� - ����
     */
    void lang_gen_rpc_call_impls(std::stringstream& source);

    /*
     * RPC���� - ����
     */
    void lang_gen_rpc_call_param_decl(std::stringstream& header, krpc_field_t* field);

    /*
     * RPC���� - proxy����
     */
    void lang_gen_rpc_call_impl_proxy(krpc_attribute_t* attribute, std::stringstream& source);

    /*
     * RPC���� - stub����
     */
    void lang_gen_rpc_call_impl_stub(krpc_attribute_t* attribute, std::stringstream& source, const std::string& rpc_name);

    /*
     * �������Զ��� - marshal/unmarshal����
     */
    void lang_gen_attribute_marshal_method_decls(std::stringstream& header);

    /*
     * ���Զ��� - marshal����
     */
    void lang_gen_attribute_marshal_method_decl(krpc_attribute_t* attribute, std::stringstream& header);

    /*
     * �������Զ��� - marshal����
     */
    void lang_gen_attribute_marshal_method_impls(std::stringstream& source);

    /*
     * ���Զ��� - marshal����
     */
    void lang_gen_attribute_marshal_method_impl(krpc_attribute_t* attribute, std::stringstream& source);

    /*
     * �������Զ��� - unmarshal����
     */
    void lang_gen_attribute_unmarshal_method_impls(std::stringstream& source);

    /*
     * ���Զ��� - unmarshal����
     */
    void lang_gen_attribute_unmarshal_method_impl(krpc_attribute_t* attribute, std::stringstream& source);

    /*
     * ���Զ��� - ������ - unmarshal����
     */
    void lang_gen_attribute_unmarshal_field_not_array(krpc_field_t* field, std::stringstream& source, const std::string& name, int index);

    /*
     * ���Զ��� - ���� - unmarshal����
     */
    void lang_gen_attribute_unmarshal_field_array(krpc_field_t* field, std::stringstream& source, const std::string& name, int index);

    /*
     * �ֶ� - marshal����
     */
    void lang_gen_field_marshal_impl(krpc_field_t* field, std::stringstream& source);

    /*
     * �ֶ� - ������ - marshal����
     */
    void lang_gen_field_marshal_impl_not_array(krpc_field_t* field, std::stringstream& source, const std::string& holder_name = "",
        const std::string& vector_name = "", const std::string& whites = "");

    /*
     * �ֶ� - ���� - marshal����
     */
    void lang_gen_field_marshal_impl_array(krpc_field_t* field, std::stringstream& source, const std::string& whites = "");

    /*
     * �ֶ� - unmarshal����
     */
    void lang_gen_field_unmarshal_impl(krpc_field_t* field, std::stringstream& source, int index);

    /*
     * �ֶ� - ������ - marshal����
     */
    void lang_gen_field_unmarshal_impl_not_array(krpc_field_t* field, std::stringstream& source, int index);

    /*
     * �ֶ� - ������, ��Ϊ���������ڵ��� - unmarshal����
     */
    void lang_gen_field_unmarshal_impl_not_array_inline(krpc_field_t* field, std::stringstream& source, int index);

    /*
     * �ֶ� - ���� - unmarshal����
     */
    void lang_gen_field_unmarshal_impl_array(krpc_field_t* field, std::stringstream& source, int index);

    /*
     * ȡ�������ֶ�������
     */
    std::string lang_field_find_type_name(krpc_field_t* field);

    /*
     * ȡ�ò����ֶ�������
     */
    std::string lang_param_find_type_name(krpc_field_t* field);

private:
    krpc_gen_t* _rpc_gen; // �������������
    uint16_t    _rpc_id;  // RPC����ID
};

#endif // KRPC_CPP_H
