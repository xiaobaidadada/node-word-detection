#include <iostream>
#include <cwctype>
#include "sensitive_struct.h"

// 违禁词数量
// long word_num = 0;
// 最长词字数 也是树的最深深度
// int max_txt = 0;

// p_sensitive_word_node root;


sensitive_word_node* get_hash_map_word(sensitive_word_node** children, wchar_t key, int size)
{
    if (children == NULL)
    {
        return NULL;
    }
    unsigned int index = hash(key, size);
    sensitive_word_node* entry = children[index];
    while (entry)
    {
        //        (strcmp(entry->char_word, key) == 0)
        if (entry->char_word == key)
        {
            return entry; // 返回 void*
        }
        entry = entry->next;
    }
    return NULL; // 未找到
}

void put_hash_map_word(p_sensitive_word_node& node, wchar_t key, p_sensitive_word_node p_node, int size)
{
    if (node->children == NULL)
    {
        create_children(node, size);
    }
    unsigned int index = hash(key, size);
    // sensitive_word_node* newEntry = p_node;
    p_node->char_word = key;
    // 把头节点添加到自己，的下一个，自己成为头节点
    p_node->next = node->children[index];
    node->children[index] = p_node;
    // 扩容判断 扩容的话 之前的链表都要作废重新整理链表，就算了吧
    node->children_num = node->children_num + 1;
    if (node->children_num > node->children_len ) // 固定扩容 条件 满了就扩容 
    {
        int new_len = 0; // unsigned short 最大值 65535
        if (node->children_len < 500)
        {
            new_len = node->children_len * 2;
        }
        else
        {
            new_len = node->children_len + 500;
            if(new_len > 65535)
            {
                new_len = 65535;
            }
        }
        resize_children(node, node->children_len, new_len); // 直接扩容一倍 
    }
}

// 只是移除但是并不删除元素（不做数组收缩)
void remove_hash_map_word(p_sensitive_word_node& node, p_sensitive_word_node children_node)
{
    if (node->children == NULL)return;
    unsigned int index = hash(children_node->char_word, node->children_len);
    auto it = node->children[index];
    if (it != NULL)
    {
        delete it;
        node->children[index] = NULL;
    }
}

// 插入违禁词的节点
void add_sensitive_word(p_sensitive_word_node& root, const wchar_t* text, int & max_txt_len,long & word_num)
{
    size_t length = wcslen(text);
    if (length > max_txt_len)
    {
        max_txt_len = length;
    }
    p_sensitive_word_node now_node = root;
    int i = 0 , is_new = 0;
    for (; i < length; ++i)
    {
        wchar_t ch = text[i];
        // if (std::iswspace(ch))
        // {
        //     continue;
        // }
        auto it = get_hash_map_word(now_node->children, ch, now_node->children_len);
        if (it != NULL)
        {
            now_node = it;
        }
        else
        {
            p_sensitive_word_node p_node = (p_sensitive_word_node)malloc(sizeof(sensitive_word_node));
            p_node->children_len = default_children_length;
            p_node->children_num = 0;
            put_hash_map_word(now_node, ch, p_node, now_node->children_len); 
            p_node->children = NULL;
            p_node->end = false;
            now_node = p_node;
            is_new = 1;
        }
    }
    if (is_new == 1 || now_node->end == false)
    {
        // 一个新单词 
        word_num++;
    }
    now_node->end = true;
}

bool remove_sensitive_word(p_sensitive_word_node& root, const wchar_t* text)
{
    size_t length = wcslen(text);
    p_sensitive_word_node now_node = root;
    std::vector<sensitive_word_node_father> list;
    for (int i = 0; i < length; ++i)
    {
        wchar_t ch = text[i];
        // if (std::iswspace(ch))
        // {
        //     continue;
        // }
        auto it = get_hash_map_word(now_node->children, ch, now_node->children_len);
        if (it != NULL)
        {
            sensitive_word_node_father n;
            n.node = it;
            n.father = now_node;
            list.push_back(n);
            now_node = it;
        }
        else if (i != length - 1)
        {
            // 有一个匹配不上就失败
            return false;
        }
    }
    // 每个都匹配上了
    for (int i = list.size() - 1; i >= 0; --i)
    {
        auto it = list[i];
        if (it.node == NULL);
        remove_hash_map_word(it.father, it.node);
    }
    return true;
}

