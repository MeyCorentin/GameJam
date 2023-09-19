#include "../includes/BinaryProtocole.hpp"

BinaryProtocole::BinaryProtocole()
{

}

BinaryProtocole::~BinaryProtocole()
{

}

bool BinaryProtocole::isLittleEndian(char *data)
{
    if (*data)
        return true;
    else
        return false;
}

uint32_t BinaryProtocole::bigToLittleEndian(uint32_t value)
{
    uint32_t b0,b1,b2,b3;
    uint32_t res;

    b0 = (value & 0x000000ff) << 24u;
    b1 = (value & 0x0000ff00) << 8u;
    b2 = (value & 0x00ff0000) >> 8u;
    b3 = (value & 0xff000000) >> 24u;

    res = b0 | b1 | b2 | b3;
    return res;
}
