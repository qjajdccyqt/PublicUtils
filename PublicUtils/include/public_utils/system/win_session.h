#pragma once
#include <vector>
#include <memory>
#include <chrono>
#include <string>
#ifdef _WIN32
namespace PublicUtils
{
class WinSessionImpl;

class WinSession
{
public:
    typedef unsigned long SessionId;
    static const  SessionId kInvalidSessionId = 0xFFFFFFFF;
    enum SessionState
    {
        Active = 0,              // User logged on to WinStation
        Connected,           // WinStation connected to client
        ConnectQuery,        // In the process of connecting to client
        Shadow,              // Shadowing another WinStation
        Disconnected,        // WinStation logged on without client
        Idle,                // Waiting for client to connect
        Listen,              // WinStation is listening for connection
        Reset,               // WinStation is being reset
        Down,                // WinStation is down due to error
        Init,
    };
    static std::vector<SessionId> ListId();
    static std::vector<SessionId> ListActiveId();
    //当前的控制台session可能不存在，需要判断结果是否等于kInvalidSessionId
    static SessionId GetConsoleId();
    static std::shared_ptr<WinSession> GetConsole();
    static std::vector<WinSession> List();
    static std::vector<WinSession> ListActiveSession();
    bool HasActiveSession();
    ~WinSession();
    WinSession(const WinSession& other);
    WinSession(WinSession&& other);
    SessionId Id();
    SessionState State();
    std::string WinStationName();
    std::chrono::system_clock::time_point LoginTime();
    std::chrono::system_clock::time_point ConnectTime();
    std::string Domain();
    std::string Username();
private:
    WinSession();
private:
    std::unique_ptr<WinSessionImpl> _impl;
};
}
#endif
