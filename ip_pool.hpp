#pragma once

#include <array>
#include <vector>
#include <string>
#include <algorithm>


struct ip_addr
{
    std::array<uint8_t, 4ul> byte;

};

bool operator==(const ip_addr&, const ip_addr&);

class ip_pool
{
public:
    ip_pool(std::istream&);

    static ip_addr convert(const std::vector<std::string>& vec_str)
    {
        ip_addr ip;
        const auto vec_size = vec_str.size();
        for(size_t idx = 0; idx < vec_size; ++idx)
            ip.byte[idx] = static_cast<uint8_t>(std::stoul(vec_str[idx]));
        return ip;
    }

    auto get() const { return _pool; }

    void sort_greater();

    std::vector<ip_addr> filter(uint8_t v) const;
    std::vector<ip_addr> filter(uint8_t v1, uint8_t v2) const;
    std::vector<ip_addr> filter_any(uint8_t v) const;

private:
    std::vector<ip_addr> _pool;
};