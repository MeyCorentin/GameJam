#include <iostream>
#include <stdint.h>
#include <string.h>
#include <vector>


class BinaryProtocole {
    public:
        struct BinaryMessage {
            uint16_t type; // 0: Player, 1: Other
            uint32_t id; // Id of element
            uint16_t x; // X position
            uint16_t y; // Y position
            uint16_t data; // Data
        };
        BinaryProtocole();
        ~BinaryProtocole();
        bool isLittleEndian(char *data);
        uint32_t bigToLittleEndian(uint32_t value);
        BinaryMessage BinToValue(const std::vector<uint16_t> buffer);
        std::vector<uint16_t> ValueToBin(BinaryMessage &message);
    private:
};
