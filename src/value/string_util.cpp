//
// Created by baoxi on 2024/11/3.
//

#include "string_util.h"
#include <codecvt>
// #include <windows.h>


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

// std::string wcharToString(const wchar_t* wstr) {
//     std::wstring ws(wstr);
//     std::string str( ws.begin(), ws.end() );
//     // 使用 std::wstring 进行转换
//     // std::wstring_convert<std::codecvt_utf8<wchar_t>> converter; // std::wstring_convert 在高版本中被弃用了
//     // return converter.to_bytes(wstr); // 转换为 std::string
//     return str;
// }


std::string wcharToString(const wchar_t* wstr) {
    // 使用 std::wstring_convert 进行 UTF-8 转换
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr); // 转换为 std::string (UTF-8 编码)
}

std::string wstring_to_string(const std::wstring &wide_string)
{
    return wstring_to_string(wide_string);
}
// std::string wstring_to_string(const std::wstring &wide_string) {
//     // 这段代码来自于微软的node-pty 无法通用
//     if (wide_string.empty()) {
//         return "";
//     }
//     const auto size_needed = WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), nullptr, 0, nullptr, nullptr);
//     if (size_needed <= 0) {
//         return "";
//     }
//     std::string result(size_needed, 0);
//     WideCharToMultiByte(CP_UTF8, 0, &wide_string.at(0), (int)wide_string.size(), &result.at(0), size_needed, nullptr, nullptr);
//     return result;
// }

// std::string wcharToString(const wchar_t* wstr) {
//     // 这段代码来自于微软的node-pty
//     std::wstring wide_string(wstr);
//     return wstring_to_string(wide_string);
// }




std::wstring to_wstring(const Napi::String& str) {
    const std::u16string & u16 = str.Utf16Value(); // Utf8Value 用于1字节 Utf16Value用于2字节的 
    return std::wstring(u16.begin(), u16.end());
}

