#pragma once

#include <string>
#include <chrono>
#include <functional>
#include <memory>
namespace PublicUtils
{
class RelativeTimerImpl;
class RelativeTimer
{
public:
    RelativeTimer();
    ~RelativeTimer();
    void AddTimerTask(const std::string & name, const std::function<void()>& callback, const std::chrono::steady_clock::duration& duration, bool once = true, bool precise = false);
    void UpdateTimerTask(const std::string & name, const std::function<void()>& callback, const std::chrono::steady_clock::duration& duration, bool once = true, bool precise = false);
    void AddTimerTask(const std::string & name, const std::function<void()>& callback, const std::chrono::steady_clock::duration& duration,
                      const std::chrono::steady_clock::duration& firstInterval, bool precise = false);
    void CancelTimerTask(const std::string & name);
    void Shutdown();
    void SetThreadName(const std::string & name);
    void SetExceptionCallcack(const std::function<void(const std::exception & exception)> & callback);
private:
    std::unique_ptr<RelativeTimerImpl> _impl;
};
}
