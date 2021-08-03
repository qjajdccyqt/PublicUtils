#ifdef _WIN32

#include <memory>
#include <string>

namespace PublicUtils
{
struct WinFileAttributesImpl;
class WinFileAttributes
{
public:
    WinFileAttributes();
    ~WinFileAttributes();
    bool Load(const std::string & path);
    bool IsReadOnly() const;
    bool IsHidden() const;
    bool IsCompress() const;
    bool IsEncrypted() const;
    bool SetReadOnly(bool state);
    bool SetHidden(bool state);
    bool SetCompress(bool state);
    bool SetEncrypted(bool state);
private:
    std::unique_ptr<WinFileAttributesImpl>  _impl;
};
}

#endif
