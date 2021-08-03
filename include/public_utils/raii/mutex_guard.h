#pragma once

namespace PublicUtils
{
template<typename Mutex>
class LockGuard
{
public:

    explicit LockGuard(Mutex& mutex) : _mutex(mutex)
    {
        _mutex.Lock();
    }

    ~LockGuard()
    {
        _mutex.Unlock();
    }

    LockGuard(const LockGuard&) = delete;
    LockGuard& operator=(const LockGuard&) = delete;

private:
    Mutex&  _mutex;
};
}
