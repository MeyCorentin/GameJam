
#include "../includes/main.hpp"
#include "../includes/Ecs.hpp"

int main(int argc, char **argv)
{
    Ecs _ecs(argc, argv);
    _ecs.create();

    while(true)
    {
        auto startTime = std::chrono::high_resolution_clock::now();
        _ecs.update();
        auto endTime =  std::chrono::high_resolution_clock::now();
        auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
        if (elapsedTime < (1.0 / 60))
            std::this_thread::sleep_for(std::chrono::duration<double>((1.0 / 60) - elapsedTime));
    }
}