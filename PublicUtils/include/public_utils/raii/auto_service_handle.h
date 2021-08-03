#pragma once
#ifdef _WIN32
#include <Windows.h>
namespace PublicUtils
{
class AutoServiceHandle
{
public:
    AutoServiceHandle();
    AutoServiceHandle(SC_HANDLE handle);
    ~AutoServiceHandle();
    SC_HANDLE Handle();
    bool Empty() const;
    AutoServiceHandle(const AutoServiceHandle&) = delete;
    AutoServiceHandle(const AutoServiceHandle&&) = delete;
    AutoServiceHandle& operator = (const AutoServiceHandle&) = delete;
    AutoServiceHandle& operator = (const AutoServiceHandle&&) = delete;
    AutoServiceHandle& operator = (const SC_HANDLE& handle);
    operator SC_HANDLE();
    operator SC_HANDLE*();
    explicit operator bool() const;
private:
    SC_HANDLE _handle;
};
}

#endif
