#pragma once
#ifdef _WIN32
#include <string>
#include <memory>
#include <vector>
namespace PublicUtils
{
class WinDigtalSignImpl;
class WinDigtalSign
{
public:
    WinDigtalSign();
    ~WinDigtalSign();
    //签名者名称
    std::string GetSubjectName();
    //序列号
    std::string GetSerialNumber();
    //颁发者名称
    std::string GetIssuerName();
    friend class WinFileDigtalSign;
private:
    std::shared_ptr<WinDigtalSignImpl> _impl;
};

class WinFileDigtalSignImpl;
class WinFileDigtalSign
{
public:

    WinFileDigtalSign();
    ~WinFileDigtalSign();
public:
    //nested 表示是否解析嵌套证书，windows下的多签名是用嵌套证书实现的
    bool Load(const std::string& path, bool nested = false);
    std::vector<std::shared_ptr<WinDigtalSign>> GetDigtalSignList();
    bool HasDigtalSign();
private:
    std::unique_ptr<WinFileDigtalSignImpl> _impl;
};
}

#endif //_WIN32
