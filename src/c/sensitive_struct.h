#pragma once
#include <unordered_map> // 无序map
#include <vector>
#include <string>
#include "../hash/hash_util.h"
#include "../value/string_util.h"

#define default_children_length  4
#define first_children_length  3026 // 因为单词的第一个词肯定很多 很分散 直接将第一个map的列表扩的足够大 常用汉字有3000-3500个

typedef struct sensitive_word_node
{
    bool end;
    int children_len; // children的数量 如果超过255就不管了
    int children_num; // children 中元素的数量
    wchar_t char_word;
    sensitive_word_node* next; // 用于链表实现 处理哈希冲突 考虑到一个词后面跟着的句子可能不会特别多，所以使用链表效率也足够了。空间使用最小
    //    unsigned char *depth; // 深度不可能特别长 0-255 （单词最长) 包含 多个深度，某个单词可能处于多个深度中，使用第一个表达当前含有的长度 依然使用hash 来判断
    sensitive_word_node** children;
    //    struct sensitive_word_node *left, *right, *parent; // 用于红黑树实现 hash冲突
} sensitive_word_node, *p_sensitive_word_node;

typedef struct sensitive_word_node_father
{
    p_sensitive_word_node node; // 当前节点
    p_sensitive_word_node father; // 节点的父节点
} sensitive_word_node_father;

// 添加敏感词
void add_sensitive_word(p_sensitive_word_node& root, const wchar_t* text, int & max_txt_len , long & word_num);

// 删除敏感词
bool remove_sensitive_word(p_sensitive_word_node& root, const wchar_t* text);

// 检测并替换违禁词
bool check_sensitive_word(p_sensitive_word_node& root,  wchar_t* & text, bool do_replace = false,
                          const wchar_t* replace = L"***");

// 查找并替换违禁词
void find_word(p_sensitive_word_node& root, wchar_t* & text, int num, std::vector<std::wstring>& stringList,
               int & max_txt_len,bool do_replace = false,  const wchar_t* replace = L"***");

// 创建子节点
sensitive_word_node** create_children(p_sensitive_word_node& node, int size = default_children_length);

// 扩容子节点
sensitive_word_node** resize_children(p_sensitive_word_node& node, int befor_size, int new_size);
