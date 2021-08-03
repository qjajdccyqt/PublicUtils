#pragma once
#include <functional>
namespace PublicUtils
{
class AutoRaii
{
public:
    AutoRaii(const std::function<void()>& constructor, const std::function<void()>& destructor);

    ~AutoRaii();

private:
    std::function<void()> _constructor;
    std::function<void()> _destructor;
};
}
