#pragma once
#include <iostream>
#include <typeinfo>

namespace custom
{

template <typename T, size_t Number = 1ul>
class allocator
{
public:
    using value_type = T;
    using pointer = T*;
    using reference = T&;
    using const_pointer = T const*;
    using const_reference = T const &;
    using size_type = size_t;

    template <typename U>
    struct rebind { using other = allocator<U>; };

    allocator() noexcept
    {
        _memory = ::malloc(Number * sizeof(value_type));
        _reserved = Number;
    }
    ~allocator() noexcept
    {
        free(_memory);
    }
    
    allocator(const allocator&) noexcept = default;
    allocator& operator=(const allocator&) noexcept = default;

    template<typename U>
    allocator(const allocator<U>&) noexcept {}

    pointer allocate(const size_type needed)
    {
        std::cout << "allocate with n = " << needed << std::endl;
        Number = needed;
        if (Number < (_allocated + needed)) // not enough memory exists
        {
            std::cout << "not enough memory, n = " << needed << ", _allocated = " << _allocated << std::endl;

        }

        std::cout << "enough memory" << std::endl;
        pointer result = reinterpret_cast<pointer>(_memory + _allocated);
        _allocated += needed;
        return result;
    }

    void deallocate([[maybe_unused]] pointer p, [[maybe_unused]] size_type needed)
    {
        std::cout << "deallocate: [n = " << needed << "]\n";
        // free(p);
        if (_allocated > 0)
        {
            --_allocated;
        }
        else
        {

        }
    }

    template<typename U, typename ...Args>
    void construct(U* p, Args&&... args)
    {
        std::cout << "construct: [U = " << typeid(decltype(p)).name() << "]\n";
        ::new(reinterpret_cast<void*>(p)) U(std::forward<Args>(args)...);
    }

    template<typename U>
    void destroy(U* p, size_type needed)
    {
        std::cout << "destroy: [n = " << needed << "] of [U = " << typeid(decltype(p)).name() << "]\n";
        p->~U();
    }

private:
    void* _memory{ nullptr };
    size_type _reserved { 0ul };
    size_type _allocated{ 0ul };
};

} // namespace custom
