#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 4 // 初始哈希表大小

/**
 * 目前先采用链地址法，不采用红黑树
 */

typedef struct hash_entry {
    char *key;
    void *value; // 使用 void* 来存储任意类型的值  移除的时候要注意释放内存，或者变量是值类型
    struct hash_entry *next; // 处理哈希冲突
} hash_entry;

typedef struct hash_map {
    hash_entry **table; // 哈希表
} hash_map;

// 创建哈希表
hash_map *create_hash_map();

// 插入键值对
void put_hash_map(hash_map *map, char *key, void *value);

// 删除键值对
void remove_hash_map(hash_map *map, char *key);

// 查找值
void *get_hash_map(hash_map *map, char *key);

// 释放哈希表
void free_hash_map(hash_map *map);

unsigned int hash(char *key,int size = TABLE_SIZE);

unsigned int hash(wchar_t *key,int size = TABLE_SIZE);

unsigned int hash(wchar_t key,int size = TABLE_SIZE);