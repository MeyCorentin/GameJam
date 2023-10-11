#pragma once

#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include <list>
#include "../system/System.hpp"
#include "../components/C_SinClock.hpp"
#include "../components/C_Clock.hpp"

class Scene {
    private:
        std::shared_ptr<sf::RenderWindow> window_;
        std::shared_ptr<sf::Event> event_;
        std::vector<std::shared_ptr<Entity>> list_entities_;
        std::vector<std::shared_ptr<Entity>> entities_;
        std::vector<std::shared_ptr<System>> systems_;
        std::vector<sf::Sprite> sprites_;
        std::vector<std::shared_ptr<sf::Texture>> textures_;
        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> spawn_index_;
        int frames_this_second_;
        int total_ticks_;
        std::unordered_map<sf::Keyboard::Key, int> key_states_;
        std::shared_ptr<sf::Clock> second_clock_;
        std::shared_ptr<sf::Text> tick_;
        std::shared_ptr<sf::Text> entities_nbr_;
        std::shared_ptr<sf::Font> font_;
        std::shared_ptr<sf::Text> current_tick_;

        int time_pressed_;
        bool is_pressed_ = false;
        std::vector<int> inputs_ = {0, 0, 0, 0, 0};

    public:
        Scene(){}
        bool running = true;
        double targetFrameTime = (1.0 / 60);
        Scene( std::vector<std::shared_ptr<System>> arg_system_list,
                std::vector<std::shared_ptr<Entity>> arg_entity_list,
                std::vector<sf::Sprite> arg_sprite_list,
                std::vector<std::shared_ptr<sf::Texture>> arg_texture_list,
                std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> arg_spawn_index)
            : systems_(arg_system_list), list_entities_(arg_entity_list), sprites_(arg_sprite_list), textures_(arg_texture_list), spawn_index_(arg_spawn_index)  {
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


        void AddNewPlayer(int arg_id)
        {
            for (const auto& entity : list_entities_) {
                if (entity->GetId() == 1)
                {
                    std::shared_ptr<C_Player<int>> index;
                    std::cout << "Add entity" << std::endl;
                    entities_.push_back(std::make_shared<Entity>(*entity));
                    for (const std::shared_ptr<Entity>& entity : entities_) {
                        index = entity->template GetComponent<C_Player<int>>();
                        if (!index)
                            continue;
                        if (index->getValue() != 0)
                            continue;
                        index->setValue(arg_id);
                        std::cout << index->getValue() << std::endl;
                    }
                }
            }
        }


    void InputFromPlayer(std::pair<int,int> arg_message)
    {
        std::cout << "----- Input from player" << std::endl;
        std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
        for (const auto& entity : list_entities_) {
            if (entity->GetId() == 1)
            {
                std::shared_ptr<C_Player<int>> index;
                for (const std::shared_ptr<Entity>& entity : entities_) {
                    index = entity->template GetComponent<C_Player<int>>();
                    if (!index)
                        continue;
                    if (index->getValue() != arg_message.first)
                        continue;
                    position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
                    if (!position_comp)
                        continue;
                    switch (arg_message.second) {
                        case 200: // Up
                            position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second - 5));
                            break;
                        case 210: // Left
                            position_comp->setValue(std::make_pair(position_comp->getValue().first - 5, position_comp->getValue().second));
                            break;
                        case 220: // Down
                            position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second + 5));
                            break;
                        case 230: // Right
                            position_comp->setValue(std::make_pair(position_comp->getValue().first + 5, position_comp->getValue().second));
                            break;
                        case 300: // Shoot
                            break;
                        default:
                            std::cerr << "Unknown message data: " << arg_message.second << std::endl;
                            break;
                    }
                    std::cout << "MOVE" << std::endl;
                }
            }
        }
    }

    void Update(int arg_is_server)
    {
        this->ClearWindow();

        for (const auto& system : systems_)
            system->Compute(arg_is_server, entities_, window_, inputs_, sprites_, textures_, event_);

        for (const auto& spawn_info : spawn_index_)
        {
            if (spawn_info.first != total_ticks_)
                continue;

            for (const auto& entity_info : spawn_info.second)
            {
                int entity_id = entity_info.first;
                int x = entity_info.second.first;
                int y = entity_info.second.second;

                for (const auto& entity : list_entities_)
                {
                    if (entity_id != entity->GetId())
                        continue;
                    if (entity->GetId() == arg_is_server)
                        continue;
                    std::shared_ptr<C_Position<std::pair<double,double>>> position;
                    std::shared_ptr<C_SinClock<sf::Clock>> sin_clock;
                    std::shared_ptr<C_Clock<sf::Clock>> clock_basic;
                    entities_.push_back(std::make_shared<Entity>(*entity));
                    position = entities_.back()->template GetComponent<C_Position<std::pair<double,double>>>();
                    position->setValue(std::make_pair(x,y));

                    sin_clock = entities_.back()->template GetComponent<C_SinClock<sf::Clock>>();
                    if (sin_clock)
                        sin_clock->getValue().restart();
                    
                    clock_basic = entities_.back()->template GetComponent<C_Clock<sf::Clock>>();
                    if (clock_basic)
                        clock_basic->getValue().restart();
                }
            }
        }
        DisplayTicks();
        DisplayEntities(entities_.size());
        DisplayCurrentTick();
        auto it = entities_.begin();
        while (it != entities_.end())
            ((*it)->is_dead_) ? it = entities_.erase(it) : ++it;
        window_->display();
    }
};
