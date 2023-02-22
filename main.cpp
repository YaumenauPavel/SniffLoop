#include <iostream>
#include "BaseSniffer.hpp"

int main()
{
    BaseSniffer sniffer {};
    sniffer.sniff_loop([&](const Packet &packet)
                       {
                           std::cout << "sniff_loop: " << std::endl;

                           return true;
                       });

    return 0;
}
