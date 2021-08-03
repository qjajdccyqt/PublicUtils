#pragma once

#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <vector>
namespace PublicUtils
{
class NetAdapterImpl;
class NetAdapter
{
public:
    struct IpAddress
    {
        std::string ip;
        std::string mask;
        friend bool operator<(const IpAddress& left, const IpAddress& right)
        {
            if (left.ip == right.ip)
            {
                return left.mask < right.mask;
            }
            else
            {
                return left.ip < right.mask;
            }
        }
        friend bool operator==(const IpAddress& left, const IpAddress& right)
        {
            return left.ip == right.ip && left.mask == right.mask;
        }

        friend std::ostream& operator<<(std::ostream& os, const IpAddress& value)
        {
            os << "ip:" << value.ip << " mask:" << value.mask;
            return os;
        }
    };

    ~NetAdapter();
    NetAdapter(const NetAdapter& other);
    NetAdapter(NetAdapter&& other);
    bool IsLookback() const;
    bool IsVirtual() const;
    bool IsEthernet() const;
    bool IsWireless() const;
    //需要管理员权限
    bool Enable();
    //需要管理员权限
    bool Disable();
    bool IsEnable() const;
    bool IsConnected() const;
#ifdef _WIN32
    bool IsConnectedInternet() const;
#endif
    std::string              GetId() const;
    std::string              GetDisplayName() const;
    std::string              GetDeviceName() const;
    std::string              GetMac(const std::string& split = ":") const;
    std::vector<IpAddress>   GetAddress() const;
    std::vector<std::string> GetGateway() const;
    std::vector<std::string> GetDnsSuffix() const;
    std::vector<std::string> GetDnsServer() const;
    std::string              GetDhcpServer();
    uint64_t                 GetSpeedLimit() const;
    //枚举所有网卡信息
    static std::vector<NetAdapter> List();
    //枚举所有网卡信息，可以获取到被禁用网卡和NIC网卡的MAC，并且不使用用COM接口，避免了内存泄露，此接口为新添加的测试接口，不保证完全可靠
    static std::vector<NetAdapter> ListAll();
    friend class NetChangeNotify;

private:
    NetAdapter();

private:
    std::unique_ptr<NetAdapterImpl> _impl;
};
#ifdef _WIN32
class NetChangeNotifyImpl;
//此类内部使用INetworkListManager的COM接口，此接口依赖windows的netprofm服务，此服务并不稳定，我们经常接到服务无法启动和网络状态不正确的报告
//你并不应该在关键业务代码中依赖此类的正确运行，此类只能作为一种辅助手段或者在非关键业务中使用
class NetChangeNotify
{
public:
    enum ConnectState
    {
        kDisConnected,
        kConnected,
        kConnectedInternet,
    };
    NetChangeNotify();
    ~NetChangeNotify();
    //此函数内部使用了com的advise回调接口，advise回调在线程套件com环境下必须由窗口消息循环来驱动，会导致阻塞。
    //所以必须在自由套件com环境下使用，如果在线程套件com环境下使用Start函数内部会自动创建自由套件线程来驱动，这会导致更大的资源消耗
    bool Start();
    void Stop();
    void AddConnectChangeCallback(
        const std::function<void(const NetAdapter& network, NetChangeNotify::ConnectState state)>& callback);

private:
    std::unique_ptr<NetChangeNotifyImpl> _impl;
};
#endif
} // namespace PublicUtils
