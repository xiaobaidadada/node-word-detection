#include "sensitive_struct.h"
#include <node_api.h>
#include <napi.h>
#include <iostream>
#include <thread>
#include <condition_variable>
#include <queue>
#include <mutex>
#include <chrono>
#include <codecvt>

extern p_sensitive_word_node root ;

typedef struct {
    const wchar_t *  word;
    Napi::Promise::Deferred deferred;
} check_param ,* p_check_param;

std::queue<check_param> queue;
std::mutex queueMutex;
std::condition_variable condition; // 可以堵塞线程的条件变量
// Napi::ThreadSafeFunction tsfn;

// void consumer() {
//     while (true) {
//         std::unique_lock<std::mutex> lock(queueMutex);
//         // 等待期间会释放 unique_lock
//         condition.wait(lock, [] { return !queue.empty(); }); // 等待直到队列非空
//
//         check_param value = queue.front();
//         queue.pop();
//         lock.unlock(); // 完成 pop后 释放锁
//         auto r = check_sensitive_word(value.word);
//         // 在主线程中处理结果
//         tsfn.BlockingCall([value,r](Napi::Env env, Napi::Function callback) {
//             Napi::HandleScope scope(env);
//             value.deferred.Resolve(Napi::Boolean::New(env, r));
//         });
//     }
// }

const wchar_t * ConvertNapiStringToWCHAR(const Napi::String& napiStr) {
    // 获取 UTF-8 字符串
    std::string utf8Str = napiStr.Utf8Value();
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    std::wstring wideStr = converter.from_bytes(utf8Str);
    const  wchar_t* nodename = wideStr.c_str();
    return nodename;
}

void add_word(const Napi::CallbackInfo &info) {
    // 全局对象
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String word = info[0].As<Napi::String>();
    add_sensitive_word(ConvertNapiStringToWCHAR(word));

}

Napi::Value check_word(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);
    Napi::String word = info[0].As<Napi::String>();
    auto str = ConvertNapiStringToWCHAR(word);
    auto r = check_sensitive_word(str);
    return Napi::Boolean::New(env, r);

//     auto str = ConvertNapiStringToWCHAR(word);
//     check_param param = { str, Napi::Promise::Deferred::New(env) };
//     queue.push(param);
//     condition.notify_one(); // 通知消费者
//     return param.deferred.Promise();
}

Napi::Object Init(Napi::Env env, Napi::Object exports) {
    // 初始化根节点
    root = (p_sensitive_word_node) malloc(sizeof (sensitive_word_node));
    create_children(root,first_children_length);
    root->children_num = 0;
//     // 开启线程
//     std::thread thread([]() {
//            consumer();
//     });
//     // 不等待子线程结束
//     thread.detach();
//     // 创建安全的线程函数
//     Napi::Function callback = Napi::Function::New(env, [](const Napi::CallbackInfo& info) {}); // 提供一个空函数 目的只是使用tsfn来创建线程函数
//     tsfn = Napi::ThreadSafeFunction::New(
//                 env,
//                 callback,  // 传递参数，子线程需要
//                 "ChildThread",                  // 线程名字
//                 0,                              // 从子线程发送到主线程的数据项队列的最大值，0是没有限制
//                 1                              // 最大线程数量，当有这么多个线程调用Release函数后，就会释放了
//     );
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




