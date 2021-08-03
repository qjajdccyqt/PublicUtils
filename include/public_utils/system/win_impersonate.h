#pragma once
#ifdef _WIN32
#include "public_utils/system/win_token.h"
namespace PublicUtils
{
//此类仅在服务下生效
class ImpersonateActiveUser
{
public:
    ImpersonateActiveUser();
    ~ImpersonateActiveUser();
private:
    bool _impersonate;
};

class ImpersonateToken
{
public:
    ImpersonateToken(const WinToken & token);
    ~ImpersonateToken();
private:
    bool _impersonate;
};
}
#endif