bool check_sensitive_word(p_sensitive_word_node& root,  wchar_t* & text, bool do_replace, const wchar_t* replace)
{
    size_t length = wcslen(text);
    size_t replace_len = wcslen(replace);
    p_sensitive_word_node now_node = root;
    bool r = false;
    for (int i = 0; i < length; ++i)
    {
        wchar_t ch = text[i];
        // if (std::iswspace(ch))
        // {
        //     continue;
        // }
        auto it = get_hash_map_word(now_node->children, ch, now_node->children_len);
        if (it == NULL)
        {
            continue;
        }
        now_node = it;
        if (now_node->end)
        {
            if (do_replace)
            {
                auto p = replaceSubstring(text, i, i, replace);
                delete [] text;
                text = p;
                length = wcslen(text);
                i += replace_len;
                r = true;
            }
            else
            {
                return true;
            }
        }
        for (int j = i + 1; j < length; j++)
        {
            wchar_t ch1 = text[j];
            auto it1 = get_hash_map_word(now_node->children, ch1, now_node->children_len);
            if (it1 == NULL)
            {
                break;
            }
            now_node = it1;
            if (now_node->end)
            {
                if (do_replace)
                {
                    auto p1 = replaceSubstring(text, i, j, replace);
                    delete [] text;
                    text = p1;
                    i += replace_len - 1;
                    length = wcslen(text);
                    r = true;
                }
                else
                {
                    return true;
                }
            }
        }
        now_node = root;
    }
    return r;
}

void find_word(p_sensitive_word_node& root,  wchar_t* & text, int num, std::vector<std::wstring>& stringList,
               int & max_txt_len, bool do_replace, const wchar_t* replace)
{
    size_t length = wcslen(text);
    size_t replace_len = wcslen(replace);
    p_sensitive_word_node now_node = root;
    wchar_t* arr = new wchar_t[max_txt_len + 1]; // 动态分配内存
    //     wchar_t arr[max_txt];
    int arr_len = 0;
    for (int i = 0; i < length; ++i)
    {
        arr_len = 0;
        wchar_t ch = text[i];
        arr[arr_len] = ch;
        arr_len++;
        // std::wstring result = std::wstring(1, ch); 
        // if (std::iswspace(ch))
        // {
        //     continue;
        // }
        auto it = get_hash_map_word(now_node->children, ch, now_node->children_len);
        if (it == NULL)
        {
            continue;
        }
        now_node = it;
        if (now_node->end)
        {
            if (num == -1 || stringList.size() < num)
            {
                stringList.push_back(std::wstring(1, ch));
                if (do_replace)
                {
                    auto p = replaceSubstring(text, i, i, replace);
                    delete [] text;
                    text = p;
                    length = wcslen(text);
                    i += replace_len;
                }
            }
            else
            {
                delete[] arr;
                return;
            }
        }
        for (int j = i + 1; j < length; j++)
        {
            wchar_t ch1 = text[j];
            arr[arr_len] = ch1;
            arr_len++;
            auto it1 = get_hash_map_word(now_node->children, ch1, now_node->children_len);
            if (it1 == NULL)
            {
                break;
            }
            now_node = it1;
            if (now_node->end)
            {
                if (num == -1 || stringList.size() < num)
                {
                    std::wstring part_of_string(arr + 0, arr_len);
                    stringList.push_back(part_of_string);
                    if (do_replace)
                    {
                        auto p1 = replaceSubstring(text, i, j, replace);
                        delete [] text;
                        text = p1;
                        i += replace_len - 1;
                        length = wcslen(text);
                    }
                }
                else
                {
                    delete[] arr;
                    return;
                }
            }
        }
        now_node = root;
    }
    delete[] arr;
}


sensitive_word_node** create_children(p_sensitive_word_node& node, int size)
{
    node->children = (sensitive_word_node**)malloc(sizeof(sensitive_word_node*) * size);
    node->children_len = size;
    for (int i = 0; i < size; i++)
    {
        node->children[i] = NULL;
    }
    return node->children;
}

sensitive_word_node** resize_children(p_sensitive_word_node& node, int befor_size, int new_size)
{
    node->children = (sensitive_word_node**)realloc(node->children, sizeof(sensitive_word_node*) * new_size);
    node->children_len = new_size;
  
    // 旧的位置全部重新hash
    auto list = (sensitive_word_node**)malloc(sizeof(sensitive_word_node*) * node->children_num);
    short count = 0;
    for (int i = 0; i < befor_size; i++) // 已有元素全部填进去
    {
        sensitive_word_node* entry = node->children[i];
        while (entry)
        {
            list[count] = entry;
            entry = entry->next;
            list[count]->next = NULL;
            count++;
        }
    }
    for (int i = 0; i < new_size; i++)
    {
        // 新的位置置空
        node->children[i] = NULL;
    }
    // 重新添加
    for (int i = 0; i < count; i++)
    {
        auto p_node = list[i];
        unsigned int index = hash(p_node->char_word, new_size);
        // 把头节点添加到自己，的下一个，自己成为头节点
        p_node->next = node->children[index];
        node->children[index] = p_node;
    }
    delete [] list;
    return node->children;
}
