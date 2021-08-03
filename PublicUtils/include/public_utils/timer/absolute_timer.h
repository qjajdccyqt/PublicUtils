#pragma once
#include <string>
#include <functional>
#include <memory>
#include <ctime>

namespace PublicUtils
{
class AbsoluteTimerImpl;
class AbsoluteTimer
{
public:
    AbsoluteTimer();
    ~AbsoluteTimer();
    bool AddTimerTask(const std::string & name, const std::function<void()>& callback, tm  point);
    bool UpdateTimerTask(const std::string & name, const std::function<void()>& callback, tm  point);
    void CancelTimerTask(const std::string & name);
    void Shutdown();
    void SetThreadName(const std::string & name);
    void SetExceptionCallcack(const std::function<void(const std::exception & exception)> & callback);
private:
    std::unique_ptr<AbsoluteTimerImpl> _impl;
};
}
