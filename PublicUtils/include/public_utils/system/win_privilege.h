#pragma once
#ifdef _WIN32
#include <memory>
#include <system_error>
#include <string>
#include <xutility>
#include <Windows.h>
namespace PublicUtils
{
struct WinPrivilegeImpl;
class WinPrivilege
{
public:
    enum class Privilege {
        kSE_CREATE_TOKEN_NAME = 0,
        kSE_ASSIGNPRIMARYTOKEN_NAME,
        kSE_LOCK_MEMORY_NAME,
        kSE_INCREASE_QUOTA_NAME,
        kSE_UNSOLICITED_INPUT_NAME,
        kSE_MACHINE_ACCOUNT_NAME,
        kSE_TCB_NAME,
        kSE_SECURITY_NAME,
        kSE_TAKE_OWNERSHIP_NAME,
        kSE_LOAD_DRIVER_NAME,
        kSE_SYSTEM_PROFILE_NAME,
        kSE_SYSTEMTIME_NAME,
        kSE_PROF_SINGLE_PROCESS_NAME,
        kSE_INC_BASE_PRIORITY_NAME,
        kSE_CREATE_PAGEFILE_NAME,
        kSE_CREATE_PERMANENT_NAME,
        kSE_BACKUP_NAME,
        kSE_RESTORE_NAME,
        kSE_SHUTDOWN_NAME,
        kSE_DEBUG_NAME,
        kSE_AUDIT_NAME,
        kSE_SYSTEM_ENVIRONMENT_NAME,
        kSE_CHANGE_NOTIFY_NAME,
        kSE_REMOTE_SHUTDOWN_NAME,
        kSE_UNDOCK_NAME,
        kSE_SYNC_AGENT_NAME,
        kSE_ENABLE_DELEGATION_NAME,
        kSE_MANAGE_VOLUME_NAME,
        kSE_IMPERSONATE_NAME,
        kSE_CREATE_GLOBAL_NAME,
        kSE_TRUSTED_CREDMAN_ACCESS_NAME,
        kSE_RELABEL_NAME,
        kSE_INC_WORKING_SET_NAME,
        kSE_TIME_ZONE_NAME,
        kSE_CREATE_SYMBOLIC_LINK_NAME,
        kSE_DELEGATE_SESSION_USER_IMPERSONATE_NAME
    };
    typedef void* HANDLE;
    WinPrivilege();
    WinPrivilege(const LUID &luid);
    ~WinPrivilege();
    LUID *operator&();
    WinPrivilege & operator =(const LUID &luid);
    operator LUID() const;
    bool operator ==(const LUID &luid) const;
    bool operator ==(const WinPrivilege &other) const;
    LUID Data() const;

    std::pair<std::error_code, std::shared_ptr<std::string>> GetName();
    std::pair<std::error_code, std::shared_ptr<std::wstring>> GetWName();
public:
    static std::pair<std::error_code, std::shared_ptr<WinPrivilege>> GetPrivilege(Privilege name);
    static std::string GetPrivilegeName(Privilege name);
    static std::wstring GetPrivilegeWName(Privilege name);
    static std::pair<std::error_code, std::shared_ptr<WinPrivilege>> GetPrivilege(const std::string &name);
    static std::pair<std::error_code, std::shared_ptr<WinPrivilege>> GetPrivilege(const std::wstring &name);
private:
    std::unique_ptr<WinPrivilegeImpl>   _impl;
};
}
#endif
