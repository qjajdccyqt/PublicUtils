#pragma once

#include <vector>
#include <memory>
#include <type_traits>
#include "public_utils/raii/mutex_object.hpp"

namespace PublicUtils
{
template<typename ValueType, bool shared = false>
class ConcurrentVector
{
    typedef std::vector<typename std::conditional<shared, std::shared_ptr<ValueType>, ValueType>::type> DataType;
public:

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

    DataType Values()
    {
        DataType values;
        MUTEX_OBJECT_LOCK(_data);
        values = _data.Value();
        return std::move(values);
    }

    DataType& Data()
    {
        return _data;
    }

    std::mutex & Mutex()
    {
        return _data.Mutex();
    }

    void PushBack(const ValueType & value)
    {
        MUTEX_OBJECT_LOCK(_data);
        _data->emplace_back(value);
    }

private:
    PublicUtils::MutexObject<DataType> _data;
};

template<typename ValueType>
class ConcurrentVector<ValueType, true>
{
    typedef std::vector<typename std::shared_ptr<ValueType>> DataType;
public:

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

    DataType Values()
    {
        DataType values;
        MUTEX_OBJECT_LOCK(_data);
        values = _data.Value();
        return std::move(values);
    }

    DataType& Data()
    {
        return _data;
    }

    std::mutex & Mutex()
    {
        return _data.Mutex();
    }

    void PushBack(const ValueType & value)
    {
        auto data = std::make_shared<ValueType>(value);
        MUTEX_OBJECT_LOCK(_data);
        _data->emplace_back(data);
    }

    void PushBack(const std::shared_ptr<ValueType> & value)
    {
        MUTEX_OBJECT_LOCK(_data);
        _data->emplace_back(value);
    }

private:
    PublicUtils::MutexObject<DataType> _data;
};
}
