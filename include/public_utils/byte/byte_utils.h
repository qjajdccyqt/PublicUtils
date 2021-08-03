#pragma once
// Package: Utils

#include <vector>
#include <utility>
#include <memory>
#include <stdint.h>
namespace PublicUtils
{
typedef std::pair<const std::uint8_t *, size_t> Bytes;
typedef std::pair<std::shared_ptr<uint8_t>, size_t> SharedBytes;
std::vector<Bytes> ByteSplit(const Bytes &src, const Bytes &delim, size_t stride = 1);

SharedBytes ByteJoin(std::vector<Bytes> &src, const Bytes &delim);
std::string::size_type ByteFind(const Bytes &src, const Bytes &sub, size_t offset = 0, size_t stride = 1);
std::string::size_type ByteReverseFind(const Bytes &src, const Bytes &sub, size_t offset = 0, size_t stride = 1);
SharedBytes ByteReplace(const Bytes &src, const Bytes &sub, const Bytes &replacement, size_t stride = 1);

bool ByteEndWith(const Bytes &src, const Bytes &end);
bool ByteStartWith(const Bytes &src, const Bytes &start);
SharedBytes HexStringToBytes(const std::string &hex);
} // namespace PublicUtils
