#pragma once
// Package: Utils

#include <string>
#include <cctype>
#include <vector>
#include <cassert>
namespace PublicUtils
{
bool IsNumber(const std::string & str);

template <class S, class It>
int Icompare(
    const S& str,
    typename S::size_type pos,
    typename S::size_type n,
    It it2,
    It end2)
    /// Case-insensitive string comparison
{
    typename S::size_type sz = str.size();
    if (pos > sz) pos = sz;
    if (pos + n > sz) n = sz - pos;
    It it1 = str.begin() + pos;
    It end1 = str.begin() + pos + n;
    while (it1 != end1 && it2 != end2)
    {
        typename S::value_type c1(static_cast<typename S::value_type>(std::tolower(*it1)));
        typename S::value_type c2(static_cast<typename S::value_type>(std::tolower(*it2)));
        if (c1 < c2)
        {
            return -1;
        }
        else if (c1 > c2)
        {
            return 1;
        }
        ++it1; ++it2;
    }

    if (it1 == end1)
    {
        return it2 == end2 ? 0 : -1;
    }
    else
        return 1;
}

template <class S>
int Icompare(const S& str1, const S& str2)
// A special optimization for an often used case.
{
    typename S::const_iterator it1(str1.begin());
    typename S::const_iterator end1(str1.end());
    typename S::const_iterator it2(str2.begin());
    typename S::const_iterator end2(str2.end());
    while (it1 != end1 && it2 != end2)
    {
        typename S::value_type c1(static_cast<typename S::value_type>(std::tolower(*it1)));
        typename S::value_type c2(static_cast<typename S::value_type>(std::tolower(*it2)));
        if (c1 < c2)
        {
            return -1;
        }
        else if (c1 > c2)
        {
            return 1;
        }
        ++it1; ++it2;
    }

    if (it1 == end1)
    {
        return it2 == end2 ? 0 : -1;
    }
    else
    {
        return 1;
    }
}

template <class S>
int Icompare(const S& str1, typename S::size_type n1, const S& str2, typename S::size_type n2)
{
    if (n2 > str2.size())
    {
        n2 = str2.size();
    }
    return Icompare(str1, 0, n1, str2.begin(), str2.begin() + n2);
}

template <class S>
int Icompare(const S& str1, typename S::size_type n, const S& str2)
{
    if (n > str2.size())
    {
        n = str2.size();
    }
    return Icompare(str1, 0, n, str2.begin(), str2.begin() + n);
}

template <class S>
int Icompare(const S& str1, typename S::size_type pos, typename S::size_type n, const S& str2)
{
    return Icompare(str1, pos, n, str2.begin(), str2.end());
}

template <class S>
int Icompare(
    const S& str1,
    typename S::size_type pos1,
    typename S::size_type n1,
    const S& str2,
    typename S::size_type pos2,
    typename S::size_type n2)
{
    typename S::size_type sz2 = str2.size();
    if (pos2 > sz2)
    {
        pos2 = sz2;
    }
    if (pos2 + n2 > sz2)
    {
        n2 = sz2 - pos2;
    }
    return Icompare(str1, pos1, n1, str2.begin() + pos2, str2.begin() + pos2 + n2);
}

template <class S>
int Icompare(
    const S& str1,
    typename S::size_type pos1,
    typename S::size_type n,
    const S& str2,
    typename S::size_type pos2)
{
    typename S::size_type sz2 = str2.size();
    if (pos2 > sz2)
    {
        pos2 = sz2;
    }
    if (pos2 + n > sz2)
    {
        n = sz2 - pos2;
    }
    return Icompare(str1, pos1, n, str2.begin() + pos2, str2.begin() + pos2 + n);
}

template <class S>
int Icompare(
    const S& str,
    typename S::size_type pos,
    typename S::size_type n,
    const typename S::value_type* ptr)
{
    assert(ptr);
    typename S::size_type sz = str.size();
    if (pos > sz)
    {
        pos = sz;
    }
    if (pos + n > sz)
    {
        n = sz - pos;
    }
    typename S::const_iterator it = str.begin() + pos;
    typename S::const_iterator end = str.begin() + pos + n;
    while (it != end && *ptr)
    {
        typename S::value_type c1(static_cast<typename S::value_type>(std::tolower(*it)));
        typename S::value_type c2(static_cast<typename S::value_type>(std::tolower(*ptr)));
        if (c1 < c2)
        {
            return -1;
        }
        else if (c1 > c2)
        {
            return 1;
        }
        ++it; ++ptr;
    }

    if (it == end)
    {
        return *ptr == 0 ? 0 : -1;
    }
    else
    {
        return 1;
    }
}

template <class S>
int Icompare(
    const S& str,
    typename S::size_type pos,
    const typename S::value_type* ptr)
{
    return Icompare(str, pos, str.size() - pos, ptr);
}

template <class S>
int Icompare(
    const S& str,
    const typename S::value_type* ptr)
{
    return Icompare(str, 0, str.size(), ptr);
}

template <class S>
S Trim(const S& str)
/// Returns a copy of str with all leading and
/// trailing whitespace removed.
{
    int first = 0;
    int last = int(str.size()) - 1;

    while (first <= last && std::isspace(str[first]))
    {
        ++first;
    }
    while (last >= first && std::isspace(str[last]))
    {
        --last;
    }

    return S(str, first, last - first + 1);
}

std::vector<std::string> Split(const std::string& str, const std::string& delim);
std::vector<std::wstring> Split(const std::wstring& str, const std::wstring& delim);

std::string Repeat(const std::string& str, size_t count);
std::wstring Repeat(const std::wstring& str, size_t count);

std::string Join(const std::vector<std::string>& strs, const std::string& delim);
std::wstring Join(const std::vector<std::wstring>& strs, const std::wstring& delim);

std::string Replace(const std::string &src, const std::string &substr, const std::string &replacement);
std::wstring Replace(const std::wstring &src, const std::wstring &substr, const std::wstring &replacement);

bool EndWith(const std::string& str, const std::string& end);
bool EndWith(const std::wstring& str, const std::wstring& end);
bool StartWith(const std::string& str, const std::string& start);
bool StartWith(const std::wstring& str, const std::wstring& start);
void ToLower(std::string& str);
void ToLower(std::wstring& str);
void ToUpper(std::string& str);
void ToUpper(std::wstring& str);

std::string ToLowerCopy(const std::string& str);
std::wstring ToLowerCopy(const std::wstring& str);
std::string ToUpperCopy(const std::string& str);
std::wstring ToUpperCopy(const std::wstring& str);

std::string BytesToHexString(const void *input, size_t length, bool upCase);

std::string IntToHexString(uint32_t integer, bool upCase = true);
std::string IntToHexString(int32_t integer, bool upCase = true);
std::string IntToHexString(uint64_t integer, bool upCase = true);
std::string IntToHexString(int64_t integer, bool upCase = true);
}
