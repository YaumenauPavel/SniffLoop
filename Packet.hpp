#pragma once

#include <iostream>

class Packet
{
public:
    int count = 0;

    Packet(int i = 0)
    {
        std::cout << "i: " << i << std::endl;
        count = i;
    }

    Packet(const Packet &rhs)
    // : pdu_()
    // , ts_()
    {
    }

    Packet &operator=(const Packet &rhs)
    {
        if (this != &rhs)
        {
            // delete pdu_;
            // ts_ = rhs.timestamp();
            // pdu_ = rhs.pdu() ? rhs.pdu()->clone() : 0;
        }
        return *this;
    }

    Packet(Packet &&rhs)
    // : pdu_(rhs.pdu())
    // , ts_(rhs.timestamp())
    {
        // rhs.pdu_ = nullptr;
    }

    Packet &operator=(Packet &&rhs)
    {
        if (this != &rhs)
        {
            // PDU* tmp = pdu_;
            // pdu_ = rhs.pdu_;
            // rhs.pdu_ = tmp;
            // ts_ = rhs.timestamp();
        }
        return *this;
    }

    ~Packet()
    {
        // delete pdu_;
    }

    explicit operator bool() const
    {
        // return pkt_ != nullptr;
    }

    Packet &operator/=(const Packet &rhs)
    {
        // pkt_ /= rhs;
        return *this;
    }

private:
    Packet* pkt_ = nullptr;
};
