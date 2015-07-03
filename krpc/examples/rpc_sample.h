//
// KRPC - Generated code, *DO NOT CHANGE*
//

#ifndef _krpc_rpc_sample_h_
#define _krpc_rpc_sample_h_

#include <cstdint>
#include <string>
#include <vector>
#include <map>
#include "knet.h"

namespace rpc_sample {

struct my_object_other_t;
struct my_object_t;

/**
 * �Զ������
 */
struct my_object_other_t {
	std::map<std::string,std::string> string_string_table; ///< ��
    
	/**
     * ���캯��
     */
    my_object_other_t();

    /**
     * ��������
     * \param rht my_object_other_t����
     */
    my_object_other_t(const my_object_other_t& rht);

    /**
     * ��ֵ
     * \param rht my_object_other_t����
     */
    const my_object_other_t& operator=(const my_object_other_t& rht);

    /**
     * ��ӡ����
     * \param ss std::stringstream���ã� ������Ϣ�������
     * \param white �����ո�
     */
    void print(std::stringstream& ss, std::string white = "");
};

/**
 * ��������
 */
struct my_object_t {
	int8_t ni8; ///< �з���8λ����
	int16_t ni16; ///< �з���16λ����
	int32_t ni32; ///< �з���32λ����
	int64_t ni64; ///< �з���64λ����
	uint8_t nui8; ///< �޷���8λ����
	uint16_t nui16; ///< �޷���16λ����
	uint32_t nui32; ///< �޷���32λ����
	uint64_t nui64; ///< �޷���64λ����
	float nf32; ///< 32λ������
	double nf64; ///< 64λ������
	std::string str; ///< �ַ���
	std::map<int8_t,std::string> int_string_table; ///< ��
	std::map<int8_t,my_object_other_t> int_object_table; ///< ��
    
	/**
     * ���캯��
     */
    my_object_t();

    /**
     * ��������
     * \param rht my_object_t����
     */
    my_object_t(const my_object_t& rht);

    /**
     * ��ֵ
     * \param rht my_object_t����
     */
    const my_object_t& operator=(const my_object_t& rht);

    /**
     * ��ӡ����
     * \param ss std::stringstream���ã� ������Ϣ�������
     * \param white �����ո�
     */
    void print(std::stringstream& ss, std::string white = "");
};

/**
 * my_object_other_t���л�
 */
krpc_object_t* marshal(my_object_other_t& o);

/**
 * my_object_other_t�����л�
 */
bool unmarshal(krpc_object_t* v, my_object_other_t& o);

/**
 * my_object_t���л�
 */
krpc_object_t* marshal(my_object_t& o);

/**
 * my_object_t�����л�
 */
bool unmarshal(krpc_object_t* v, my_object_t& o);

/**
 * my_rpc_func1����
 */
krpc_object_t* my_rpc_func1_proxy(my_object_t& my_obj);

/**
 * my_rpc_func2����
 */
krpc_object_t* my_rpc_func2_proxy(std::vector<my_object_t>& my_objs, int8_t my_i8);

/**
 * my_rpc_func3����
 */
krpc_object_t* my_rpc_func3_proxy(const std::string& my_str, int8_t my_i8);

/**
 * my_rpc_func1׮
 */
int my_rpc_func1_stub(krpc_object_t* o);

/**
 * my_rpc_func2׮
 */
int my_rpc_func2_stub(krpc_object_t* o);

/**
 * my_rpc_func3׮
 */
int my_rpc_func3_stub(krpc_object_t* o);

/**
 * RPC����ʾ��, my_rpc_func1��������ʵ�ִ˷���
 * \param my_obj ����1
 * \retval rpc_ok          �ɹ�
 * \retval rpc_close       ���Դ��󣬹ر�
 * \retval rpc_error       ���󣬵����ر�
 * \retval rpc_error_close �����ҹر�
 */
int my_rpc_func1(my_object_t& my_obj);

/**
 * RPC����ʾ��, my_rpc_func2��������ʵ�ִ˷���
 * \param my_objs ����1
 * \param my_i8 ����2
 * \retval rpc_ok          �ɹ�
 * \retval rpc_close       ���Դ��󣬹ر�
 * \retval rpc_error       ���󣬵����ر�
 * \retval rpc_error_close �����ҹر�
 */
int my_rpc_func2(std::vector<my_object_t>& my_objs, int8_t my_i8);

/**
 * RPC����ʾ��, my_rpc_func3��������ʵ�ִ˷���
 * \param my_str ����1
 * \param my_i8 ����2
 * \retval rpc_ok          �ɹ�
 * \retval rpc_close       ���Դ��󣬹ر�
 * \retval rpc_error       ���󣬵����ر�
 * \retval rpc_error_close �����ҹر�
 */
int my_rpc_func3(const std::string& my_str, int8_t my_i8);

/**
 * RPC������
 */
class rpc_sample_t {
public:
    /**
     * ����
     */
    ~rpc_sample_t();

