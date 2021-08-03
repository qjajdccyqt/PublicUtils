#pragma once
#include <functional>
#include <chrono>
namespace PublicUtils
{
class AutoTick
{
public:
    AutoTick(const std::function<void(const std::chrono::steady_clock::duration & duration)>& logCallback);

    ~AutoTick();

private:
    std::chrono::steady_clock::time_point _begin;
    std::function<void(const std::chrono::steady_clock::duration & duration)> _logCallback;
};
}
