#pragma once

#include "Iterator.hpp"

#include <iostream>
#include <zconf.h>
#include <vector>

template <typename T, typename P, typename=void>
struct accepts_type : std::false_type
{
};

template <typename T, typename P>
struct accepts_type<T, P, typename std::enable_if<std::is_same<decltype(std::declval<T>()(
std::declval<P>())), bool>::value>::type> : std::true_type
{
};

template <typename Functor, typename Packet>
bool invoke_loop_cb(Functor &f, Packet &p,
                    typename std::enable_if<accepts_type<Functor, Packet>::value, bool>::type* = 0)
{
    return f(std::move(p));
}

template <typename Functor, typename Packet>
bool invoke_loop_cb(Functor &f, Packet &p,
                    typename std::enable_if<!accepts_type<Functor, Packet>::value && accepts_type<Functor, Packet &>::value, bool>::type* = 0)
{
    return f(p);
}

template <typename Functor, typename Packet>
bool invoke_loop_cb(Functor &f, Packet &p,
                    typename std::enable_if<!accepts_type<Functor, Packet>::value && !accepts_type<Functor, Packet &>::value, bool>::type* = 0)
{
    return f(*p);
}

class BaseSniffer
{
private:
    typedef Iterator iterator;

public:
    BaseSniffer() = default;

    virtual ~BaseSniffer() = default;

    BaseSniffer(const BaseSniffer &) = delete;
    BaseSniffer &operator=(const BaseSniffer &) = delete;

public:
    iterator begin()
    {
        return {this};
    }

    iterator end()
    {
        return {0};
    }

    BaseSniffer &operator=(BaseSniffer &&rhs) noexcept
    {
        using std::swap;
        return *this;
    }

    template <typename Functor>
    void sniff_loop(Functor function, uint32_t max_packets = 0)
    {
        std::cout << "1) start - sniff_loop" << std::endl;

        for (iterator it = begin(); it != end(); ++it)
        {
            try
            {
                if (!invoke_loop_cb(function, *it))
                {
                    return;
                }
            }
            catch (...)
            {
            }

            if (max_packets && --max_packets == 0)
            {
                return;
            }
        }

        std::cout << "end - sniff_loop" << std::endl;
    }

    template <typename Type, typename Functor>
    void sniff_loop(Type type, Functor function)
    {
        std::cout << "2) start - sniff_loop" << std::endl;

        typename Type::const_iterator it;
        for (it = type.begin(); it != type.end(); ++it)
        {
            try
            {
                if (!invoke_loop_cb(function, *it))
                {
                    return;
                }
            }
            catch (...)
            {
            }
        }

        std::cout << "end - sniff_loop" << std::endl;
    }

    Packet next_packet()
    {
        if (!*temp)
        {
            temp = std::next(vec.begin(), 1);
        }
        else
        {
            temp = vec.begin();
        }

        auto it = temp;
        return *it;
    }

    std::vector<Packet>::iterator temp;
    std::vector<Packet> vec {1, 2, 3, 4, 5};
};
