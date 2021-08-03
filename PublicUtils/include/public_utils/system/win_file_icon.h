#pragma once
#ifdef _WIN32
#include <string>
#include <vector>
#include <memory>

namespace PublicUtils
{
enum IconSize
{
    kIconSie16 = 16,
    kIconSize24 = 24,
    kIconSize32 = 32,
    kIconSize40 = 40,
    kIconSize48 = 48,
    kIconSize64 = 64,
    kIconSize96 = 96,
    kIconSize128 = 128,
    kIconSize256 = 256
};

class WinFileIconImpl;
class WinFileIcon
{
public:
    WinFileIcon();
    ~WinFileIcon();
public:
    bool Load(const std::string& filename);
    size_t GetIconGroupCounts();
    size_t GetIconCounts(size_t group = 0);
    size_t GetIconCounts(const std::string& group);

    /// @brief 获取图标文件
    /// @param saveFilename 存储路径,建议传入的后缀名是ico
    /// @param group 图标序号
    /// @param standard 参数指是否只提取标准的icon数据(长宽一致，其中包含的最大图片尺寸不超过256),因为chrome无法显示非标准的icon，所以特别添加此参数
    /// @return 是否提取成功，失败表明可能没有符合传入参数的图标可供提取
    bool GetIconGroupFile(const std::string& saveFilename, size_t group = 0, bool standard = true);
    bool GetIconGroupFile(const std::string& saveFilename, const std::string& group, bool standard = true);
    /// @brief 获取期望尺寸的图标文件
    /// @param saveFilename 存储路径,提取到的单个图片也一样包装成ico格式，所以建议传入的后缀名是ico
    /// @param size 期望的尺寸，建议使用IconSize中的值，会自动搜寻与期望尺寸最接近的尺寸图片，如果找到多个相同尺寸的候图片，使用字节数最多的。
    /// 如果函数提取成功，此参数返回实际提取到的图片尺寸
    /// @param group 图标序号
    /// @param standard 参数指是否只提取标准的icon数据(长宽一致，其中包含的最大图片尺寸不超过256),因为chrome无法显示非标准的icon，所以特别添加此参数
    /// @return 是否提取成功，失败表明可能没有符合传入参数的图标可供提取
    bool GetSizeIcoFile(const std::string& saveFilename, size_t& size, size_t group = 0, bool standard = true);
    bool GetSizeIcoFile(const std::string& saveFilename, size_t& size, const std::string& group, bool standard = true);
    /// @brief 获取图标中指定序号的图片文件
    /// @param saveFilename 存储路径,提取到的单个图片也一样包装成ico格式，所以建议传入的后缀名是ico
    /// @param group 图标序号
    /// @param index 图标中的图片序号
    /// @return 是否提取成功，失败表明可能没有符合传入参数的图片可供提取
    bool GetIcoFile(const std::string& saveFilename, size_t group = 0, size_t index = 0);
    bool GetIcoFile(const std::string& saveFilename, const std::string& group, size_t index = 0);
    /// @brief 获取图标中指定序号的图片文件
    /// @param saveFilename 存储路径,目前已知格式为png或者bmp
    /// @param group 图标序号
    /// @param index 图标中的图片序号
    /// @return 是否提取成功，失败表明可能没有符合传入参数的图片可供提取
    bool GetRawImageFile(const std::string& saveFilename, size_t group = 0, size_t index = 0);
    bool GetRawImageFile(const std::string& saveFilename, const std::string& group, size_t index = 0);
    bool IsPngIco(size_t group, size_t index);
    bool IsPngIco(const std::string& group, size_t index);
    /// @brief 获取图标中期望尺寸的图片序号
    /// @param index 函数找到了符合要求的图片,此参数返回找到的图片的序号
    /// @param group 图标序号
    /// @param standard 参数指是否只提取标准的icon数据(长宽一致，其中包含的最大图片尺寸不超过256),因为chrome无法显示非标准的icon，所以特别添加此参数
    /// @return 是否提取成功，失败表明可能没有符合传入参数的图片可供提取
    bool GetSizeIconIndex(size_t& size, size_t &index, size_t group, bool standard = true);
    bool GetSizeIconIndex(size_t& size, size_t &index, const std::string& group, bool standard = true);
private:
    std::unique_ptr<WinFileIconImpl> _impl;
};
}

#endif // _WIN32
