#include "../include/UDPclient.hpp"



void start_solo(int ac, char** av)
{
    Ecs ecs(ac, av);
    std::chrono::high_resolution_clock::time_point start_time;
    std::chrono::high_resolution_clock::time_point end_time;
    std::chrono::high_resolution_clock::time_point elapsed_time;

    ecs.Create(0, av[1]);
    srand(time(NULL));
    while(true)
    {
        start_time = std::chrono::high_resolution_clock::now();
        ecs.Update(0);
        end_time =  std::chrono::high_resolution_clock::now();
        auto elapsed_time = std::chrono::duration_cast<std::chrono::duration<double>>(end_time - start_time).count();
        if (elapsed_time < (1.0 / 60))
            std::this_thread::sleep_for(std::chrono::duration<double>((1.0 / 60) - elapsed_time));
    }
}

int main(int ac, char **av)
{

    if (ac != 4 && ac != 2) {
        std::cerr << "Usage: client <host> <port> <path_game> or Usage: client  <path_game>" << std::endl;
        return 1;
    }

    if (ac == 2)
    {
        start_solo(ac, av);
    }
    else
    {
        try {
            boost::asio::io_context io_context;

            UDPClient client(io_context, av[1], std::stoi(av[2]));
            std::cout << "Client running" << std::endl;
            client.start(av[3]);
        } catch (std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
    }
    return 0;
}
