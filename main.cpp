#include "lib.h"
#include "filter_ip.hpp"
#include "print.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <filesystem>
#include <algorithm>

int main(int, char**)
{
    try
    {
        std::ifstream test_file("../test/ip_filter.tsv");
        auto ip_pool = parse(test_file);
        
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
