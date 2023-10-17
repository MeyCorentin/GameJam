#include "../include/BinaryProtocole.hpp"

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

std::vector<uint16_t> BinaryProtocole::ValueToBin(BinaryProtocole::BinaryMessage &message)
{
    std::vector<uint16_t> buffer;

    buffer.push_back(message.type);
    buffer.push_back(message.id);
    buffer.push_back(message.x);
    buffer.push_back(message.y);
    buffer.push_back(message.data);

    // for (uint16_t value : buffer)
    //     std::cout << value << std::endl;

    return buffer;
}

BinaryProtocole::BinaryMessage BinaryProtocole::BinToValue(const std::vector<uint16_t> buffer)
{
    BinaryProtocole::BinaryMessage message;

    int cmpt = 0;

    for (uint16_t value : buffer) {
        switch (cmpt) {
            case 0:
                message.type = value;
            case 1:
                message.id = value;
            case 2:
                message.x = value;
            case 3:
                message.y = value;
            case 4:
                message.data = value;
        }
        cmpt += 1;
    }

    return message;
}
