private:
    /**
     * ���캯��
     */
    {{@name}}_t();

    /**
     * ��������
     */
    {{@name}}_t(const {{@name}}_t&);

private:
    static {{@name}}_t* _instance; // ����ָ��
    krpc_t* _rpc; // RPCʵ����"
