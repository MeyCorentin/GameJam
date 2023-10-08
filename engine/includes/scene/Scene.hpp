#pragma once

#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include <list>
#include "../system/System.hpp"

class Scene {
    private:
        std::shared_ptr<sf::RenderWindow> window_;
        std::shared_ptr<sf::Event> event_;
        std::vector<std::shared_ptr<Entity>> entities_;
        std::vector<std::shared_ptr<System>> systems_;
        std::vector<std::shared_ptr<sf::Sprite>> sprites_;
        std::vector<std::shared_ptr<sf::Texture>> textures_;
        int frames_this_second_;
        int total_ticks_;
        std::unordered_map<sf::Keyboard::Key, bool> key_states_;
        std::shared_ptr<sf::Clock> second_clock_;
        std::shared_ptr<sf::Text> tick_;
        std::shared_ptr<sf::Text> entities_nbr_;
        std::shared_ptr<sf::Font> font_;
        std::shared_ptr<sf::Text> current_tick_;

    public:
        Scene(){}
        bool running = true;
        double targetFrameTime = (1.0 / 60);
        Scene( std::vector<std::shared_ptr<System>> arg_system_list,
                std::vector<std::shared_ptr<Entity>> arg_entity_list,
                std::vector<std::shared_ptr<sf::Sprite>> arg_sprite_list,
                std::vector<std::shared_ptr<sf::Texture>> arg_texture_list)
            : systems_(arg_system_list), entities_(arg_entity_list), sprites_(arg_sprite_list), textures_(arg_texture_list) {
                window_ = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(1000, 1000), "R-Type"));
                frames_this_second_ = 0;
                total_ticks_ = 0;
                event_ = std::shared_ptr<sf::Event>(new sf::Event());
                second_clock_ = std::shared_ptr<sf::Clock>(new sf::Clock());
                entities_nbr_ = std::shared_ptr<sf::Text>(new sf::Text());
                font_ = std::shared_ptr<sf::Font>(new sf::Font());
                font_->loadFromFile("../../rtype/sources/fonts/arial.ttf");
                tick_ = std::shared_ptr<sf::Text>(new sf::Text());
                tick_->setPosition(0, 0);
                tick_->setFillColor(sf::Color::White);
                tick_->setCharacterSize(14),
                tick_->setFont(*font_);

                entities_nbr_->setPosition(0, 20);
                entities_nbr_->setFillColor(sf::Color::White);
                entities_nbr_->setCharacterSize(14),
                entities_nbr_->setFont(*font_);


                current_tick_ = std::shared_ptr<sf::Text>(new sf::Text());
                current_tick_->setPosition(0, 40);
                current_tick_->setFillColor(sf::Color::White);
                current_tick_->setCharacterSize(14),
                current_tick_->setFont(*font_);

                for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
                    key_states_[static_cast<sf::Keyboard::Key>(i)] = false;
                }
            }


        void ClearWindow()
        {
            window_->clear();
        }

        std::vector<std::shared_ptr<Entity>> GetEntities()
        {
            return  entities_;
        }

        std::vector<std::shared_ptr<System>> GetSystems()
        {
            return systems_;
        }

        void DisplayCurrentTick() {
            int &ref = total_ticks_;
            std::string tick_string;

            ref += 1;
            tick_string = std::to_string(ref) + " (ticks)";
            current_tick_->setString(tick_string);
            window_->draw(*current_tick_);
        }

        void DisplayEntities(int nbr) {
            std::string nbr_string = std::to_string(nbr) + " (enttities)";

            this->entities_nbr_->setString(nbr_string);
            window_->draw(*entities_nbr_);
        }

        void DisplayTicks() {
            int &ref = frames_this_second_;
            std::string tick_string;

            ref += 1;
            if (second_clock_->getElapsedTime().asSeconds() >= 1.0) {
                tick_string = std::to_string(ref) + " (t/s)";
                tick_->setString(tick_string);
                ref= 0;
                second_clock_->restart();
            }
            window_->draw(*tick_);
        }

        void Update()
        {
            this->ClearWindow();
            std::vector<int> inputs = {0, 0, 0, 0, 0};

            while (window_->pollEvent(*event_))
            {
                if (event_->type == sf::Event::Closed)
                    window_->close();
                if (event_->type == sf::Event::KeyPressed)
                    key_states_[event_->key.code] = true;
                if (event_->type == sf::Event::KeyReleased)
                    key_states_[event_->key.code] = false;
            }
            inputs[0] = key_states_[sf::Keyboard::Z];
            inputs[1] = key_states_[sf::Keyboard::Q];
            inputs[2] = key_states_[sf::Keyboard::S];
            inputs[3] = key_states_[sf::Keyboard::D];
            inputs[4] = key_states_[sf::Keyboard::Space];
            for (const auto& system : systems_)
                system->Compute(entities_, window_, inputs, sprites_, textures_);
            DisplayTicks();
            DisplayEntities(entities_.size());
            DisplayCurrentTick();
            auto it = entities_.begin();
            while (it != entities_.end())
                ((*it)->is_dead_) ? it = entities_.erase(it) : ++it;
            window_->display();
        }
};

