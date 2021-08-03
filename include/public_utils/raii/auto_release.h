#pragma once
#include <functional>
namespace PublicUtils
{
class AutoRelease
{
public:
    AutoRelease(const std::function<void()>& destructor);
    AutoRelease & operator = (std::function<void()> && destructor);

    ~AutoRelease();

private:
    std::function<void()> _destructor;
};

#ifdef _WIN32
#define __PUBLIC_UTILS_CONCAT(a, b) a##b
#define __PUBLIC_UTILS_MAKE_DEFER(line) PublicUtils::AutoRelease __PUBLIC_UTILS_CONCAT(Defer, line) = [&] ()
#define PUBLIC_UTILS_DEFER __PUBLIC_UTILS_MAKE_DEFER(__LINE__)
#endif
}
