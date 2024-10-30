#include <iostream>
#include <cwctype>
#include "sensitive_struct.h"
#include <comdef.h> // wchar* 转到 char*

// 违禁词数量
long word_num = 0;
// 最长词字数 也是树的最深深度
int max_txt = 0;

p_sensitive_word_node root;


sensitive_word_node *get_hash_map_word(sensitive_word_node **children, wchar_t  key, int size) {
    if (children == NULL) {
        return NULL;
    }
    unsigned int index = hash(key, size);
    sensitive_word_node *entry = children[index];
    while (entry) {
//        (strcmp(entry->char_word, key) == 0)
        if (entry->char_word == key) {
            return entry; // 返回 void*
        }
        entry = entry->next;
    }
    return NULL; // 未找到
}

void put_hash_map_word(p_sensitive_word_node &node, wchar_t  key, p_sensitive_word_node p_node, int size) {
    if (node->children == NULL) {
        create_children(node, size);
    }
    unsigned int index = hash(key, size);
    sensitive_word_node *newEntry = p_node;
    newEntry->char_word = key;
    newEntry->next = node->children[index];
    node->children[index] = newEntry;
    // 扩容判断
    auto add_v = p_node->children_num+1;
    p_node->children_num = add_v;
    if (add_v > (p_node->children_len + 4)) {
        resize_children(p_node, p_node->children_len, add_v);
    }
}

// 插入违禁词的节点
void add_sensitive_word(const wchar_t  *text) {
    size_t length = wcslen(text);
    if (length > max_txt) {
        max_txt = length;
    }
    p_sensitive_word_node now_node = root;
    for (int i = 0; i < length; ++i) {
        wchar_t  ch = text[i];
        if (std::iswspace(ch)) {
            continue;
        }
        auto it = get_hash_map_word(now_node->children, ch, i == 0 ? now_node->children_len : default_children_length);
        if (it != NULL) {
            now_node = (p_sensitive_word_node) it;
        } else {
            word_num++;
            p_sensitive_word_node p_node = (p_sensitive_word_node) malloc(sizeof(sensitive_word_node));
            p_node->children_len = first_children_length;
            p_node->children_num = 1;
            put_hash_map_word(now_node, ch, p_node, i == 0 ? first_children_length : default_children_length);
            p_node->children = NULL;
            p_node->char_word = ch;
            p_node->end = false;
            now_node = p_node;
        }
    }
    now_node->end = true;
}

bool check_sensitive_word(const wchar_t  *text, const wchar_t  *replace) {
    size_t length = wcslen(text);
    p_sensitive_word_node now_node = root;
    for (int i = 0; i < length; ++i) {
        wchar_t  ch = text[i];
        if (std::iswspace(ch)) {
            continue;
        }
        auto it = get_hash_map_word(now_node->children, ch,now_node->children_len);
        if (it == NULL) {
            continue;
        }
        now_node = it;
        if (now_node->end) {
            return true;
        }
        for (int j = i + 1; j < length; j++) {
            wchar_t  ch1 = text[j];
            auto it1 = get_hash_map_word(now_node->children, ch1, now_node->children_len);
            if (it1 == NULL) {
                break;
            }
            now_node = it1;
            if (now_node->end) {
                return true;
            }
        }
        now_node = root;
    }
    return false;
}


sensitive_word_node **create_children(p_sensitive_word_node &node, int size) {
    node->children = (sensitive_word_node **) malloc(sizeof(sensitive_word_node *) * size);
    node->children_len = size;
    for (int i = 0; i < size; i++) {
        node->children[i] = NULL;
    }
    return node->children;
}

sensitive_word_node **resize_children(p_sensitive_word_node &node, int befor_size, int new_size) {
    node->children = (sensitive_word_node **) realloc(node->children, sizeof(sensitive_word_node *) * new_size);
    node->children_len = new_size;
    for (int i = befor_size; i < new_size; i++) {
        node->children[i] = NULL;
    }
    return node->children;
}
