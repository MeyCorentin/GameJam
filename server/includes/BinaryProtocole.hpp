#include <iostream>
#include <stdint.h>

class BinaryProtocole {
    private:
    public:
        BinaryProtocole();
        ~BinaryProtocole();
        bool isLittleEndian(char *data);
        uint32_t bigToLittleEndian(uint32_t value);
};