#pragma once

#include "System.hpp"
#include "../components/C_Direction.hpp"
#include "../components/C_Speed.hpp"
#include "../components/C_Position.hpp"

class S_Mouvement : public System {
    public:
        std::vector<std::shared_ptr<Entity>> filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->hasComponent(typeid(C_Direction<std::pair<double, double>>)) &&
                    entity->hasComponent(typeid(C_Position<std::pair<double, double>>)) &&
                    entity->hasComponent(typeid(C_Speed<double>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void execute(
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) override {
            std::shared_ptr<C_Direction<std::pair<double, double>>> direction;
            std::shared_ptr<C_Position<std::pair<double, double>>> position;
            std::shared_ptr<C_Speed<double>> speed;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                direction = entity->template getComponent<C_Direction<std::pair<double, double>>>();
                position = entity->template getComponent<C_Position<std::pair<double, double>>>();
                speed = entity->template getComponent<C_Speed<double>>();
                position->setValue(std::make_pair(  position->getValue().first + speed->getValue() * direction->getValue().first,
                                                    position->getValue().second+ speed->getValue() * direction->getValue().second));
            }
        }
};
