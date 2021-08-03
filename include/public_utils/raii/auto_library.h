#pragma once

#include  <memory>
#include <string>
namespace PublicUtils
{
class AutoLibraryImpl;
class AutoLibrary
{
public:
    AutoLibrary(const std::string& path);
    AutoLibrary(const std::string& path, uint32_t flag);
    AutoLibrary();
    ~AutoLibrary();
    bool Load(const std::string& path);
    bool Load(const std::string& path, uint32_t flag);
    bool Empty() const;
    std::string Error() const;
    bool HasSymbol(const std::string& name);
    void* GetSymbol(const std::string& name);
    template <class Type>
    Type GetTypeSymbol(const std::string& name);
    AutoLibrary(const AutoLibrary&) = delete;
    AutoLibrary(const AutoLibrary&&) = delete;
    AutoLibrary& operator = (const AutoLibrary&) = delete;
    AutoLibrary& operator = (const AutoLibrary&&) = delete;
    explicit operator bool() const;
private:
    std::unique_ptr<AutoLibraryImpl> _impl;
};
template<class Type>
inline Type AutoLibrary::GetTypeSymbol(const std::string & name)
{
    return reinterpret_cast<Type>(GetSymbol(name));
}
}
