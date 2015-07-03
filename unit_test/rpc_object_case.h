#include "helper.h"
#include "knet.h"

CASE(Test_Rpc_Number) {
    krpc_object_t* number = krpc_object_create();

    krpc_number_set_i8(number, 16);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_i8));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16 == krpc_number_get_i8(number));

    krpc_number_set_i16(number, 16);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_i16));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16 == krpc_number_get_i16(number));

    krpc_number_set_i32(number, 16);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_i32));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16 == krpc_number_get_i32(number));

    krpc_number_set_i64(number, 16);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_i64));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16 == krpc_number_get_i64(number));

    krpc_number_set_ui8(number, 16);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_ui8));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16 == krpc_number_get_ui8(number));

    krpc_number_set_ui16(number, 16);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_ui16));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16 == krpc_number_get_ui16(number));

    krpc_number_set_ui32(number, 16);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_ui32));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16 == krpc_number_get_ui32(number));

    krpc_number_set_ui64(number, 16);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_ui64));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16 == krpc_number_get_ui64(number));

    krpc_number_set_f32(number, 16.0f);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_f32));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16.0f == krpc_number_get_f32(number));

    krpc_number_set_f64(number, 16.0f);
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_f64));
    EXPECT_TRUE(krpc_object_check_type(number, krpc_type_number));
    EXPECT_TRUE(16.0f == krpc_number_get_f64(number));

    krpc_object_destroy(number);
}

CASE(Test_Rpc_String) {
    krpc_object_t* string = krpc_object_create();

    // ��һ�����þ������ȼ����ͣ��������ò��ܸı䳤��
    krpc_string_set(string, "12345");
    EXPECT_TRUE(krpc_object_check_type(string, krpc_type_string));
    EXPECT_TRUE(std::string("12345") == krpc_string_get(string));
    EXPECT_TRUE(krpc_string_get_size(string) == 6);

    krpc_string_set(string, "123456");
    EXPECT_TRUE(krpc_object_check_type(string, krpc_type_string));
    // ���Ȳ��ɸı�
    EXPECT_TRUE(std::string("12345") == krpc_string_get(string));
    EXPECT_TRUE(krpc_string_get_size(string) == 6);

    krpc_string_set_s(string, "12345", 6);
    EXPECT_TRUE(krpc_object_check_type(string, krpc_type_string));
    EXPECT_TRUE(std::string("12345") == krpc_string_get(string));
    EXPECT_TRUE(krpc_string_get_size(string) == 6);

    krpc_string_set_s(string, "123456", 7);
    EXPECT_TRUE(krpc_object_check_type(string, krpc_type_string));
    // ���Ȳ��ɸı�
    EXPECT_TRUE(std::string("12345") == krpc_string_get(string));
    EXPECT_TRUE(krpc_string_get_size(string) == 6);

    krpc_object_destroy(string);
}

CASE(Test_Rpc_Vector) {
    // TODO δ�����Ե����
    // 1.ͬһkrpc_object_t��vectorֻ�ܴ���һ���������ظ�����
    //   ����ͬһkrpc_object_t�ᱻ��������, ��ΪRPC������ɵ�
    //   ���벻��������������⣬Ϊ��Ч�ʿ���û���������⣬��������.
    // 2.vector�ڲ�Ԫ�ش�������ǿ����ǲ�ͬ���͵ģ����Ƕ���c++
    //   std::vector���ǲ����ܵģ���������.

    krpc_object_t* v = krpc_object_create();

    for (int i = 0; i < 10; i++) {
        krpc_object_t* e = krpc_object_create();
        krpc_number_set_i32(e, 128);
        EXPECT_TRUE(error_ok == krpc_vector_push_back(v, e));
    }
    EXPECT_TRUE(10 == krpc_vector_get_size(v));

    for (int i = 0; i < 10; i++) {
        krpc_object_t* e = krpc_vector_get(v, i);
        EXPECT_TRUE(128 == krpc_number_get_i32(e));
    }

    // Խ��
    EXPECT_FALSE(krpc_vector_get(v, 10));
    EXPECT_FALSE(krpc_vector_get(v, 100));

    // ��Ԫ�ر�ɾ��
    krpc_object_t* insertee1 = krpc_object_create();
    krpc_number_set_i32(insertee1, 256);
    EXPECT_TRUE(error_ok == krpc_vector_set(v, insertee1, 1));
    EXPECT_TRUE(insertee1 == krpc_vector_get(v, 1));

    // Խ��
    krpc_object_t* insertee2 = krpc_object_create();
    krpc_number_set_i32(insertee2, 256);
    EXPECT_FALSE(error_ok == krpc_vector_set(v, insertee2, 10));
    krpc_object_destroy(insertee2);

    // ��գ�ɾ������Ԫ��
    krpc_vector_clear(v);
    EXPECT_TRUE(0 == krpc_vector_get_size(v));

    krpc_object_destroy(v);
}

CASE(Test_Rpc_Map) {
    // TODO δ�����Ե����
    // 1.ͬһkey��value��rpc_object_t������mapֻ�ܴ���һ���������ظ�����
    //   ����ͬһkrpc_object_t�ᱻ��������, ��ΪRPC������ɵ�
    //   ���벻��������������⣬Ϊ��Ч�ʿ���û���������⣬��������.
    // 2.map�ڲ�Ԫ�ش������value�ǿ����ǲ�ͬ���͵ģ����Ƕ���c++
    //   std::map���ǲ����ܵģ���������.

    krpc_object_t* m = krpc_object_create();
    int key = 0, value = 0;
    for (; key < 10; key++, value++) {
        krpc_object_t* k = krpc_object_create();
        krpc_object_t* v = krpc_object_create();
        krpc_number_set_i32(k, key);
        krpc_number_set_i32(v, value);
        EXPECT_TRUE(error_ok == krpc_map_insert(m, k, v));
    }
    EXPECT_TRUE(10 == krpc_map_get_size(m));

    for (key = 0, value = 0; key < 10; key++, value++) {
        krpc_object_t* k = krpc_object_create();
        krpc_number_set_i32(k, key);
        krpc_object_t* v = krpc_map_get(m, k);
        EXPECT_TRUE(v);
        EXPECT_TRUE(value == krpc_number_get_i32(v));
        krpc_object_destroy(k);
    }

    do {
        krpc_object_t* k = krpc_object_create();
        krpc_object_t* v = krpc_object_create();
        krpc_string_set(k, "key");
        krpc_number_set_i32(v, 128);

        // key���Ͳ��ܱ��ı�
        EXPECT_FALSE(error_ok == krpc_map_insert(m, k, v));

        krpc_object_destroy(k);
        krpc_object_destroy(v);
    } while(0);

    do {
        krpc_object_t* k = 0;
        krpc_object_t* v = 0;
        int value = 0;
        for (krpc_map_get_first(m, &k, &v); (error_ok == krpc_map_next(m, &k, &v)); value++) {
            EXPECT_TRUE(value == krpc_number_get_i32(k));
            EXPECT_TRUE(value == krpc_number_get_i32(v));
        }
    } while(0);

    krpc_map_clear(m);
    EXPECT_TRUE(0 == krpc_map_get_size(m));

    krpc_object_destroy(m);
}
