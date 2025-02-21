//
// Created by baoxi on 2024/11/3.
//
#include <iostream>
#include <cstring> // 用于 wcscpy 和 wcslen
#include <locale>
#include <napi.h>

wchar_t* replaceSubstring(const wchar_t* str, size_t start, size_t end, const wchar_t* replacement);

wchar_t* new_wstr(const wchar_t* str);

std::string wcharToString(const wchar_t* wstr);

std::wstring to_wstring(const Napi::String& str);

std::string wstring_to_string(const std::wstring &wide_string) ;