#pragma once
#include <string>
#include <map>
#include <unordered_map>
#ifdef _WIN32
#include <string.h>
#else
#include <strings.h>
#endif
namespace PublicUtils
{
class StringICaseKeyCompare
{
public:
    bool operator() (std::string const &first, std::string const &second) const
    {
#ifdef _WIN32
        return _stricmp(first.c_str(), second.c_str()) < 0;
#else
        return strcasecmp(first.c_str(), second.c_str()) < 0;
#endif
    }
};

class WStringICaseKeyCompare
{
public:
    bool operator() (std::wstring const &first, std::wstring const &second) const
    {
#ifdef _WIN32
        return _wcsicmp(first.c_str(), second.c_str()) < 0;
#else
        return wcscasecmp(first.c_str(), second.c_str()) < 0;
#endif
    }
};

typedef std::map<std::string, std::string, StringICaseKeyCompare> ICaseStringMap;
typedef std::map<std::wstring, std::wstring, WStringICaseKeyCompare> ICaseWStringMap;
}
