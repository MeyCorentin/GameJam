#pragma once

#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include <list>
#include "../system/TSystem.hpp"

class TScene {
    private:
        std::shared_ptr<sf::RenderWindow> window;
        std::shared_ptr<sf::Event> event;

    public:
        TScene(){}
        std::vector<std::shared_ptr<TEntity>> entities;
        std::vector<std::shared_ptr<TSystem>> systems;
        std::vector<std::shared_ptr<sf::Sprite>> sprites;
        std::vector<std::shared_ptr<sf::Texture>> textures;
        int framesThisSecond;
        std::unordered_map<sf::Keyboard::Key, int> keyStates;
        std::shared_ptr<sf::Clock> secondClock;
        std::shared_ptr<sf::Text> tick;
        std::shared_ptr<sf::Font> font;
        bool running = true;
        double targetFrameTime = (1.0 / 60);
        TScene( std::vector<std::shared_ptr<TSystem>> _systemList,
                std::vector<std::shared_ptr<TEntity>> _entityList,
                std::vector<std::shared_ptr<sf::Sprite>> _spriteList,
                std::vector<std::shared_ptr<sf::Texture>> _textureList)
            : systems(_systemList), entities(_entityList), sprites(_spriteList), textures(_textureList) {
                window = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1000, 1000), "R-Type"));
                framesThisSecond = 0;
                event = std::shared_ptr<sf::Event>(new sf::Event());
                secondClock = std::shared_ptr<sf::Clock>(new sf::Clock());
                tick = std::shared_ptr<sf::Text>(new sf::Text());
                font = std::shared_ptr<sf::Font>(new sf::Font());
                font->loadFromFile("../../rtype/sources/fonts/arial.ttf");
                tick->setPosition(0, 0);
                tick->setFillColor(sf::Color::White);
                tick->setCharacterSize(14),
                tick->setFont(*font);
                for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
                    keyStates[static_cast<sf::Keyboard::Key>(i)] = 0;
                }
            }


        void clearWindow()
        {
            window->clear();
        }

        std::vector<std::shared_ptr<TEntity>> getEntities()
        {
            return  entities;
        }

        std::vector<std::shared_ptr<TSystem>> getSystems()
        {
            return systems;
        }
        void displayTicks() {
            int &ref = framesThisSecond;
            ref += 1;
            if (this->secondClock->getElapsedTime().asSeconds() >= 1.0) {
                std::string tickString = std::to_string(ref) + " ticks";
                this->tick->setString(tickString);
                ref= 0;
                this->secondClock->restart();
            }
            window->draw(*tick);
        }
        void update()
        {
            this->clearWindow();
            auto startTime = std::chrono::high_resolution_clock::now();
            std::vector<int> inputs = {0, 0, 0, 0, 0};
            while (window->pollEvent(*this->event))
            {
                if (this->event->type == sf::Event::Closed)
                    window->close();
                if (this->event->type == sf::Event::KeyPressed) {
                    keyStates[this->event->key.code] = 1;
                } else {
                    keyStates[this->event->key.code] = 0;
                }
                inputs[4] = keyStates[sf::Keyboard::Space];
            }
            inputs[0] = keyStates[sf::Keyboard::Z];
            inputs[1] = keyStates[sf::Keyboard::Q];
            inputs[2] = keyStates[sf::Keyboard::S];
            inputs[3] = keyStates[sf::Keyboard::D];
            for (const auto& system : systems)
                system->compute(entities, this->window, inputs, sprites, textures);
            displayTicks();
            window->display();
        }
};

