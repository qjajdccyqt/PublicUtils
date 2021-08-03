#pragma once
#ifdef _WIN32
#include <string>
#include <memory>
#include <vector>
#include <chrono>
#include <xutility>
#include <system_error>
namespace PublicUtils
{
class WinServiceImpl;

class WinService
    /// This class provides an object-oriented interface to
    /// the Windows Service Control Manager for registering,
    /// unregistering, configuring, starting and stopping
    /// services.
    ///
    /// This class is only available on Windows platforms.
{
public:
    enum StartupType
    {
        SVC_AUTO_START,
        SVC_MANUAL_START,
        SVC_DISABLED,
        SVC_AUTO_START_DELAY,
        SVC_BOOT_START,
        SVC_SYSTEM_START,
    };

    enum ServiceType
    {
        SVC_UNKNOW_SERVICE,
        SVC_FILE_SYSTEM_DRIVER,
        SVC_KERNEL_DRIVER,
        SVC_WIN32_OWN_PROCESS,
        SVC_WIN32_SHARE_PROCESS,
    };

    enum ServiceState
    {
        SVC_STOPPED = 1,
        SVC_START_PENDING,
        SVC_STOP_PENDING,
        SVC_RUNNING,
        SVC_CONTINUE_PENDING,
        SVC_PAUSE_PENDING,
        SVC_PAUSED,
    };

    WinService();

    WinService(const std::string& name);
    /// Creates the WinService, using the given service name.

    ~WinService();
    /// Destroys the WinService.

    bool Load(const std::string& name = "");

    const std::string& Name() const;
    /// Returns the service name.

    void SetDisplayName(const std::string& displayName);

    std::string GetDisplayName() const;
    /// Returns the service's display name.

    void SetPath(const std::string& path);

    std::string GetPath() const;
    /// Returns the path to the service executable.
    ///
    /// Throws a NotFoundException if the service has not been registered.

    std::pair<std::error_code, bool> RegisterService();
    /// Creates a Windows service with the executable specified by path
    /// and the given displayName.
    ///

    std::pair<std::error_code, bool> UnRegisterService();
    /// Deletes the Windows service.
    ///
    /// Throws a NotFoundException if the service has not been registered.

    std::pair<std::error_code, bool> IsRunning() const;
    /// Returns true if the service is currently running.

    std::pair<std::error_code, bool> Start(const std::vector<std::string>& params = std::vector<std::string>());
    /// Starts the service.
    /// Does nothing if the service is already running.
    ///
    /// Throws a NotFoundException if the service has not been registered.

    std::pair<std::error_code, bool> Stop();
    /// Stops the service.
    /// Does nothing if the service is not running.
    ///
    /// Throws a NotFoundException if the service has not been registered.

    std::pair<std::error_code, bool> Remove();

    //此方法只能修改已经存在的服务信息，创建服务请使用RegisterService， 目前只能保存显示名、启动方式、描述、路径
    std::pair<std::error_code, bool> Save();

    void SetStartup(WinService::StartupType startup);
    /// Sets the startup mode for the service.

    WinService::StartupType GetStartup() const;
    /// Returns the startup mode for the service.

    void SetServiceType(WinService::ServiceType type);

    WinService::ServiceType GetServiceType() const;

    void SetDescription(const std::string& description);
    /// Sets the service description in the registry.

    std::string GetDescription() const;
    /// Returns the service description from the registry.

    void AddDependency(const std::string& dependency);

    std::vector<std::string> GetDependencies() const;

    void SetGuard(const std::chrono::seconds& interval);

    bool IsDriver() const;

    std::pair<std::error_code, ServiceState> GetState() const;
private:
    std::unique_ptr<WinServiceImpl> _impl;
};
}
#endif
