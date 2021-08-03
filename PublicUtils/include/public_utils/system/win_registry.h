#pragma once
#ifdef _WIN32
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <Windows.h>

namespace PublicUtils
{
class WinRegistryImpl;

enum class RegistryRedirectType
{
    AUTO,
    WIN_KEY_32,
    WIN_KEY_64,
};

class WinRegistry
    /// This class implements a convenient interface to the
    /// Windows Registry.
    ///
    /// This class is only available on Windows platforms.
{
public:
    typedef std::vector<std::string> RegistryKeys;
    typedef std::vector<std::string> RegistryValues;
    typedef std::function<void(WinRegistry &)> ChangeNofityCallback;

    enum RegistryType
    {
        REGT_NONE = 0,
        REGT_STRING = 1,
        REGT_STRING_EXPAND = 2,
        REGT_BINARY = 3,
        REGT_DWORD = 4,
        REGT_DWORD_BIG_ENDIAN = 5,
        REGT_LINK = 6,
        REGT_MULTI_STRING = 7,
        REGT_RESOURCE_LIST = 8,
        REGT_FULL_RESOURCE_DESCRIPTOR = 9,
        REGT_RESOURCE_REQUIREMENTS_LIST = 10,
        REGT_QWORD = 11
    };

    WinRegistry(const std::string& key, bool readOnly = false, bool activeSession = false, bool preserved = true);
    /// Creates the WinRegistry.
    ///
    /// The key must start with one of the root key names
    /// like HKEY_CLASSES_ROOT, e.g. HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services.
    ///
    /// If readOnly is true, then only read access to the registry
    /// is available and any attempt to write to the registry will
    /// result in an exception.
    ///
    /// extraSam is used to pass extra flags (in addition to KEY_READ and KEY_WRITE)
    /// to the samDesired argument of RegOpenKeyEx() or RegCreateKeyEx().

    WinRegistry(HKEY hRootKey, const std::string& subKey, bool readOnly = false, bool activeSession = false, bool preserved = true);
    /// Creates the WinRegistry.
    ///
    /// If readOnly is true, then only read access to the registry
    /// is available and any attempt to write to the registry will
    /// result in an exception.
    ///
    /// extraSam is used to pass extra flags (in addition to KEY_READ and KEY_WRITE)
    /// to the samDesired argument of RegOpenKeyEx() or RegCreateKeyEx().

    ~WinRegistry();
    /// Destroys the WinRegistry.

    void SetString(const std::string& name, const std::string& value);
    /// Sets the string value (REG_SZ) with the given name.
    /// An empty name denotes the default value.

    std::string GetString(const std::string& name);

    std::string GetString(const std::string& name, const std::string& defaultValue);
    /// Returns the string value (REG_SZ) with the given name.
    /// An empty name denotes the default value.
    ///
    /// Throws a NotFoundException if the value does not exist.

    void SetStringExpand(const std::string& name, const std::string& value);
    /// Sets the expandable string value (REG_EXPAND_SZ) with the given name.
    /// An empty name denotes the default value.

    std::string GetStringExpand(const std::string& name);
    std::string GetStringExpand(const std::string& name, const std::string& defaultValue);
    /// Returns the string value (REG_EXPAND_SZ) with the given name.
    /// An empty name denotes the default value.
    /// All references to environment variables (%VAR%) in the string
    /// are expanded.
    ///
    /// Throws a NotFoundException if the value does not exist.
    ///
    ///
    std::vector<std::string> GetMultiString(const std::string& name);
    void SetMultiString(const std::string& name, const std::vector<std::string>& value);

    void SetBinary(const std::string& name, const std::vector<char>& value);
    /// Sets the string value (REG_BINARY) with the given name.
    /// An empty name denotes the default value.

    std::vector<char> GetBinary(const std::string& name);
    /// Returns the string value (REG_BINARY) with the given name.
    /// An empty name denotes the default value.
    ///
    /// Throws a NotFoundException if the value does not exist.

    void SetInt(const std::string& name, int value);
    /// Sets the numeric (REG_DWORD) value with the given name.
    /// An empty name denotes the default value.

    int GetInt(const std::string& name);
    int GetInt(const std::string& name, int defaultValue);
    /// Returns the numeric value (REG_DWORD) with the given name.
    /// An empty name denotes the default value.
    ///
    /// Throws a NotFoundException if the value does not exist.

    void SetInt64(const std::string& name, int64_t value);
    /// Sets the numeric (REG_QWORD) value with the given name.
    /// An empty name denotes the default value.

    int64_t GetInt64(const std::string& name);
    int64_t GetInt64(const std::string& name, int64_t defaultValue);
    /// Returns the numeric value (REG_QWORD) with the given name.
    /// An empty name denotes the default value.
    ///
    /// Throws a NotFoundException if the value does not exist.

    void DeleteValue(const std::string& name);
    /// Deletes the value with the given name.
    ///
    /// Throws a NotFoundException if the value does not exist.

    void DeleteKey();
    /// Recursively deletes the key and all subkeys.

    bool Exists();
    /// Returns true iff the key exists.

    RegistryType Type(const std::string& name);
    /// Returns the type of the key value.

    bool Exists(const std::string& name);
    /// Returns true iff the given value exists under that key.

    void SubKeys(RegistryKeys& keys);
    /// Appends all subKey names to keys.

    void Values(RegistryValues& vals);
    /// Appends all value names to vals;

    bool IsReadOnly() const;
    /// Returns true if the key has been opened for read-only access only.

    void SetChangeNotify(const ChangeNofityCallback & callback, bool subTree = false);

    // 对HKLM/SOFTWARE下的子项进行重定向
    void SetRedirectType(RegistryRedirectType type);

private:
    std::unique_ptr<WinRegistryImpl> _impl;
};
}
#endif
