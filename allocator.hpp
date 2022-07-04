#pragma once
#include <iostream>
#include <typeinfo>
#include <cstring>
#include <iomanip>

namespace custom
{

template <typename T, size_t Number = 1ul>
class Allocator
{
public:
    using value_type = T;
    using pointer = T*;

    template <typename U>
    struct rebind{ using other = Allocator<U, Number>; };

    Allocator() noexcept : _reserved(Number)
    {
        _memory = reinterpret_cast<pointer>(malloc(_reserved * sizeof(T)));
        std::cout << "ctor() reserved: " << _reserved << " elements ";
        std::cout << " at " << std::setbase(16) << _memory << ".\n";
    }
    
    ~Allocator() noexcept
    {
        std::cout << "dtor() _reserved: " << _reserved << " _count: " << _count << '\n';
        free(_memory);
    }

    T* allocate(const size_t amount)
    {
        std::cout << "allocate " << amount << " elements\n";
        if (_reserved < _count + amount)
        {
            _relocate(amount);
        }
        T* result = _memory + _count;
        _count += amount;
        return result;
    }

    void deallocate([[maybe_unused]] T* p, [[maybe_unused]] const size_t amount)
    {
        std::cout << "deallocate " << amount << "elements at " << std::setbase(16) << p << << "\n";
        if (!(_count < amount))
            _count -= amount;
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args&&... args)
    {
        std::cout << "construct(U* p, Args&&... ";
        (std::cout << ... << args);
        std::cout << ")\n";
        ::new(reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p, [[maybe_unused]] const size_t amount)
    {
        std::cout << "destroy " << amount << " elements at " << std::setbase(16) << p << ")\n";
        p->~U();
    }

private:
    void _relocate(const size_t amount)
    {
        std::cout << "relocate, needed " << amount << ", _count " << _count << ", _reserved " << _reserved << "\n";

        const size_t exact_new_size = _count + amount;
        const size_t remainder = exact_new_size % _reserved;
        const size_t new_reserve = (exact_new_size + remainder) * 2;
        T* new_memory = reinterpret_cast<pointer>(malloc(new_reserve * sizeof(T)));
        if constexpr (std::is_nothrow_move_constructible_v<T> || !std::is_copy_constructible_v<T>)
        {
            std::memmove(new_memory, _memory, _count * sizeof(T));
        }
        else
        {
            std::memcpy(new_memory, _memory, _count * sizeof(T));
        }

        free(_memory);
        _reserved = new_reserve;
        _memory = new_memory;
    }

private:
    T* _memory{ nullptr };
    size_t _count{ 0ul };
    size_t _reserved{ 0ul };
};

} // namespace custom
