#pragma once

#include <cstdint>
#include <array>
#include <iostream>

template <typename K, typename V, uint32_t S>
class OpenAddressMap
{
public:
    using key_type = K;
    using value_type = V;
    using index_type = uint32_t;

    auto operator[](key_type key) -> value_type&
    {
        index_type index = linear_probe_search(key);

        if (index == -1)
        {
            if (_occupancy == S)
                throw std::runtime_error("No space!");

            // This is an insertion.
            index = linear_probe_find_insert(key);
            _occupancy++;
            key_store[index] = key;
            used[index] = true;
            deleted[index] = false;
        }

        return value_store[index];
    }

    auto operator[](key_type key) const -> const value_type&
    {
        index_type index = linear_probe_search(key);

        if (index == -1)
            return value_store.end();

        return value_store[index];
    }

    auto remove(key_type key) -> void
    {
        index_type index = linear_probe_search(key);

        if (index == -1)
            throw std::runtime_error("Couldn't find key.");

        _occupancy--;
        deleted[index] = true;
    }

    auto size() const -> const index_type
    {
        return S;
    }

    auto occupancy() const -> const index_type&
    {
        return _occupancy;
    }

private:
    std::array<bool, S> used{};
    std::array<bool, S> deleted{};
    std::array<key_type, S> key_store{};
    std::array<key_type, S> value_store{};
    index_type _occupancy = 0;
    
    auto linear_probe_find_insert(const key_type& k) const -> index_type
    {
        index_type index;
        index_type attempt = 0;

        while (true)
        {
            index = get_hash(attempt, k);

            if (!used[index] || deleted[index])
                return index;

            attempt++;
        }
    }

    auto linear_probe_search(const key_type& k) const -> index_type
    {
        index_type index;
        index_type attempt = 0;

        while (true)
        {
            if (attempt == S)
                return -1;

            index = get_hash(attempt, k);

            if (!used[index])
                return -1;

            if (key_store[index] == k && !deleted[index])
                return index;

            attempt++;

        }
    }

    auto get_hash(uint32_t attempt, const key_type& k) const -> index_type
    {
        return (hash_key(k) + attempt) % S;
    }

    auto hash_key(const key_type& k) const -> index_type
    {
        return 0;
    }

};
