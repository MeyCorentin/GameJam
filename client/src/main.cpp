#include "../include/UDPclient.hpp"

int main(int ac, char **av)
{
    if (ac != 4) {
        std::cerr << "Usage: client <host> <port> <path_game>" << std::endl;
        return 1;
    }

    try {
        boost::asio::io_context io_context;

        UDPClient client(io_context, av[1], std::stoi(av[2]));
        std::cout << "Client running" << std::endl;
        client.start(av[3]);
    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
