#include "sensitive_struct.h"
#include <node_api.h>
#include <napi.h>

extern p_sensitive_word_node root ;

wchar_t* ConvertNapiStringToWCHAR(const Napi::String& napiStr) {
    // 获取 UTF-8 字符串
    std::string utf8Str = napiStr.Utf8Value();
    // 计算宽字符所需的缓冲区大小
    size_t size = mbstowcs(NULL, utf8Str.c_str(), 0);
    if (size == (size_t)-1) {
        return nullptr; // 错误处理
    }
    // 分配缓冲区
    wchar_t* wideStr = new wchar_t[size + 1]; // +1 以放置结束符
    // 转换为宽字符
    mbstowcs(wideStr, utf8Str.c_str(), size + 1);
    return wideStr;
}

void add_word(const Napi::CallbackInfo &info) {
    // 全局对象
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String word = info[0].As<Napi::String>();
    auto str = ConvertNapiStringToWCHAR(word);
    add_sensitive_word(str);
    delete [] str;
}

Napi::Boolean check_word(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String word = info[0].As<Napi::String>();
    auto str = ConvertNapiStringToWCHAR(word);
    auto r = check_sensitive_word(str);
    delete [] str;
    return Napi::Boolean::New(env, r);
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // 初始化根节点
    root = (p_sensitive_word_node) malloc(sizeof (sensitive_word_node));
    create_children(root,first_children_length);
    root->children_num = 0;
    // 设置函数
    exports.Set(Napi::String::New(env, "add_word"),
                Napi::Function::New(env, add_word));
    exports.Set(Napi::String::New(env, "check_word"),
                Napi::Function::New(env, check_word));
    return exports;
}

// 模块的入口点，node addon 就是写模块的
// 名字 初始化函数
NODE_API_MODULE(get_process, Init)




