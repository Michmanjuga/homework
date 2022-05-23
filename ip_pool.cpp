#include "ip_pool.hpp"

#include <istream>

bool operator==(const ip_addr& l, const ip_addr& r)
{
    return l.byte == r.byte;
}

std::vector<std::string> split(const std::string &str, char delim)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(delim);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(delim, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ip_pool::ip_pool(std::istream& is)
{
    const std::size_t some_big_enough_value = 10'000;
    _pool.reserve(some_big_enough_value);

    for(std::string line; std::getline(is, line);)
    {
        auto v = split(line, '\t'); // separate
        _pool.push_back(convert(split(v.at(0), '.')));
    }
    _pool.shrink_to_fit();
}

void ip_pool::sort_greater()
{
    std::sort(std::begin(_pool), std::end(_pool),
        [](const ip_addr& l, const ip_addr& r) {
            return l.byte > r.byte;
        }
    );
}

std::vector<ip_addr> ip_pool::filter(uint8_t v1) const
{
    std::vector<ip_addr> result;
    result.reserve(_pool.size());
    for(const auto& ip : _pool)
        if (ip.byte[0] == v1)
            result.push_back(ip);
    result.shrink_to_fit();
    return result;
}


std::vector<ip_addr> ip_pool::filter(uint8_t v1, uint8_t v2) const
{
    std::vector<ip_addr> result;
    result.reserve(_pool.size());
    for (const auto& ip : _pool)
        if(ip.byte[0] == v1
        && ip.byte[1] == v2)
            result.push_back(ip);
    result.shrink_to_fit();
    return result;
}


std::vector<ip_addr> ip_pool::filter_any(uint8_t v1) const
{
    std::vector<ip_addr> result;
    result.reserve(_pool.size());
    for (const auto& ip : _pool)
        if (ip.byte[0] == v1
        ||  ip.byte[1] == v1
        ||  ip.byte[2] == v1
        ||  ip.byte[3] == v1)
            result.push_back(ip);
    result.shrink_to_fit();
    return result;
}
