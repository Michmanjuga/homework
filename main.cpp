#include "print.hpp"
#include "allocator.hpp"
#include "list.hpp"

#include <iostream>


constexpr size_t factorial(size_t value)
{
    if (value == 0ul)
        return 1ul;
    
    return value * factorial(value - 1ul);
}

int main(int, char**)
{
    // - создание экземпляра std::map<int, int>
    std::map<int, int> std_map;

    // - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    for(std::size_t number : {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u} )
        std_map.emplace( number, factorial(number) );
    std::cout << std_map << std::endl;

    // - создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10 элементами
    std::map<int, int, std::less<int>, custom::Allocator<int, 1ul>> custom_map;
    //- заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    for(std::size_t number : {0u, 1u, 2u, 3u, 4u, 5u, 6u, 7u, 8u, 9u} )
        custom_map.emplace(number, factorial(number));
    // - вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
    std::cout << custom_map << std::endl;
    
    // создание экземпляра своего контейнера для хранения значений типа int
    // custom::forward_list<int> list_custom;
    
    // заполнение 10 элементами от 0 до 9
    // создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
    // ограниченным 10 элементами
    // заполнение 10 элементами от 0 до 9
    // вывод на экран всех значений, хранящихся в контейнере
       
    return 0;
}
