//
// Created by baoxi on 2024/11/3.
//

#include "string_util.h"


wchar_t* replaceSubstring(const wchar_t* str, size_t start, size_t end, const wchar_t* replacement)
{
    // 计算替换后的新字符串长度
    size_t replacementLen = wcslen(replacement);
    size_t originalLen = wcslen(str);
    size_t newLength = originalLen - (end - start + 1) + replacementLen + 1; // +1 for null terminator

    // 动态分配新字符串的内存
    wchar_t* newStr = new wchar_t[newLength];

    // 复制原字符串的前缀部分
    wcsncpy(newStr, str, start); // 复制从开始到目标位置前的部分
    newStr[start] = L'\0'; // 添加字符串结束符

    // 添加替换字符串
    wcscat(newStr, replacement);

    // 复制原字符串的后缀部分
    wcscat(newStr, str + end + 1); // 复制从目标结束位置之后的部分

    return newStr; // 返回新字符串
}

wchar_t* new_wstr(const wchar_t* str)
{
    size_t size = wcslen(str);
    wchar_t* wideStr = new wchar_t[size+1]; // 动态分配宽字符数组 +1是增加结尾的 \0
    wcscpy(wideStr, str); // 初始化字符串
    return wideStr;
}

std::string wcharToString(const wchar_t* wstr) {
    std::wstring ws(wstr);
    std::string str( ws.begin(), ws.end() );
    // 使用 std::wstring 进行转换
    // std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    // return converter.to_bytes(wstr); // 转换为 std::string
    return str;
}
