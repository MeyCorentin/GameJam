#pragma once

#include "System.hpp"
#include "../components/C_Direction.hpp"
#include "../components/C_Speed.hpp"
#include "../components/C_Position.hpp"

class S_Mouvement : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->HasComponent(typeid(C_Direction<std::pair<double, double>>)) &&
                    entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
                    entity->HasComponent(typeid(C_Speed<double>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::shared_ptr<sf::Event> event_) override {
            std::shared_ptr<C_Direction<std::pair<double, double>>> direction;
            std::shared_ptr<C_Position<std::pair<double, double>>> position;
            std::shared_ptr<C_Speed<double>> speed;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                direction = entity->template GetComponent<C_Direction<std::pair<double, double>>>();
                position = entity->template GetComponent<C_Position<std::pair<double, double>>>();
                speed = entity->template GetComponent<C_Speed<double>>();
                position->setValue(std::make_pair(  position->getValue().first + speed->getValue() * direction->getValue().first,
                                                    position->getValue().second+ speed->getValue() * direction->getValue().second));
            }
        }
};
