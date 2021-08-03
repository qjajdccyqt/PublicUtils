#pragma once

#include <unordered_map>
#include <set>
#include <iterator>
#include <vector>
#include <memory>
#include <type_traits>
#include "public_utils/raii/mutex_object.hpp"

namespace PublicUtils
{
template<typename KeyType, typename ValueType, bool shared = false>
class ConcurrentUnorderedMultiMap
{
    typedef std::unordered_multimap<KeyType, typename std::conditional<shared, std::shared_ptr<ValueType>, ValueType>::type> DataType;
public:
    std::vector<typename DataType::mapped_type> Get(const KeyType& key)
    {
        std::vector<typename DataType::mapped_type> result;
        MUTEX_OBJECT_LOCK(_data);
        result.reserve(_data->count(key));
        auto range = _data->equal_range(key);
        for (auto &iter = range.first; iter != range.second; iter++)
        {
            result.emplace_back(iter->second);
        }
        return result;
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
        std::set<KeyType> keys;
        {
            MUTEX_OBJECT_LOCK(_data);
            for (auto & iter : _data.Value())
            {
                if (!keys.count(iter.first))
                {
                    keys.emplace(iter.first);
                }
            }
        }

        std::vector<KeyType> result;
        result.reserve(keys.size());
        std::copy(keys.begin(), keys.end(), std::back_inserter(result));
        return result;
    }

    DataType& Data()
    {
        return _data;
    }

    std::mutex & Mutex()
    {
        return _data.Mutex();
    }

    void Set(const KeyType& key, const ValueType & value, typename std::integral_constant<bool, !shared>::type * = 0)
    {
        MUTEX_OBJECT_LOCK(_data);
        _data->emplace(key, value);
    }

private:
    PublicUtils::MutexObject<DataType> _data;
};

template<typename KeyType, typename ValueType>
class ConcurrentUnorderedMultiMap<KeyType, ValueType, true>
{
    typedef std::unordered_multimap<KeyType, typename std::shared_ptr<ValueType>> DataType;
public:
    std::vector<typename DataType::mapped_type> Get(const KeyType& key)
    {
        std::vector<typename DataType::mapped_type> result;
        MUTEX_OBJECT_LOCK(_data);
        result.reserve(_data->count(key));
        auto range = _data->equal_range(key);
        for (auto &iter = range.first; iter != range.second; iter++)
        {
            result.emplace_back(iter->second);
        }
        return result;
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
        std::set<KeyType> keys;
        {
            MUTEX_OBJECT_LOCK(_data);
            for (auto & iter : _data.Value())
            {
                if (!keys.count(iter.first))
                {
                    keys.emplace(iter.first);
                }
            }
        }

        std::vector<KeyType> result;
        result.reserve(keys.size());
        std::copy(keys.begin(), keys.end(), std::back_inserter(result));
        return result;
    }

    DataType& Data()
    {
        return _data;
    }

    std::mutex & Mutex()
    {
        return _data.Mutex();
    }

    void Set(const KeyType& key, const ValueType & value)
    {
        auto data = std::make_shared<ValueType>(value);
        MUTEX_OBJECT_LOCK(_data);
        _data->emplace(key, data);
    }

    void Set(const KeyType& key, const std::shared_ptr<ValueType> & value)
    {
        MUTEX_OBJECT_LOCK(_data);
        _data->emplace(key, value);
    }

private:
    PublicUtils::MutexObject<DataType> _data;
};
}
