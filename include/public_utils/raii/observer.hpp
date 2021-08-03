#pragma once
#include <memory>
#include <string>
#include <list>
#include <functional>
#include <mutex>
#include <unordered_map>
namespace PublicUtils
{
template<typename Param>
class ObserverManager
{
public:
    //id从1开始，记录时可以以0表示未注册
    size_t AddObserver(const std::string & name, const std::function<void(const Param & param)> & callback)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        ++_index;
        _data.emplace(_index, std::make_pair(name, std::make_shared<std::function<void(const Param & param)>>(callback)));
        _cache.emplace(name, _index);
        return _index;
    }
    void RemoveObserver(size_t id)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto iter = _data.find(id);
        if (iter != _data.end())
        {
            auto range = _cache.equal_range(iter->second.first);
            for (auto cacheIter = range.first; cacheIter != range.second; cacheIter++)
            {
                if (cacheIter->second == id)
                {
                    _cache.erase(cacheIter);
                    break;
                }
            }
            _data.erase(iter);
        }
    }
    void Clear(const std::string & name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto range = _cache.equal_range(name);
        for (auto iter = range.first; iter != range.second; iter++)
        {
            _data.erase(iter->second);
        }
        _cache.erase(name);
    }
    void Clear()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _data.clear();
        _cache.clear();
    }
    void Emit(const std::string & name, const Param & param)
    {
        std::list<std::shared_ptr<std::function<void(const Param & param)>>> callbacks;
        {
            std::lock_guard<std::mutex> lock(_mutex);

            auto range = _cache.equal_range(name);
            for (auto iter = range.first; iter != range.second; iter++)
            {
                callbacks.emplace_back(_data[iter->second].second);
            }
        }
        for (auto & callback : callbacks)
        {
            try
            {
                (*callback)(param);
            }
            catch (std::exception &)
            {
            }
        }
    }
private:
    std::mutex _mutex;
    std::unordered_map<size_t, std::pair<std::string, std::shared_ptr<std::function<void(const Param & param)>>>> _data;
    std::unordered_multimap<std::string, size_t> _cache;
    size_t _index = 0;
};

template<>
class ObserverManager<void>
{
public:
    size_t AddObserver(const std::string & name, const std::function<void()> & callback)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        ++_index;
        _data.emplace(_index, std::make_pair(name, std::make_shared<std::function<void()>>(callback)));
        _cache.emplace(name, _index);
        return _index;
    }
    void RemoveObserver(size_t id)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto iter = _data.find(id);
        if (iter != _data.end())
        {
            auto range = _cache.equal_range(iter->second.first);
            for (auto cacheIter = range.first; cacheIter != range.second; cacheIter++)
            {
                if (cacheIter->second == id)
                {
                    _cache.erase(cacheIter);
                    break;
                }
            }
            _data.erase(iter);
        }
    }
    void Clear(const std::string & name)
    {
        std::lock_guard<std::mutex> lock(_mutex);
        auto range = _cache.equal_range(name);
        for (auto iter = range.first; iter != range.second; iter++)
        {
            _data.erase(iter->second);
        }
        _cache.erase(name);
    }
    void Clear()
    {
        std::lock_guard<std::mutex> lock(_mutex);
        _data.clear();
        _cache.clear();
    }
    void Emit(const std::string & name)
    {
        std::list<std::shared_ptr<std::function<void()>>> callbacks;
        {
            std::lock_guard<std::mutex> lock(_mutex);

            auto range = _cache.equal_range(name);
            for (auto iter = range.first; iter != range.second; iter++)
            {
                callbacks.emplace_back(_data[iter->second].second);
            }
        }
        for (auto & callback : callbacks)
        {
            try
            {
                (*callback)();
            }
            catch (std::exception &)
            {
            }
        }
    }
private:
    std::mutex _mutex;
    std::unordered_map<size_t, std::pair<std::string, std::shared_ptr<std::function<void()>>>> _data;
    std::unordered_multimap<std::string, size_t> _cache;
    size_t _index = 0;
};
}
