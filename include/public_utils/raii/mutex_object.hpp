#pragma once
#include <mutex>
namespace PublicUtils
{
template<typename T>
class MutexObject
{
public:
    MutexObject()
    {
    }

    template<typename ...Args >
    MutexObject(Args...args)
        :_obj(std::forward<Args>(args)...)
    {
    }

    T* operator ->()
    {
        return &_obj;
    }

    T& operator *()
    {
        return _obj;
    }

    T& operator =(const T & obj)
    {
        _obj = obj;
        return _obj;
    }

    T& operator =(T && obj)
    {
        _obj = obj;
        return _obj;
    }

    operator T&()
    {
        return _obj;
    }

    operator T && ()
    {
        return std::move(_obj);
    }
    std::mutex& Mutex()
    {
        return _mutex;
    }
    T& Value()
    {
        return _obj;
    }
public:
    T _obj;
    std::mutex _mutex;
};

template<typename T>
class RecursiveMutexObject
{
public:
    RecursiveMutexObject()
    {
    }

    template<typename ...Args >
    RecursiveMutexObject(Args...args)
        :_obj(std::forward<Args>(args)...)
    {
    }

    T* operator ->()
    {
        return &_obj;
    }

    T& operator *()
    {
        return _obj;
    }

    T& operator =(const T & obj)
    {
        _obj = obj;
        return _obj;
    }

    T& operator =(T && obj)
    {
        _obj = obj;
        return _obj;
    }

    operator T&()
    {
        return _obj;
    }

    operator T && ()
    {
        return std::move(_obj);
    }
    std::recursive_mutex& Mutex()
    {
        return _mutex;
    }
    T& Value()
    {
        return _obj;
    }
public:
    T _obj;
    std::recursive_mutex _mutex;
};
}
#define MUTEX_OBJECT_LOCK(mutexObject) std::lock_guard<std::mutex> lock(mutexObject.Mutex());
#define RECURSIVE_MUTEX_OBJECT_LOCK(mutexObject) std::lock_guard<std::recursive_mutex> lock(mutexObject.Mutex());
