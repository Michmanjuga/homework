#include "lib.h"
#include "filter_ip.hpp"
#include "print.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    try
    {
        auto ip_pool = parse(std::cin);
        
        std::sort(std::begin(ip_pool), std::end(ip_pool), std::greater<>());

        std::cout << ip_pool;
        std::cout << filter(ip_pool, 1);
        std::cout << filter(ip_pool, 46, 70);
        std::cout << filter_any(ip_pool, 46);
    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
