#include "Iterator.hpp"

#include "BaseSniffer.hpp"

void Iterator::advance()
{
    std::cout << "start - advance" << std::endl;
    pkt_ = sniffer_->next_packet();

    if (!pkt_)
    {
        std::cout << "sniffer_ = 0" << std::endl;
        sniffer_ = nullptr;
    }

    std::cout << "end - advance" << std::endl;
}

bool Iterator::operator!=(const Iterator &rhs) const
{
    return !(*this == rhs);
}

bool Iterator::operator==(const Iterator &rhs) const
{
    return sniffer_ == rhs.sniffer_;
}

Packet* Iterator::operator->()
{
    return &(**this);
}

Packet &Iterator::operator*()
{
    return pkt_;
}

Iterator Iterator::operator++(int)
{
    Iterator other(*this);
    advance();
    return other;
}

Iterator &Iterator::operator++()
{
    advance();
    return *this;
}

Iterator::Iterator(BaseSniffer* sniffer)
: sniffer_(sniffer)
{
    if (sniffer_)
    {
        advance();
    }
}
