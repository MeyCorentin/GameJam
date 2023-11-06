#include "../include/UDPserver.hpp"

int main(int ac, char **av)
{
    if (ac != 3) {
        std::cerr << "Usage: server <port>\n";
        return 1;
    }
    try {
        int port = std::stoi(av[1]);

        boost::asio::io_context io_context;
        UDPServer server(io_context, port);
        std::cout << "Server running" << std::endl;
        server.start(av[2]);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
