#pragma once
#include "hash_util.h"



// 创建哈希表
hash_map *create_hash_map() {
    hash_map *map = (hash_map *)malloc(sizeof(hash_map));
    map->table = (hash_entry **)malloc(sizeof(hash_entry *) * TABLE_SIZE);
    for (int i = 0; i < TABLE_SIZE; i++) {
        map->table[i] = NULL;
    }
    return map;
}

// 哈希函数 DJB2 哈希算法
unsigned int hash(char *key,int size) {
    unsigned long int hashval = 0;
    while (*key) {
        hashval = (hashval << 5) + *key++; // 左移并加上字符
    }
    return hashval % size;
}

// 哈希函数 DJB2 哈希算法
unsigned int hash(wchar_t *key,int size ) {
    unsigned long int hashval = 0;
    while (*key) {
        hashval = (hashval << 5) + *key++; // 左移并加上字符
    }
    return hashval % size;
}

// 哈希函数 DJB2 哈希算法，处理单个 WCHAR
unsigned int hash(wchar_t key,int size ) {
    // 将单个字符转换为哈希值
    unsigned long int hashval = key; // 直接使用字符的值
    return hashval % size; // 返回哈希值
}

// 插入键值对
void put_hash_map(hash_map *map, char *key, void *value) {
    unsigned int index = hash(key);
    hash_entry *newEntry = (hash_entry *)malloc(sizeof(hash_entry));
    newEntry->key = strdup(key);
    newEntry->value = value; // 存储任意类型的值
    newEntry->next = map->table[index];
    map->table[index] = newEntry;
}

// 查找值
void *get_hash_map(hash_map *map, char *key) {
    if (map == NULL) {
        return NULL;
    }
    unsigned int index = hash(key);
    hash_entry *entry = map->table[index];
    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value; // 返回 void*
        }
        entry = entry->next;
    }
    return NULL; // 未找到
}

// 删除键值对
void remove_hash_map(hash_map *map, char *key) {
    unsigned int index = hash(key);
    hash_entry *entry = map->table[index];
    hash_entry *prev = NULL;

    while (entry) {
        if (strcmp(entry->key, key) == 0) {
            if (prev) {
                prev->next = entry->next;
            } else {
                map->table[index] = entry->next;
            }
            free(entry->key);
            free(entry);
            return;
        }
        prev = entry;
        entry = entry->next;
    }
}

// 释放哈希表
void free_hash_map(hash_map *map) {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hash_entry *entry = map->table[i];
        while (entry) {
            hash_entry *temp = entry;
            entry = entry->next;
            free(temp->key);
            free(temp);
        }
    }
    free(map->table);
    free(map);
}

// 测试代码
int main1() {
    hash_map *map = create_hash_map();

    int value1 = 42;
    double value2 = 3.14;

    put_hash_map(map, "key1", &value1); // 存储整型
    put_hash_map(map, "key2", &value2); // 存储浮点型

    printf("key1: %d\n", *(int *) get_hash_map(map, "key1")); // 输出: key1: 42
    printf("key2: %.2f\n", *(double *) get_hash_map(map, "key2")); // 输出: key2: 3.14

    remove_hash_map(map, "key1");
    printf("key1: %p\n", get_hash_map(map, "key1")); // 输出: key1: (null)

    free_hash_map(map);
    return 0;
}
