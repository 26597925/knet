#ifndef VERSION_H
#define VERSION_H

/*
 * ȡ�õ�ǰ�汾���ַ���
 * @return ��ǰ�汾���ַ���
 */
extern const char* knet_get_version_string();

/*
 * ȡ�����汾��
 * @return ���汾��
 */
extern int knet_get_version_major();

/*
 * ȡ�ôΰ汾��
 * @return �ΰ汾��
 */
extern int knet_get_version_minor();

/*
 * ȡ�ò����汾��
 * @return �����汾��
 */
extern int knet_get_version_path();

#endif /* VERSION_H */
