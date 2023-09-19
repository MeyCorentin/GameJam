#include <iostream>
#include "../includes/main.hpp"

int main(int argc, char **argv)
{
    std::cout << "> Server start" << std::endl;
    
    BinaryProtocole proto;

    unsigned int i = 1;
    char *c = (char*)&i;

    if (proto.isLittleEndian(c))
        std::cout << "Little Endian" << std::endl;
    else
        std::cout << "Big Endian" << std::endl;

    i = proto.bigToLittleEndian(i);
    char *b = (char*)&i;

    if (proto.isLittleEndian(b))
        std::cout << "Little Endian" << std::endl;
    else
        std::cout << "Big Endian" << std::endl;
}