#pragma once
#include <string>
#include <memory>
#include "public_utils/data_type/optional.hpp"
namespace PublicUtils
{
class VersionImpl;
class Version
{
public:
    Version();
    Version(size_t major, size_t minor, size_t patch, size_t build);
    ~Version();
    Version(const Version& other);
    bool Zero() const;
    std::string ToString() const;

    size_t GetMajor() const;
    size_t GetMinor() const;
    size_t GetPatch() const;
    size_t GetBuild() const;
    void SetMajor(size_t data);
    void SetMinor(size_t data);
    void SetPatch(size_t data);
    void SetBuild(size_t data);
    Version& operator=(const Version& other);
    bool operator==(const std::string& other) const;
    bool operator==(const Version& other) const;
    bool operator>(const Version& other) const;
    bool operator>=(const Version& other) const;
    bool operator<(const Version& other) const;
    bool operator<=(const Version& other) const;
    operator std::string() const;
public:
    static PublicUtils::optional<Version> Parser(const std::string& verstr);
private:
    std::unique_ptr<VersionImpl> _impl;
};
}
