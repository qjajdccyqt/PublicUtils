#pragma once

#ifdef _WIN32
#include <vector>
#include <memory>
#include <system_error>
#include <utility>
#define _X86_
#include <windef.h>
#include "public_utils/raii/auto_handle.h"
#include "public_utils/system/win_session.h"
#include "public_utils/system/win_sid.h"
#include "public_utils/system/process.h"
#include "public_utils/system/win_privilege.h"

namespace PublicUtils
{
struct WinTokenImpl;
class WinToken
{
public:
    enum class WinTokenElevationType
    {
        kDefault,
        kFull,
        kLimited,
        kUnknow,
    };

    enum class WinTokenIntegrityLevel
    {
        kUntrusted,
        kLow,
        kMedium,
        kMediumPlus,
        kHigh,
        kSystem,
        Protected,
        kUnknow,
    };
    enum class SecurityImpersonationLevel
    {
        Anonymous = 0,
        Identification,
        Impersonation,
        Delegation,
    };
    WinToken();
    WinToken(const PublicUtils::AutoHandle &token);
    WinToken(const HANDLE token);
    WinToken(WinToken &&other);
    ~WinToken();

    std::pair<std::error_code, bool> HasLinkToken() const;
    std::pair<std::error_code, bool> IsPrimary() const;
    std::pair<std::error_code, WinSession::SessionId> GetSessionId() const;
    std::pair<std::error_code, std::shared_ptr<WinToken>> GetLinkerToken() const;
    std::pair<std::error_code, bool> IsUiAccess() const;
    std::pair<std::error_code, WinTokenElevationType> GetElevationType() const;
    std::pair<std::error_code, WinTokenIntegrityLevel> GetIntegrityLevel() const;
    std::pair<std::error_code, std::shared_ptr<SID>> GetUserSID() const;
    std::pair<std::error_code, std::shared_ptr<WinSID::Account>> GetUserAccount() const;
    std::pair<std::error_code, std::shared_ptr<std::string>> GetUserSIDString() const;
    std::pair<std::error_code, bool> GetInformation(int type, std::unique_ptr<uint8_t[]> & data) const;
    std::pair<std::error_code, bool> SetInformation(int type, const void * data, size_t size);
    std::pair<std::error_code, bool> SetSessionId(WinSession::SessionId sessionId);
    std::pair<std::error_code, bool> SetUiAccess(bool enable);
    std::pair<std::error_code, bool> EnablePrivileges(const WinPrivilege& privilege, bool enable);
    std::pair<std::error_code, bool> EnablePrivileges(WinPrivilege::Privilege privilege, bool enable);
    std::pair<std::error_code, std::shared_ptr<WinToken>> Duplicate(bool primary, SecurityImpersonationLevel level) const;
    HANDLE *operator&();
    operator HANDLE() const;
    HANDLE Handle() const;
    bool Empty() const;
public:
    static WinToken GetCurrentProcessToken();
    static WinToken GetCurrentThreadToken();
    static std::pair<std::error_code, std::shared_ptr<WinToken>> GetSessionToken(WinSession::SessionId session);
    static std::pair<std::error_code, std::shared_ptr<WinToken>> GetProcessToken(Process::PID pid);
    static std::pair<std::error_code, std::shared_ptr<WinToken>> GetProcessToken(const Process &process);
    static std::pair<std::error_code, std::shared_ptr<WinToken>> GetProcessToken(HANDLE processHandle);
private:
    WinToken(const WinToken &other) = delete;
    WinToken &operator=(const WinToken &other) = delete;

private:
    std::unique_ptr<WinTokenImpl> _impl;
};
} // namespace PublicUtils
#endif
