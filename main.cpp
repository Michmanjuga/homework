#include "print.hpp"

#include <iostream>
#include <vector>
#include <algorithm>


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
    try
    {
        ip_pool pool(std::cin);
        pool.sort_greater();

        std::cout << pool.get();
        std::cout << pool.filter(1);
        std::cout << pool.filter(46, 70);
        std::cout << pool.filter_any(46);

    }
    catch(const std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 0;
}
