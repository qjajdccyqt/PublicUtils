#pragma once
#ifdef _WIN32
#include <memory>
#include <thread>
namespace PublicUtils
{
class ComInitImpl;
class ComInit
{
public:
    enum class ComType
    {
        APARTMENTTHREADED,
        MULTITHREADED,
        NEUTRAL,//此参数不能用来初始化，只能用来获取当前状态。如果初始化使用默认等于MULTITHREADED
        NONE_INIT, //此参数不能用来初始化，只能用来获取当前状态。如果初始化使用默认等于MULTITHREADED
    };
    ComInit(ComType type = ComType::APARTMENTTHREADED);
    ~ComInit();
    //当前已经初始化的类型
    ComType CurrentType();
    //当前已经初始化的线程id
    std::thread::id CurrentThreadId();
public:
    static ComType GetCurrentComType();
private:
    ComInit(const ComInit&) = delete;
    ComInit& operator = (const ComInit&) = delete;
private:
    std::unique_ptr<ComInitImpl>    _impl;
};
}

#endif
