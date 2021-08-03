#pragma once
#include <vector>
#include <list>
#include <set>
#include <map>
#include <unordered_set>
#include <unordered_map>

namespace PublicUtils
{
template<typename C>
void VectorToList(const std::vector<C> & source, std::list<C> &dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item);
    }
}

template<typename C>
void ListToVector(const std::list<C> & source, std::vector<C> &dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item);
    }
}

template<typename C>
void SetToVector(const std::set<C> & source, std::vector<C> &dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item);
    }
}

template<typename C>
void VectorToSet(const std::vector<C> & source, std::set<C> &dest)
{
    for (auto & item : source)
    {
        dest.emplace(item);
    }
}

template<typename C>
void SetToList(const std::set<C> & source, std::list<C> &dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item);
    }
}

template<typename C>
void ListToSet(const std::list<C> & source, std::set<C> &dest)
{
    for (auto & item : source)
    {
        dest.emplace(item);
    }
}

template<typename C>
void SetToVector(const std::unordered_set<C> & source, std::vector<C> &dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item);
    }
}

template<typename C>
void VectorToSet(const std::vector<C> & source, std::unordered_set<C> &dest)
{
    for (auto & item : source)
    {
        dest.emplace(item);
    }
}

template<typename C>
void SetToList(const std::unordered_set<C> & source, std::list<C> &dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item);
    }
}

template<typename C>
void ListToSet(const std::list<C> & source, std::unordered_set<C> &dest)
{
    for (auto & item : source)
    {
        dest.emplace(item);
    }
}

template<typename C>
void SetToSet(const std::unordered_set<C> & source, std::set<C> & dest)
{
    for (auto & item : source)
    {
        dest.emplace(item);
    }
}

template<typename C>
void SetToSet(const std::set<C> & source, std::unordered_set<C> & dest)
{
    for (auto & item : source)
    {
        dest.emplace(item);
    }
}

template<typename K, typename V>
void MapToMap(const std::map<K, V> & source, std::unordered_map<K, V> & dest)
{
    for (auto & item : source)
    {
        dest.emplace(item);
    }
}

template<typename K, typename V>
void MapToMap(const std::unordered_map<K, V> & source, std::map<K, V> & dest)
{
    for (auto & item : source)
    {
        dest.emplace(item);
    }
}

template<typename K, typename V>
void MapKeysToVector(const std::map<K, V> & source, std::vector<K> & dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item.first);
    }
}

template<typename K, typename V>
void MapKeysToList(const std::map<K, V> & source, std::list<K> & dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item.first);
    }
}

template<typename K, typename V>
void MapKeysToVector(const std::multimap<K, V> & source, std::vector<K> & dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item.first);
    }
}

template<typename K, typename V>
void MapKeysToList(const std::multimap<K, V> & source, std::list<K> & dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item.first);
    }
}

template<typename K, typename V>
void MapKeysToVector(const std::unordered_map<K, V> & source, std::vector<K> & dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item.first);
    }
}

template<typename K, typename V>
void MapKeysToList(const std::unordered_map<K, V> & source, std::list<K> & dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item.first);
    }
}

template<typename K, typename V>
void MapKeysToVector(const std::unordered_multimap<K, V> & source, std::vector<K> & dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item.first);
    }
}

template<typename K, typename V>
void MapKeysToList(const std::unordered_multimap<K, V> & source, std::list<V> & dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item.first);
    }
}

template<typename K, typename V>
void MapValuesToVector(const std::map<K, V> & source, std::vector<V> & dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item.second);
    }
}

template<typename K, typename V>
void MapValuesToList(const std::map<K, V> & source, std::list<V> & dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item.second);
    }
}

template<typename K, typename V>
void MapValuesToVector(const std::multimap<K, V> & source, std::vector<V> & dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item.second);
    }
}

template<typename K, typename V>
void MapValuesToList(const std::multimap<K, V> & source, std::list<V> & dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item.second);
    }
}

template<typename K, typename V>
void MapValuesToVector(const std::unordered_map<K, V> & source, std::vector<V> & dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item.second);
    }
}

template<typename K, typename V>
void MapValuesToList(const std::unordered_map<K, V> & source, std::list<V> & dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item.second);
    }
}

template<typename K, typename V>
void MapValuesToVector(const std::unordered_multimap<K, V> & source, std::vector<V> & dest)
{
    dest.reserve(source.size());
    for (auto & item : source)
    {
        dest.emplace_back(item.second);
    }
}

template<typename K, typename V>
void MapValuesToList(const std::unordered_multimap<K, V> & source, std::list<V> & dest)
{
    for (auto & item : source)
    {
        dest.emplace_back(item.second);
    }
}
}
