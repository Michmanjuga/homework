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
    static const size_t value = number * factorial<number - 1>::value;
};

template<>
struct factorial<0ul> {
    static const size_t value = 1ul;
};


int main(int, char**)
{
    std::map<int, int, std::less<int>, custom::allocator<std::pair<const int, int>>> fact;
    for (size_t i = 1; i < 11; ++i) {
        static size_t factorial = 1ul;
        factorial *= i;
        fact.emplace( i, factorial );
    }
    
    
    std::cout << fact << std::endl;
    
    return 0;
}
