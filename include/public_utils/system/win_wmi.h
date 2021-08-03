#pragma once
#ifdef _WIN32
#include <memory>
#include "public_utils/raii/com_init.h"
#include "public_utils/nlohmann_json/json.hpp"

namespace PublicUtils
{
class WMIQueryImpl;
class WMIQuery
{
public:
    WMIQuery();
    ~WMIQuery();
    //Init 和Uninit函数必须在同一线程中调用，否则会造成Com内存泄露或者内存错误
    bool Init(const std::string& nameSpace = "ROOT\\CIMV2");
    void Uninit();
    nlohmann::json Query(std::string strWql);

private:
    std::unique_ptr<WMIQueryImpl>   _impl;
};
}
#endif
