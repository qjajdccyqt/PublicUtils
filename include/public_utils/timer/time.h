#pragma once
#include <chrono>

namespace PublicUtils
{
void Sleep(const std::chrono::milliseconds & duration);
void Sleep(const std::chrono::seconds & duration);

class TimeClock
{
public:
    TimeClock();
    ~TimeClock();
    std::chrono::nanoseconds Elapsed() const;
    void Reset();
private:
    std::chrono::steady_clock::time_point   _clock;
};
}
