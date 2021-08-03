#pragma once
#include <string>
namespace PublicUtils
{
class CharsetUtils
{
public:
    static bool UnicodeToUTF8(const std::wstring &strSource, std::string &strDest);
    static bool UTF8ToUnicode(const std::string &strSource, std::wstring &strDest);
    static std::string UnicodeToUTF8(const std::wstring &strSource);
    static std::wstring UTF8ToUnicode(const std::string &strSource);

    static bool UnicodeToANSI(const std::wstring &strSource, std::string &strDest);
    static bool ANSIToUnicode(const std::string &strSource, std::wstring &strDest);
    static std::string UnicodeToANSI(const std::wstring &strSource);
    static std::wstring ANSIToUnicode(const std::string &strSource);

    static bool UTF8ToANSI(const std::string &strSource, std::string &strDest);
    static bool ANSIToUTF8(const std::string &strSource, std::string &strDest);
    static std::string UTF8ToANSI(const std::string &strSource);
    static std::string ANSIToUTF8(const std::string &strSource);
private:
    static bool g_init;
    static bool InitLocale();
};
}
