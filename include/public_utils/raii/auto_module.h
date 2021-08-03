#pragma once
#include <string>
#include <memory>

#ifdef _WIN32
#include <Windows.h>
#endif

namespace PublicUtils
{
class AutoModuleImpl;
class AutoModule
{
public:
    AutoModule();
    AutoModule(const std::string & path);
    AutoModule(const std::string & path, uint32_t flag);
#ifdef _WIN32
    AutoModule(HMODULE module);
#else
    AutoModule(void* module);
#endif
    ~AutoModule();

    bool Load(const std::string & path);
    bool Load(const std::string & path, uint32_t flag);
    void Unload();
    bool Empty() const;
    std::string Error() const;
    AutoModule(const AutoModule&) = delete;
    AutoModule(const AutoModule&&) = delete;
    AutoModule& operator = (const AutoModule&) = delete;
    AutoModule& operator = (const AutoModule&&) = delete;
#ifdef _WIN32
    HMODULE Module();
    AutoModule& operator = (const HMODULE& module);
    operator HMODULE();
    void Attach(const HMODULE& module);

#else
    void* Module();
    AutoModule& operator = (const void* module);
    operator void*();
    void Attach(const void* module);
#endif
    void Detach();
    explicit operator bool() const;
private:
    std::unique_ptr<AutoModuleImpl> _impl;
};
}
