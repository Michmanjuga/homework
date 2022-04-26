#pragma once

#include <ostream>
#include <string>
#include <vector>

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
        return os << endl;
    }

    template<>
    ostream& operator<<(ostream& os, const vector<ip_addr>& data)
    {
        for(auto ip : data)
        {
            os  << static_cast<uint32_t>(ip.byte[0]) << '.' 
                << static_cast<uint32_t>(ip.byte[1]) << '.' 
                << static_cast<uint32_t>(ip.byte[2]) << '.' 
                << static_cast<uint32_t>(ip.byte[3]) << endl;
        }
        return os;
    }
}