    /**
     * ȡ�õ���ָ��
     * \return rpc_sample_tָ��
     */
    static rpc_sample_t* instance();

    /**
     * ���ٵ���
     */
    static void finalize();

    /**
     * ��stream_t��ȡRPC��������
     * \param stream stream_tʵ��
     * \retval error_ok �ɹ�����һ��RPC����
     * \retval error_rpc_not_enough_bytes û��������RPC���Դ���
     * \retval error_rpc_unmarshal_fail ����RPC���ֽ���ʱ��ȡʧ��
     * \retval error_rpc_unknown_id ��ȡ��RPC���ã���RPC IDδע��
     * \retval error_rpc_cb_fail ����RPC������ʱ���������ڲ���������
     * \retval error_rpc_cb_fail_close ����RPC������ʱ���������ڲ��������󣬴�����Ҫ��ر�stream_t������Ĺܵ�
     * \retval error_rpc_cb_close ����RPC�������󣬴�����Ҫ��ر�stream_t������Ĺܵ�
     * \retval error_rpc_unknown_type RPC���ʹ���
     */
    int rpc_proc(stream_t* stream);

    /**
     * my_rpc_func1 RPC����ʾ��
	 * \param stream stream_tʵ��
    * \param my_obj ����1
    * \retval error_ok �ɹ�
    * \retval error_rpc_marshal_fail ���л�RPC����ʱʧ��
    */
	int my_rpc_func1(stream_t* stream, my_object_t& my_obj);

    /**
     * my_rpc_func2 RPC����ʾ��
	 * \param stream stream_tʵ��
    * \param my_objs ����1
    * \param my_i8 ����2
    * \retval error_ok �ɹ�
    * \retval error_rpc_marshal_fail ���л�RPC����ʱʧ��
    */
	int my_rpc_func2(stream_t* stream, std::vector<my_object_t>& my_objs, int8_t my_i8);

    /**
     * my_rpc_func3 RPC����ʾ��
	 * \param stream stream_tʵ��
    * \param my_str ����1
    * \param my_i8 ����2
    * \retval error_ok �ɹ�
    * \retval error_rpc_marshal_fail ���л�RPC����ʱʧ��
    */
	int my_rpc_func3(stream_t* stream, const std::string& my_str, int8_t my_i8);

private:
    /**
     * ���캯��
     */
    rpc_sample_t();

    /**
     * ��������
     */
    rpc_sample_t(const rpc_sample_t&);

private:
    static rpc_sample_t* _instance; // ����ָ��
    krpc_t* _rpc; // RPCʵ����"
};

/**
 * rpc_sample单件访问帮助函数
 */
inline static rpc_sample_t* rpc_sample_ptr() {
	return rpc_sample_t::instance();
}

} // namespace rpc_sample

#endif // _krpc_rpc_sample_h_

