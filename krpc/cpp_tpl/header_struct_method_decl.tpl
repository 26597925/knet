    
	/**
     * ���캯��
     */
    {{@name}}();

    /**
     * ��������
     * \param rht {{@name}}����
     */
    {{@name}}(const {{@name}}& rht);

    /**
     * ��ֵ
     * \param rht {{@name}}����
     */
    const {{@name}}& operator=(const {{@name}}& rht);

    /**
     * ��ӡ����
     * \param ss std::stringstream���ã� ������Ϣ�������
     * \param white �����ո�
     */
    void print(std::stringstream& ss, std::string white = "");
