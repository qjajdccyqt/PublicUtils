#pragma once
#include <memory>
#include <string>

namespace PublicUtils
{
class FileMutexImpl;
class FileMutex
{
public:
    FileMutex(const std::string & name);
    FileMutex(const std::string & path, const std::string & name);
    ~FileMutex();

    void Lock();
    bool TryLock();
    void Unlock();
private:
    FileMutex(const FileMutex&) = delete;
    FileMutex(FileMutex &&) = delete;
    FileMutex & operator = (const FileMutex&) = delete;
    FileMutex &operator=(FileMutex &&) = delete;
private:
    std::unique_ptr<FileMutexImpl>  _impl;
};
}
