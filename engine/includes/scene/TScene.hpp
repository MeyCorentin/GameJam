#pragma once

#include "../main.hpp"
<<<<<<< HEAD
#include "../entity/EntityBuilder.hpp"
=======
#include "../entity/TEntity.hpp"
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c
#include "../system/TSystem.hpp"

class TScene {
    private:
        std::vector<std::shared_ptr<TEntity>>  entities;
        std::vector<std::shared_ptr<TSystem>> systems;

        std::unordered_map<sf::Keyboard::Key, bool> keyStates;
        bool running = true;
        double targetFrameTime = (1.0 / 60);

    public:
<<<<<<< HEAD
        TScene(std::vector<std::shared_ptr<TSystem>> systemList, std::vector<std::shared_ptr<TEntity>> entityList)
=======
        TScene(std::initializer_list<std::shared_ptr<TSystem>> systemList, std::initializer_list<std::shared_ptr<TEntity>> entityList)
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c
            : systems(systemList), entities(entityList) {
                for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
                    keyStates[static_cast<sf::Keyboard::Key>(i)] = false;
                }
            }

        void run() {
            sf::RenderWindow window(sf::VideoMode(1000, 1000), "R-Type");
            sf::Event event;
            std::vector<int> inputs = {0, 0, 0, 0};

            while (running)
            {
                window.clear();
                inputs = {0, 0, 0, 0};
                while (window.pollEvent(event))
                {
                    if (event.type == sf::Event::Closed)
                        window.close();
<<<<<<< HEAD
                    if (event.type == sf::Event::KeyPressed)
                        keyStates[event.key.code] = true;
                    if (event.type == sf::Event::KeyReleased)
                        keyStates[event.key.code] = false;
=======
                    if (event.type == sf::Event::KeyPressed) {
                        keyStates[event.key.code] = true;
                    }
                    if (event.type == sf::Event::KeyReleased) {
                        keyStates[event.key.code] = false;
                    }
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c
                }
                auto startTime = std::chrono::high_resolution_clock::now();
                inputs[0] = keyStates[sf::Keyboard::Z];
                inputs[1] = keyStates[sf::Keyboard::Q];
                inputs[2] = keyStates[sf::Keyboard::S];
                inputs[3] = keyStates[sf::Keyboard::D];
                for (const auto& system : systems)
                    system->compute(entities, window, inputs);
<<<<<<< HEAD
        
=======
>>>>>>> a5a4786374f43f10e1597baecd486ba09e0e679c
                auto endTime =  std::chrono::high_resolution_clock::now();
                auto elapsedTime = std::chrono::duration_cast<std::chrono::duration<double>>(endTime - startTime).count();
                if (elapsedTime < targetFrameTime) {
                    auto sleepTime = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::duration<double>(targetFrameTime - elapsedTime));
                    std::this_thread::sleep_for(sleepTime);
                }
                window.display();
            }
        }
};

