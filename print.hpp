#pragma once

#include <ostream>
#include <string>
#include <vector>
#include <map>

namespace std
{
    template<typename T>
    ostream& operator<<(ostream& os, const vector<T>& data)
    {
        const auto cstart = cbegin(data);
        const auto cfinish = cend(data);
        
        for(auto it = begin(data); it != cfinish; ++it)
        {
            if (!(it == cstart))
                os << ", ";
            os << *it;
        }
        return os;
    }

    template<
        typename Key,
        typename Value,
        typename Comp = std::less<Key>,
        typename Alloc = std::allocator<std::pair<const Key, Value>>
    > ostream& operator<<(ostream& os, const std::map<Key, Value, Comp, Alloc>& m)
    {
        for(const auto& [key, value] : m)
            os << key << ' ' << value << endl;
        return os;
    }
}
