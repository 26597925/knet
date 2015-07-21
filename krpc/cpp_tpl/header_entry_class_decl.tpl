/**
 * RPC������
 */
class {{@name}}_t {
public:
    /**
     * ����
     */
    ~{{@name}}_t();

    /**
     * ȡ�õ���ָ��
     * \return {{@name}}_tָ��
     */
    static {{@name}}_t* instance();

    /**
     * ���ٵ���
     */
    static void finalize();

    /**
     * ��stream_t��ȡRPC��������
     * \param stream kstream_tʵ��
     * \retval error_ok �ɹ�����һ��RPC����
     * \retval error_rpc_not_enough_bytes û��������RPC���Դ���
     * \retval error_rpc_unmarshal_fail ����RPC���ֽ���ʱ��ȡʧ��
     * \retval error_rpc_unknown_id ��ȡ��RPC���ã���RPC IDδע��
     * \retval error_rpc_cb_fail ����RPC������ʱ���������ڲ���������
     * \retval error_rpc_cb_fail_close ����RPC������ʱ���������ڲ��������󣬴�����Ҫ��ر�kstream_t������Ĺܵ�
     * \retval error_rpc_cb_close ����RPC�������󣬴�����Ҫ��ر�kstream_t������Ĺܵ�
     * \retval error_rpc_unknown_type RPC���ʹ���
     */
    int rpc_proc(kstream_t* stream);
	
	/**
	 * ��ȡkrpc_tʵ��
	 * @return krpc_tʵ��
	 */
	 krpc_t* get_rpc();

