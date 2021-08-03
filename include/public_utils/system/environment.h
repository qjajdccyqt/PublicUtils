#pragma once

#include <string>
#include <vector>
#include <map>

#ifdef _WIN32
#include <Windows.h>
#endif

#include "process.h"
#include "public_utils/data_type/optional.hpp"
#include "public_utils/string/version.h"
#include "public_utils/system/win_token.h"

namespace PublicUtils
{
class Environment
{
public:
    static std::string Get(const std::string& name);
    static std::string Get(const std::string& name, const std::string& defaultValue);
    static bool Has(const std::string& name);
    static void Set(const std::string& name, const std::string& value);

#ifdef _WIN32
    //获取当前活动用户实时的环境变量
    static std::string GetReal(const std::string& name);
    //获取当前活动用户实时的环境变量
    static std::string GetReal(const std::string& name, const std::string& defaultValue);
    //获取含有环境变量的扩展字符串
    static PublicUtils::optional<std::string> GetExpandString(const std::string& path);
    //获取含有当前用户环境变量的扩展字符串
    static PublicUtils::optional<std::string> GetExpandStringReal(const std::string& path);
#endif

    static std::string OsKernelName();
    static std::string OsDisplayName();
    static std::string OsProductName();
    static PublicUtils::Version OsVersion();
    static std::string OsArchitecture();
    static bool IsOs64Bits();
    static std::string OsProductType();
    //此名称的表示通常为系统名称、内核、位数、版本、发布号的综合。
    static std::string OsFullName();
    static unsigned ProcessorCount();

#ifdef _WIN32
    static unsigned PhysicalProcessorCount();
    static bool IsWinServer();
    static bool IsWin7();
    static bool IsWin8();
    static bool IsWin8_1();
    static bool IsWin10();
    static bool IsWin7OrGreater();
    static bool IsWin8OrGreater();
    static bool IsWin8_1OrGreater();
#endif

    static bool IsUnix();
    static bool IsWindows();

    static Process::PID ProcessId();
    static std::vector<std::string>  GetActiveUsers();
    static std::string GetUser();
    static std::string GetHome();
    static std::string GetMacId();
    //获取当前可执行文件的完整路径
    static std::string GetAppPath();
    //获取当前可执行文件的完整目录
    static std::string GetAppDir();
    static PublicUtils::Version GetAppVersion();
    static std::string GetDesktopPath();

#ifdef _WIN32
#if _WIN32_WINNT >= 0x0600
    static std::string GetWindowsFolderPath(const GUID& rfid, const std::shared_ptr<WinToken> & token = nullptr);
#else
    static std::string GetWindowsFolderPath(int csidl);
#endif
    static std::string GetPublicDesktopPath();
    static PublicUtils::Version GetProductVersion();
    static PublicUtils::Version GetDllVersion();
    static std::string GetDllPath();
    static std::string GetProgramdata();
    static std::string GetAppdata();
    static std::string GetActiveUserAppdata();
    static size_t ProcessSessionId();
#else
    static std::string GetSoPath();
#endif

    static std::string GetDynamicModulePath();
    static std::string GetCurrentDateTime();
};
}
