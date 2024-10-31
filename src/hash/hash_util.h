#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TABLE_SIZE 4 // 初始哈希表大小



unsigned int hash(char *key,int size = TABLE_SIZE);

unsigned int hash(wchar_t *key,int size = TABLE_SIZE);

unsigned int hash(wchar_t key,int size = TABLE_SIZE);