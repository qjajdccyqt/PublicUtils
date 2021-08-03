#pragma once
#ifdef _WIN32
#include <memory>
#include <string>
#include <functional>
#define _X86_
#include <windef.h>
namespace PublicUtils
{
class WinWindow
{
public:
    static std::string GetWindowClass(HWND hwnd);
    static std::string GetWindowTitle(HWND hwnd);
    static DWORD GetWindowPid(HWND hwnd);
    static HWND GetWindowRoot(HWND hwnd);
    static HWND GetWindowParent(HWND hwnd);
    static RECT GetWindowPos(HWND hwnd);
    static bool IsExist(HWND hwnd);
    static bool IsVisible(HWND hwnd);
    static bool IsEnable(HWND hwnd);
    static bool IsMinimized(HWND hwnd);
    static bool IsMaximized(HWND hwnd);
    static bool IsChild(HWND hwnd);
    static bool IsHung(HWND hwnd);
    static DWORD GetStyle(HWND hwnd);
    static DWORD GetExtraStyle(HWND hwnd);
    static bool EnumWindow(const std::function<bool(HWND hwnd)> & callback);
    static bool EnumChildWindow(HWND parentWnd, const std::function<bool(HWND hwnd)> & callback);
};
}
#endif
