#pragma once
#ifdef _WIN32
#include <Windows.h>
#include "public_utils/system/process.h"
namespace PublicUtils
{
class AutoHandle
{
public:
    AutoHandle();
    AutoHandle(HANDLE handle);
    AutoHandle(AutoHandle&&);
    ~AutoHandle();
    void Close();
    HANDLE Handle() const;
    bool Empty() const;
    AutoHandle(const AutoHandle&) = delete;
    AutoHandle& operator = (const AutoHandle&) = delete;
    AutoHandle& operator = (AutoHandle&& other);
    AutoHandle& operator = (const HANDLE& handle);
    operator HANDLE() const;
    HANDLE* operator&();
    HANDLE operator*();
    explicit operator bool() const;
    void Attach(const HANDLE handle);
    void Detach();
    AutoHandle Duplicate() const;
private:
    HANDLE _handle;
};
}

#endif
