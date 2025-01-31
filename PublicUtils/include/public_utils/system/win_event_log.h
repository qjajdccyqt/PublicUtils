﻿#pragma once
#include <string>
namespace PublicUtils
{
class WinEventLog
{
public:
    enum WinEventLogType
    {
        LOG_TYPE_INFO = 1,
        LOG_TYPE_WARN = 2,
        LOG_TYPE_ERROR = 3,
    };
    static bool ReportEventLog(const std::string & source, uint32_t id, const std::string & message, WinEventLogType type = WinEventLogType::LOG_TYPE_INFO);
};
}
