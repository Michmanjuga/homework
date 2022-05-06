#include "print.hpp"
#include "allocator.hpp"

#include <iostream>
/*
    Прикладной код должен содержать следующие вызовы:
    - создание экземпляра std::map<int, int>
    - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    - создание экземпляра std::map<int, int> с новым аллокатором, ограниченным 10
    элементами
    - заполнение 10 элементами, где ключ - это число от 0 до 9, а значение - факториал ключа
    - вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
    - создание экземпляра своего контейнера для хранения значений типа int
    - заполнение 10 элементами от 0 до 9
    - создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,
    ограниченным 10 элементами
    - заполнение 10 элементами от 0 до 9
    - вывод на экран всех значений, хранящихся в контейнере
*/

template<size_t number>
struct factorial {
    static constexpr size_t value = number * factorial<number - 1>::value;
};

template<>
struct factorial<0ul> {
    static constexpr size_t value = 1ul;
};


int main(int, char**)
{
    std::map<
        int,
        int,
        std::less<int>,
        custom::allocator<std::pair<const int, int>>
    > fact;
    
    fact.emplace( 0, factorial<0>::value );
    fact.emplace( 1, factorial<1>::value );
    fact.emplace( 2, factorial<2>::value );
    fact.emplace( 3, factorial<3>::value );
    fact.emplace( 4, factorial<4>::value );
    fact.emplace( 5, factorial<5>::value );
    fact.emplace( 6, factorial<6>::value );
    fact.emplace( 7, factorial<7>::value );
    fact.emplace( 8, factorial<8>::value );
    fact.emplace( 9, factorial<9>::value );
    
    
    std::cout << fact << std::endl;
    
    return 0;
}
