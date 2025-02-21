#include "sensitive_struct.h"
#include <node_api.h>
#include <napi.h>
#include "../value/string_util.h"

// extern  p_sensitive_word_node root ;

wchar_t* ConvertNapiStringToWchar(const Napi::String& napiString)
{
    // 获取 UTF-8 字符串
    std::string utf8String = napiString.Utf8Value();
    // 将 UTF-8 字符串转换为 std::wstring
    std::wstring wideString(utf8String.begin(), utf8String.end());
    const wchar_t* wstr = wideString.c_str();
    return new_wstr(wstr); // wideString周期接收就会变成空
}


class NodeWordDetection : public Napi::ObjectWrap<NodeWordDetection> {
public:
    NodeWordDetection(const Napi::CallbackInfo& info) : Napi::ObjectWrap<NodeWordDetection>(info) {
        root = (p_sensitive_word_node)malloc(sizeof(sensitive_word_node));
        create_children(root,first_children_length);
        root->children_num = 0;
    }

    static Napi::Object Init(Napi::Env env, Napi::Object exports) {
        Napi::Function func = DefineClass(env, "NodeWordDetection", {
            InstanceMethod("add_word", &NodeWordDetection::node_add_word),
              InstanceMethod("check_word", &NodeWordDetection::node_check_word),
              InstanceMethod("check_word_replace", &NodeWordDetection::node_check_word_replace),
              InstanceMethod("find_word", &NodeWordDetection::node_find_word),
              InstanceMethod("find_word_replace", &NodeWordDetection::node_find_word_replace),
              InstanceMethod("remove_word", &NodeWordDetection::node_remove_word),
              InstanceMethod("get_word_num", &NodeWordDetection::get_word_num),
        });
        exports.Set("NodeWordDetection", func);
        return exports;
    }

    
private:
    
    Napi::Value get_word_num(const Napi::CallbackInfo& info) {
        return Napi::Number::New(info.Env(), word_num);
    }

    void node_add_word(const Napi::CallbackInfo& info)
    {
        // 全局对象
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        // Napi::String word = info[0].As<Napi::String>();
        const std::wstring word(to_wstring(info[0].As<Napi::String>()));
        auto str = word.c_str();
        add_sensitive_word(root,str,max_txt_len);
        word_num ++;
        // delete [] str;
    }

    void node_remove_word(const Napi::CallbackInfo& info)
    {
        // 全局对象
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        const std::wstring word(to_wstring(info[0].As<Napi::String>()));
        auto str = word.c_str();
        if (remove_sensitive_word(root,str))
        {
            word_num --;
        }
    }

    Napi::Value node_check_word(const Napi::CallbackInfo& info)
    {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        const std::wstring word(to_wstring(info[0].As<Napi::String>()));
        wchar_t* str_value = new wchar_t[word.length() + 1];
        wcscpy(str_value, word.c_str());
        auto r = check_sensitive_word(root,str_value);
        delete[] str_value;
        return Napi::Boolean::New(env, r);
    }

    Napi::Value node_check_word_replace(const Napi::CallbackInfo& info)
    {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        if (info.Length() != 2 || !info[1].IsString())
        {
            Napi::TypeError::New(env, "Please check Params").ThrowAsJavaScriptException();
        }
        const std::wstring word(to_wstring(info[0].As<Napi::String>()));
        // auto str = word.c_str();
        wchar_t* str_value = new wchar_t[word.length() + 1];  // +1 为 '\0' 结尾字符
        wcscpy(str_value, word.c_str());  // 将 std::wstring 内容复制到可修改的内存
        const std::wstring replace(to_wstring(info[1].As<Napi::String>()));
        auto replace_str =replace.c_str();
        auto r = check_sensitive_word(root,str_value, true, replace_str);
        Napi::Object o = Napi::Object::New(env);
        o.Set("have", r);
        o.Set("str", Napi::String::New(env, wcharToString(str_value)));
        delete[] str_value;
        return o;
    }

    Napi::Value node_find_word(const Napi::CallbackInfo& info)
    {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        if (info.Length() != 2 || !info[1].IsNumber())
        {
            Napi::TypeError::New(env, "Please check Params").ThrowAsJavaScriptException();
        }
        const std::wstring word(to_wstring(info[0].As<Napi::String>()));
        wchar_t* str_value = new wchar_t[word.length() + 1];
        wcscpy(str_value, word.c_str());
        Napi::Number num = info[1].As<Napi::Number>();
        std::vector<std::wstring> stringList;
        find_word(root,str_value, num.Int32Value(), stringList,max_txt_len);
        delete[] str_value;
        // 创建一个 JavaScript 数组
        Napi::Array jsArray = Napi::Array::New(env, stringList.size());
        for (size_t i = 0; i < stringList.size(); ++i)
        {
            jsArray[i] = Napi::String::New(env, wstring_to_string(stringList[i]));
        }
        return jsArray;
    }

    Napi::Value node_find_word_replace(const Napi::CallbackInfo& info)
    {
        Napi::Env env = info.Env();
        Napi::HandleScope scope(env);
        if (info.Length() != 3)
        {
            Napi::TypeError::New(env, "Please check Params").ThrowAsJavaScriptException();
        }
       
        Napi::Number num = info[1].As<Napi::Number>();
        
        const std::wstring word(to_wstring(info[0].As<Napi::String>()));
        wchar_t* str_value = new wchar_t[word.length() + 1];
        wcscpy(str_value, word.c_str());
        const std::wstring replace(to_wstring(info[2].As<Napi::String>()));
        auto replace_str =replace.c_str();
        std::vector<std::wstring> stringList;
        find_word(root,str_value, num.Int32Value(), stringList, max_txt_len,true,replace_str);
        
        Napi::Object o = Napi::Object::New(env);
        // 创建一个 JavaScript 数组
        Napi::Array jsArray = Napi::Array::New(env, stringList.size());
        for (size_t i = 0; i < stringList.size(); ++i)
        {
            jsArray[i] = Napi::String::New(env, wstring_to_string(stringList[i]));
        }
        o.Set("word_list", jsArray);
        o.Set("str", Napi::String::New(env, wcharToString(str_value)));
        delete[] str_value;
        return o;
    }

    // 根节点
    p_sensitive_word_node root;
    // 总违禁词数量
    long word_num = 0;
    // 最长词字数 也是树的最深深度 只做计算单位使用 如果删除单词这个变量目前将会变得不准确
    int max_txt_len = 0;
};



Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    // 设置函数
    NodeWordDetection::Init(env, exports);
    return exports;
}
NODE_API_MODULE(node-word-detection, Init)

// NODE_API_ADDON(NodeWordDetection) // node 16会报错
