#pragma once

#include <stdint.h>
#include <array>
#include <string>
#ifdef _WIN32
#include <Guiddef.h>
#endif
#include "public_utils/data_type/optional.hpp"
namespace PublicUtils
{
class Uuid
{
public:
    Uuid();
    ~Uuid();
    static Uuid GenerateRandom();
    std::string toString(const std::string& split = "-", bool up = true) const;
#ifdef _WIN32
    //此方法是windows标准的字符串转换规则，默认会用{}包含，以-分割，和Uuid对象直接转化string不相等，如果要判断相等，请判断Uuid对象相等
    std::string toWindowsString()  const;
    //此方法是windows标准的字符串转换规则，默认会用{}包含，以-分割，和Uuid对象直接转化string不相等，如果要判断相等，请判断Uuid对象相等
    static std::string toString(const GUID & guid);
    static Uuid FromGuid(const GUID & guid);
    GUID toGuid()  const;
#endif
    static optional<Uuid> FromWindowsString(const std::string& guid);
private:
    typedef uint8_t ValueType;
    static const size_t DATA_LENGTH = 16;
    friend bool operator==(Uuid const & lhs, Uuid const & rhs) noexcept;
    friend bool operator<(Uuid const & lhs, Uuid const & rhs) noexcept;

    std::array<ValueType, DATA_LENGTH> _data;
};
}
