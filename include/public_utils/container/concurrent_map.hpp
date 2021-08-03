#pragma once

#include <map>
#include <vector>
#include <memory>
#include <type_traits>
#include "public_utils/raii/mutex_object.hpp"

namespace PublicUtils
{
template<typename KeyType, typename ValueType, bool shared = false>
class ConcurrentMap
{
    typedef std::map<KeyType, typename std::conditional<shared, std::shared_ptr<ValueType>, ValueType>::type> DataType;
public:
    ValueType Get(const KeyType& key)
    {
        MUTEX_OBJECT_LOCK(_data);
        auto iter = _data->find(key);
        if (iter != _data->end())
        {
            return iter->second;
        }
        else
        {
            return ValueType();
        }
    }
    bool Remove(const KeyType& key)
    {
        MUTEX_OBJECT_LOCK(_data);
        auto size = _data->erase(key);
        return size > 0;
    }
    bool Has(const KeyType& key)
    {
        MUTEX_OBJECT_LOCK(_data);
        return _data->count(key) > 0;
    }
    void Clear()
    {
        MUTEX_OBJECT_LOCK(_data);
        _data->clear();
    }
    size_t Size()
    {
        MUTEX_OBJECT_LOCK(_data);
        return _data->size();
    }

    std::vector<typename DataType::mapped_type> Values()
    {
        std::vector<typename DataType::mapped_type> values;
        MUTEX_OBJECT_LOCK(_data);
        for (auto & iter : _data.Value())
        {
            values.emplace_back(iter.second);
        }
        return values;
    }

    std::vector<KeyType> Keys()
    {
        std::vector<KeyType> keys;
        MUTEX_OBJECT_LOCK(_data);
        for (auto & iter : _data.Value())
        {
            keys.emplace_back(iter.first);
        }
        return keys;
    }

    DataType& Data()
    {
        return _data;
    }

    std::mutex & Mutex()
    {
        return _data.Mutex();
    }

    bool Set(const KeyType& key, const ValueType & value, bool cover = true)
    {
        MUTEX_OBJECT_LOCK(_data);
        auto ret = _data->emplace(key, value);
        if (!ret.second)
        {
            if (cover)
            {
                ret.first->second = value;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

private:
    PublicUtils::MutexObject<DataType> _data;
};

template<typename KeyType, typename ValueType>
class ConcurrentMap<KeyType, ValueType, true>
{
    typedef std::map<KeyType, typename std::shared_ptr<ValueType>> DataType;
public:
    std::shared_ptr<ValueType> Get(const KeyType& key)
    {
        MUTEX_OBJECT_LOCK(_data);
        auto iter = _data->find(key);
        if (iter != _data->end())
        {
            return iter->second;
        }
        else
        {
            return nullptr;
        }
    }
    bool Remove(const KeyType& key)
    {
        MUTEX_OBJECT_LOCK(_data);
        auto size = _data->erase(key);
        return size > 0;
    }
    bool Has(const KeyType& key)
    {
        MUTEX_OBJECT_LOCK(_data);
        return _data->count(key) > 0;
    }
    void Clear()
    {
        MUTEX_OBJECT_LOCK(_data);
        _data->clear();
    }
    size_t Size()
    {
        MUTEX_OBJECT_LOCK(_data);
        return _data->size();
    }

    std::vector<typename DataType::mapped_type> Values()
    {
        std::vector<typename DataType::mapped_type> values;
        MUTEX_OBJECT_LOCK(_data);
        for (auto & iter : _data.Value())
        {
            values.emplace_back(iter.second);
        }
        return values;
    }

    std::vector<KeyType> Keys()
    {
        std::vector<KeyType> keys;
        MUTEX_OBJECT_LOCK(_data);
        for (auto & iter : _data.Value())
        {
            keys.emplace_back(iter.first);
        }
        return keys;
    }

    DataType& Data()
    {
        return _data;
    }

    std::mutex & Mutex()
    {
        return _data.Mutex();
    }

    bool Set(const KeyType& key, const ValueType & value, bool cover = true)
    {
        auto data = std::make_shared<ValueType>(value);
        MUTEX_OBJECT_LOCK(_data);
        auto ret = _data->emplace(key, data);
        if (!ret.second)
        {
            if (cover)
            {
                ret.first->second = data;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    bool Set(const KeyType& key, const std::shared_ptr<ValueType> & value, bool cover = true)
    {
        MUTEX_OBJECT_LOCK(_data);
        auto ret = _data->emplace(key, value);
        if (!ret.second)
        {
            if (cover)
            {
                ret.first->second = value;
            }
            else
            {
                return false;
            }
        }
        return true;
    }

private:
    PublicUtils::MutexObject<DataType> _data;
};
}
