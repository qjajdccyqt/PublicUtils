#pragma once
#ifdef _WIN32
#include <string>
#include <memory>
#include <xutility>
namespace PublicUtils
{
class WinSymlinkImpl;
class WinSymlink
{
public:
    struct HotKey
    {
        uint8_t modifierFlags;
        uint8_t virtualKey;
    };
    WinSymlink(const std::string & path);
    ~WinSymlink();
    bool Load();
    bool Apply();

    void SetPath(const std::string & path);
    std::string GetPath();

    void SetDescription(const std::string & description);
    std::string GetDescription();

    void SetWorkingDirectory(const std::string & directory);
    std::string GetWorkingDirectory();

    void SetArguments(const std::string & arguments);
    std::string GetArguments();

    void SetIconLocation(const std::string & location, size_t index = 0);
    std::pair<std::string, size_t> GetIconLocation();

    //! https://docs.microsoft.com/zh-cn/windows/win32/api/shobjidl_core/nf-shobjidl_core-ishelllinka-getshowcmd
    void SetShowCmd(int cmd);
    int GetShowCmd();

    //! https://docs.microsoft.com/zh-cn/windows/win32/api/shobjidl_core/nf-shobjidl_core-ishelllinka-gethotkey
    void SetHotkey(const HotKey hotKey);
    HotKey GetHotKey();
private:
    std::unique_ptr<WinSymlinkImpl> _impl;
};
}
#endif
