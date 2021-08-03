#pragma once

#include <string>
#include <system_error>
#include <utility>
#include <memory>
#include <Windows.h>

#ifdef _WIN32

namespace PublicUtils
{
class WinSID
{
public:
    struct Account
    {
        std::string username;
        std::string domain;
    };
    static std::pair<std::error_code, std::shared_ptr<Account>> GetSIDAccount(PSID sid);
    static std::pair<std::error_code, std::shared_ptr<std::string>> GetSIDString(PSID sid);
    static std::pair<std::error_code, std::shared_ptr<SID>> CopySID(PSID sid);
    static std::pair<std::error_code, std::shared_ptr<SID>> GetAccountSID(const std::string & username);
    static std::pair<std::error_code, std::shared_ptr<SID>> GetWellknowSID(WELL_KNOWN_SID_TYPE type);
    static bool IsSIDEqual(PSID sid1, PSID sid2);
};
}
#endif
