#pragma once
#ifdef _WIN32
#include <string>
#include <memory>
#include <tuple>
#include "public_utils/string/version.h"

namespace PublicUtils
{
class WinFileVersionImpl;
class WinFileVersion
{
public:
    WinFileVersion();
    ~WinFileVersion();
    bool Load(const std::string& path);
    PublicUtils::Version GetFileVersion();
    PublicUtils::Version GetProductVersion();
    std::string GetExternFileVersion();
    std::string GetExternProductVersion();
    std::string GetFileDescription();
    std::string GetInternalName();
    std::string GetCompanyName();
    std::string GetLegalCopyright();
    std::string GetOriginalFilename();
    std::string GetProductName();
    std::string GetCustomString(const std::string& key);
private:
    std::unique_ptr<WinFileVersionImpl> _impl;
};
}
#endif
