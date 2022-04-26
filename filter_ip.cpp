#include "filter_ip.hpp"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]

bool operator>(ip_addr left, ip_addr right)
{
    return 
        left.byte[0] == right.byte[0]
        ? (left.byte[1] == right.byte[1] 
            ? (left.byte[2] == right.byte[2] 
                ? (left.byte[3] > right.byte[3])
                : left.byte[2] > right.byte[2])
            : left.byte[1] > right.byte[1])
        : left.byte[0] > right.byte[0];
}


std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}

ip_addr convert(std::vector<std::string> ip_vec)
{
    ip_addr ip {0};
    const auto vec_size = ip_vec.size();
    for(size_t idx = 0; idx < vec_size; ++idx)
        ip.byte[idx] = static_cast<uint8_t>(std::stoul(ip_vec[idx]));
    return ip;
}

std::vector<ip_addr> parse(std::istream& is)
{
    std::vector<ip_addr> ip_pool;
    for(std::string line; std::getline(is, line);)
    {
        auto v = split(line, '\t'); // separate
        ip_pool.push_back(convert(split(v.at(0), '.')));
    }
    return ip_pool;
}

std::vector<ip_addr> filter(std::vector<ip_addr> ip_vec, uint8_t value)
{
    std::vector<ip_addr> result{};
    result.reserve(ip_vec.size());
    for(auto ip : ip_vec)
    {
        if(ip.byte[0] == value)
            result.push_back(ip);
    }
    return result;
}

std::vector<ip_addr> filter(std::vector<ip_addr> ip_vec, uint8_t value1, uint8_t value2)
{
    std::vector<ip_addr> middle = filter(ip_vec, value1);
    std::vector<ip_addr> result;
    result.reserve(middle.size());

    for(auto ip : middle)
    {
        if(ip.byte[1] == value2)
            result.push_back(ip);
    }
    return result;
}

std::vector<ip_addr> filter_any(std::vector<ip_addr> ip_vec, uint8_t value)
{
    std::vector<ip_addr> result;
    result.reserve(ip_vec.size());

    for(auto ip : ip_vec)
    {
        if(ip.byte[0] == value || ip.byte[1] == value || ip.byte[2] == value || ip.byte[3] == value)
            result.push_back(ip);
    }
    return result;
}
