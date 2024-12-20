#include "sensitive_struct.h"
#include <node_api.h>
#include <napi.h>

extern p_sensitive_word_node root ;

wchar_t* ConvertNapiStringToWchar(const Napi::String& napiString) {
    // 获取 UTF-8 字符串
    std::string utf8String = napiString.Utf8Value();
    // 将 UTF-8 字符串转换为 std::wstring
    std::wstring wideString(utf8String.begin(), utf8String.end());
    const wchar_t* wstr = wideString.c_str();
    return new_wstr(wstr); // wideString周期接收就会变成空
}

void node_add_word(const Napi::CallbackInfo &info) {
    // 全局对象
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String word = info[0].As<Napi::String>();
    auto str = ConvertNapiStringToWchar(word);
    add_sensitive_word(str);
    delete [] str;
}

Napi::Boolean node_check_word(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String word = info[0].As<Napi::String>();
    auto str = ConvertNapiStringToWchar(word);
    auto r = check_sensitive_word(str);
    delete [] str;
    return Napi::Boolean::New(env, r);
}
Napi::Object node_check_word_replace(const Napi::CallbackInfo &info) {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        if (info.Length() != 2 || !info[1].IsString())
        {
            Napi::TypeError::New(env, "Please check Params").ThrowAsJavaScriptException();
        }
        Napi::String word = info[0].As<Napi::String>();
        Napi::String replace = info[1].As<Napi::String>();
        auto str = ConvertNapiStringToWchar(word);
        auto replace_str = ConvertNapiStringToWchar(replace);
        auto r = check_sensitive_word(str,true,replace_str);
        Napi::Object o = Napi::Object::New(env);
        o.Set("have", r);
        o.Set("str", Napi::String::New(env, wcharToString(str)));
        delete [] str;
        delete [] replace_str;
        return o;
}

Napi::Array node_find_word(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    if (info.Length() != 2 || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Please check Params").ThrowAsJavaScriptException();
    }
    Napi::String word = info[0].As<Napi::String>();
    Napi::Number num = info[1].As<Napi::Number>();
    auto str = ConvertNapiStringToWchar(word);
    std::vector<std::wstring>  stringList;
    find_word(str,num.Int32Value(),stringList);
    // 创建一个 JavaScript 数组
    Napi::Array jsArray = Napi::Array::New(env, stringList.size());
    for (size_t i = 0; i < stringList.size(); ++i) {
        std::wstring wstr = stringList[i];
        std::string str(wstr.begin(), wstr.end());
        jsArray[i] = Napi::String::New(env, str);
    }
    delete [] str;
    return jsArray;
}
Napi::Object node_find_word_replace(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    if (info.Length() != 3 )
    {
        Napi::TypeError::New(env, "Please check Params").ThrowAsJavaScriptException();
    }
    Napi::String word = info[0].As<Napi::String>();
    Napi::Number num = info[1].As<Napi::Number>();
    Napi::String replace = info[2].As<Napi::String>();
    auto str = ConvertNapiStringToWchar(word);
    auto replace_str = ConvertNapiStringToWchar(replace);
    std::vector<std::wstring>  stringList;
    find_word(str,num.Int32Value(),stringList,replace_str);
    Napi::Object o = Napi::Object::New(env);
    // 创建一个 JavaScript 数组
    Napi::Array jsArray = Napi::Array::New(env, stringList.size());
    for (size_t i = 0; i < stringList.size(); ++i) {
        std::wstring wstr = stringList[i];
        std::string str(wstr.begin(), wstr.end());
        jsArray[i] = Napi::String::New(env, str);
    }
    o.Set("word_list", jsArray);
    o.Set("str", Napi::String::New(env, wcharToString(str)));
    delete [] str;
    delete [] replace_str;
    return o;
}
Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // 初始化根节点
    root = (p_sensitive_word_node) malloc(sizeof (sensitive_word_node));
    create_children(root,first_children_length);
    root->children_num = 0;
    // 设置函数
    exports.Set(Napi::String::New(env, "add_word"),
                Napi::Function::New(env, node_add_word));
    exports.Set(Napi::String::New(env, "check_word"),
                Napi::Function::New(env, node_check_word));
    exports.Set(Napi::String::New(env, "check_word_replace"),
                    Napi::Function::New(env, node_check_word_replace));
    exports.Set(Napi::String::New(env, "find_word"),
                    Napi::Function::New(env, node_find_word));
    exports.Set(Napi::String::New(env, "find_word_replace"),
                    Napi::Function::New(env, node_find_word_replace));
    return exports;
}

// 模块的入口点，node addon 就是写模块的
// 名字 初始化函数
NODE_API_MODULE(get_process, Init)




