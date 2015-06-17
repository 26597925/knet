#include "hash.h"
#include "list.h"

struct _hash_t {
    uint32_t    size;    /* Ͱ���� */
    uint32_t    count;   /* ��ǰ����Ԫ�ظ��� */
    dlist_t**   buckets; /* Ͱ���� */
    hash_dtor_t dtor;    /* �Զ���ֵ���ٺ��� */
};

typedef struct _hash_value_t {
    uint32_t key;        /* ���ּ� */
    char*    string_key; /* �ַ����� */
    void*    value;      /* ֵ */
} hash_value_t;

/*
 * ����ֵ
 * @param key ���ּ�
 * @param string_key �ַ�����
 * @param value ֵ
 * @return hash_value_tʵ��
 */
hash_value_t* hash_value_create(uint32_t key, const char* string_key, void* value);

/*
 * ����ֵ
 * @param hash_value hash_value_tʵ��
 */
void hash_value_destroy(hash_value_t* hash_value);

/*
 * �������ּ��Ƿ����
 * @param hash_value hash_value_tʵ��
 * @param key ������
 * @retval 0 �����
 * @retval ���� ���
 */
int hash_value_equal(hash_value_t* hash_value, uint32_t key);

/*
 * �����ַ������Ƿ����
 * @param hash_value hash_value_tʵ��
 * @param key �ַ�����
 * @retval 0 �����
 * @retval ���� ���
 */
int hash_value_equal_string_key(hash_value_t* hash_value, const char* key);

/*
 * ����ַ���������ֵ
 * @param key �ַ���
 * @return ������ֵ
 */
uint32_t _hash_string(const char* key);

hash_value_t* hash_value_create(uint32_t key, const char* string_key, void* value) {
    hash_value_t* hash_value = create(hash_value_t);
    assert(hash_value);
    memset(hash_value, 0, sizeof(hash_value_t));    
    if (string_key) { /* �ַ����� */
        hash_value->string_key = create_type(char, strlen(string_key) + 1);
        strcpy(hash_value->string_key, string_key);
    } else { /* ���ּ� */
        hash_value->key = key;
    }
    hash_value->value = value;
    return hash_value;
}

void hash_value_destroy(hash_value_t* hash_value) {
    assert(hash_value);
    if (hash_value->string_key) {
        destroy(hash_value->string_key);
    }
    destroy(hash_value);
}

int hash_value_equal(hash_value_t* hash_value, uint32_t key) {
    assert(hash_value);
    return (key == hash_value->key);
}

int hash_value_equal_string_key(hash_value_t* hash_value, const char* key) {
    assert(hash_value);
    assert(key);
    if (!hash_value->string_key) {
        /* �ⲿ����ĵ��� */
        assert(0);
        return 0;
    }
    return (0 == strcmp(key, hash_value->string_key));
}

hash_t* hash_create(uint32_t size, hash_dtor_t dtor) {
    uint32_t i = 0;
    hash_t* hash = create(hash_t);
    assert(hash);
    memset(hash, 0, sizeof(hash_t));
    if (!size) {
        size = 128; /* Ĭ��bucket���� */
    }
    hash->dtor = dtor;
    hash->size = size;
    hash->buckets = (dlist_t**)create_type(dlist_t*, sizeof(dlist_t*) * size);
    assert(hash->buckets);
    memset(hash->buckets, 0, size * sizeof(dlist_t*));
    /* ����bucket���� */
    for (; i < size; i++) {
        hash->buckets[i] = dlist_create();
    }
    return hash;
}

void hash_destroy(hash_t* hash) {
    uint32_t      i     = 0;
    dlist_node_t* node  = 0;
    dlist_node_t* temp  = 0;
    hash_value_t* value = 0;
    assert(hash);
    /* ��������bucket������ */
    for (; i < hash->size; i++) {
        if (hash->buckets[i]) {
            dlist_for_each_safe(hash->buckets[i], node, temp) {
                value = (hash_value_t*)dlist_node_get_data(node);
                if (hash->dtor) {
                    /* �Զ������� */
                    hash->dtor(value->value);
                }
                /* ����ֵ */
                hash_value_destroy(value);
            }
            /* �������� */
            dlist_destroy(hash->buckets[i]);
            hash->buckets[i] = 0;
        }
    }
    /* ����bucket */
    destroy(hash->buckets);
    destroy(hash);
}

