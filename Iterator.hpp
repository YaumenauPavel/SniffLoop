#pragma once

#include <iterator>

#include "Packet.hpp"

class BaseSniffer;

class Iterator : public std::iterator<std::forward_iterator_tag, Packet>
{
public:
    /**
     * Constructs a SnifferIterator.
     * \param sniffer The sniffer to iterate.
     */
    Iterator(BaseSniffer* sniffer = nullptr);

    /**
     * Advances the iterator.
     */
    Iterator &operator++();

    /**
     * Advances the iterator.
     */
    Iterator operator++(int);

    /**
     * Dereferences the iterator.
     * \return reference to the current packet.
     */
    Packet &operator*();

    /**
     * Dereferences the iterator.
     * \return pointer to the current packet.
     */
    Packet* operator->();

    /**
     * Compares this iterator for equality.
     * \param rhs The iterator to be compared to.
     */
    bool operator==(const Iterator &rhs) const;

    /**
     * Compares this iterator for in-equality.
     * \param rhs The iterator to be compared to.
     */
    bool operator!=(const Iterator &rhs) const;

private:
    void advance();

    BaseSniffer* sniffer_;
    Packet pkt_;
};