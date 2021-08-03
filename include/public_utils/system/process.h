#pragma once
#include <string>
#include <set>
#include <memory>
#ifdef _WIN32
#include "public_utils/system/win_session.h"
#else
#include <sys/types.h>
#endif
namespace PublicUtils
{
class ProcessImpl;
class Process
{
public:
#ifdef _WIN32
    typedef unsigned long PID;

#else
    typedef pid_t PID;
#endif

    Process(const Process & other);
    Process(Process && other);
    ~Process();
    PID Id() const;
    std::string Name() const;
    std::string ExePath() const;
    PID ParentId() const;
#ifdef _WIN32
    WinSession::SessionId SessionId() const;
#endif
public:
    Process();
    static std::set<Process> FindProcess(const std::string& name, const std::string& exe = "");
    static std::shared_ptr<Process> FindProcess(const PID& pid);
    static bool KillProcess(const PID& pid, bool wait = false);
    static std::set<PID> ListId();
    static PID GetCurrentId();
    static Process GetCurrentProcess();
    static std::set<Process> ListProcess();
    static std::string GetProcessPath(const PID& pid);
    bool operator<(const Process& other)  const;

private:
    std::unique_ptr<ProcessImpl>    _impl;
};
}
