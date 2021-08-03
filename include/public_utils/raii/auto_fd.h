#pragma once
#ifndef _WIN32
#include <sys/types.h>
namespace PublicUtils
{
class AutoFd
{
public:
    AutoFd();
    AutoFd(int fd);
    ~AutoFd();
    void Close();
    int Fd();
    bool Empty() const;
    AutoFd(const AutoFd&) = delete;
    AutoFd(const AutoFd&&) = delete;
    AutoFd& operator = (const AutoFd&) = delete;
    AutoFd& operator = (const AutoFd&&) = delete;
    AutoFd& operator = (const int& fd);
    explicit operator int() ;
    explicit operator int*() ;
    explicit operator bool() const;
private:
    int _fd;
};
}

#endif
