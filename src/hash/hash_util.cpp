#pragma once
#include "hash_util.h"

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


