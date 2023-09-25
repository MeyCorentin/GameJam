#include "../include/main.hpp"

int main(int ac, char **av)
{
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

    if (ac != 2) {
        std::cerr << "Usage: server <port>\n";
        return 1;
    }
    try {
        int port = std::stoi(av[1]);

        boost::asio::io_context io_context;
        UDPServer server(io_context, port);
        std::cout << "Server running" << std::endl;
        server.start();
        io_context.run();
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