int hash_add(hash_t* hash, uint32_t key, void* value) {
    uint32_t      hash_key   = 0;
    hash_value_t* hash_value = 0;
    assert(hash);
    assert(value);
    hash_key = key % hash->size;
    /* ����ֵ */
    hash_value = hash_value_create(key, 0, value);
    /* ��ӵ�����β */
    dlist_add_tail_node(hash->buckets[hash_key], hash_value);
    hash->count++;
    return error_ok;
}

int hash_add_string_key(hash_t* hash, const char* key, void* value) {
    uint32_t      hash_key   = 0;
    hash_value_t* hash_value = 0;
    assert(hash);
    assert(value);
    hash_key = _hash_string(key);
    /* ����ֵ */
    hash_value = hash_value_create(0, key, value);
    /* ��ӵ�����β */
    dlist_add_tail_node(hash->buckets[hash_key], hash_value);
    hash->count++;
    return error_ok;
}

void* hash_remove(hash_t* hash, uint32_t key) {
    uint32_t      hash_key   = 0;
    dlist_node_t* node       = 0;
    dlist_node_t* temp       = 0;
    hash_value_t* hash_value = 0;
    void*         value      = 0;
    assert(hash);
    hash_key = key % hash->size;
    /* ����������� */
    dlist_for_each_safe(hash->buckets[hash_key], node, temp) {
        hash_value = (hash_value_t*)dlist_node_get_data(node);
        if (hash_value_equal(hash_value, key)) {
            hash->count--;
            value = hash_value->value;
            /* ���ٽڵ� */
            dlist_delete(hash->buckets[hash_key], node);
            /* ����ֵ */
            hash_value_destroy(hash_value);
            return value; /* ���ظ������� */
        }
    }
    return 0; /* û�ҵ� */
}

void* hash_remove_string_key(hash_t* hash, const char* key) {
    uint32_t      hash_key   = 0;
    dlist_node_t* node       = 0;
    dlist_node_t* temp       = 0;
    hash_value_t* hash_value = 0;
    void*         value      = 0;
    assert(hash);
    hash_key = _hash_string(key);
    /* ����������� */
    dlist_for_each_safe(hash->buckets[hash_key], node, temp) {
        hash_value = (hash_value_t*)dlist_node_get_data(node);
        if (hash_value_equal_string_key(hash_value, key)) {
            hash->count--;
            value = hash_value->value;
            /* ���ٽڵ� */
            dlist_delete(hash->buckets[hash_key], node);
            /* ����ֵ */
            hash_value_destroy(hash_value);
            return value; /* ���ظ������� */
        }
    }
    return 0; /* û�ҵ� */
}

int hash_delete(hash_t* hash, uint32_t key) {
    void* value = 0;
    assert(hash);
    value = hash_remove(hash, key);
    if (hash->dtor) {
        hash->dtor(value);
    } else {
        /* ����ⲿ������ڴ棬�������ֲ��ṩ���ٺ������ڴ�й¶ */
    }
    return error_ok;
}

int hash_delete_string_key(hash_t* hash, const char* key) {
    void* value = 0;
    assert(hash);
    value = hash_remove_string_key(hash, key);
    if (hash->dtor) {
        hash->dtor(value);
    } else {
        /* ����ⲿ������ڴ棬�������ֲ��ṩ���ٺ�����������ڴ�й¶ */
    }
    return error_ok;
}

void* hash_get(hash_t* hash, uint32_t key) {
    uint32_t      hash_key   = 0;
    dlist_node_t* node       = 0;
    hash_value_t* hash_value = 0;
    assert(hash);
    hash_key = key % hash->size;
    /* ����������� */
    dlist_for_each(hash->buckets[hash_key], node) {
        hash_value = (hash_value_t*)dlist_node_get_data(node);
        if (hash_value_equal(hash_value, key)) {
            return hash_value->value;
        }
    }
    return 0; /* û�ҵ� */
}

void* hash_get_string_key(hash_t* hash, const char* key) {
    uint32_t      hash_key   = 0;
    dlist_node_t* node       = 0;
    hash_value_t* hash_value = 0;
    assert(hash);
    hash_key = _hash_string(key);
    /* ����������� */
    dlist_for_each(hash->buckets[hash_key], node) {
        hash_value = (hash_value_t*)dlist_node_get_data(node);
        if (hash_value_equal_string_key(hash_value, key)) {
            return hash_value->value;
        }
    }
    return 0; /* û�ҵ� */
}

uint32_t hash_get_size(hash_t* hash) {
    assert(hash);
    return hash->count;
}

uint32_t _hash_string(const char* key) {
    uint32_t hash_key = 0;
    /* �򵥵ļ��������key */
    for(; *key; key++) {
        hash_key = *key + hash_key * 31;
    }
    return hash_key;
}
