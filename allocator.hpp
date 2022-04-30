#pragma once
#include <iostream>
#include <typeinfo>

#define UNUSED(value) ((void)(value))

namespace custom
{

template <typename T, std::size_t number = 1ul>
struct allocator
{
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = T const*;
    using const_reference = T const &;
    using size_type = std::size_t;

    template <typename U>
    struct rebind { using other = allocator<U>; };

    allocator() noexcept = default;
    ~allocator() noexcept = default;
    
    allocator(const allocator&) noexcept = default;
    allocator& operator=(const allocator&) = default;

    template<typename U>
    allocator(const allocator<U>&) noexcept {}

    pointer allocate(const size_type n)
    {
        std::cout << "allocate: [n = " << n << "]\n";
        return reinterpret_cast<pointer>(malloc(n * sizeof(T)));
    }

    void deallocate(pointer p, size_type n)
    {
        std::cout << "deallocate: [n = " << n << "]\n";
        free(p);
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args&&... args)
    {
        std::cout << "construct: [U = " << typeid(decltype(p)).name() << "]\n";
        ::new(reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p, size_type n)
    {
        std::cout << "destroy: [U = " << typeid(decltype(p)).name() << "]\n";
        p->~U();
    }
};

} // namespace custom
