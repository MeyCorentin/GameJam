#pragma once

#include "System.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Hitbox.hpp"

class S_Collision : public System {
    public:
        std::vector<std::shared_ptr<Entity>> filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->hasComponent(typeid(C_Hitbox<std::pair<int, int>>)) &&
                    entity->hasComponent(typeid(C_Position<std::pair<double, double>>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void drawHitbox(
                std::shared_ptr<sf::RenderWindow> arg_window,
                const std::shared_ptr<C_Position<std::pair<double, double>>>& arg_position_comp,
                const std::shared_ptr<C_Hitbox<std::pair<int, int>>>& arg_hitbox_comp,
                bool arg_is_player) {
            sf::RectangleShape hitbox;

            hitbox.setPosition(arg_position_comp->getValue().first, arg_position_comp->getValue().second);
            hitbox.setSize(sf::Vector2f(arg_hitbox_comp->getValue().first, arg_hitbox_comp->getValue().second));
            hitbox.setFillColor(sf::Color::Transparent);
            hitbox.setOutlineColor(arg_is_player ? sf::Color::Green : sf::Color::Red);
            hitbox.setOutlineThickness(1.0f);
            arg_window->draw(hitbox);
        }

        void execute(
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) override {
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_1;
            std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_comp_1;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_2;
            std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_comp_2;
            std::shared_ptr<C_Player<bool>> is_player;
            float x1;
            float y1;
            float x2;
            float y2;

            for (const std::shared_ptr<Entity>& entity1 : arg_entities) {
                position_comp_1 = entity1->template getComponent<C_Position<std::pair<double, double>>>();
                hitbox_comp_1 = entity1->template getComponent<C_Hitbox<std::pair<int, int>>>();
                is_player = entity1->template getComponent<C_Player<bool>>();

                drawHitbox(arg_window, position_comp_1, hitbox_comp_1, is_player ? is_player->getValue() : false);
                x1 = static_cast<float>(position_comp_1->getValue().first);
                y1 = static_cast<float>(position_comp_1->getValue().second);
                for (const std::shared_ptr<Entity>& entity2 : arg_entities) {
                    if (entity1 == entity2)
                        continue;
                    position_comp_2 = entity2->template getComponent<C_Position<std::pair<double, double>>>();
                    hitbox_comp_2 = entity2->template getComponent<C_Hitbox<std::pair<int, int>>>();
                    x2 = static_cast<float>(position_comp_2->getValue().first);
                    y2 = static_cast<float>(position_comp_2->getValue().second);
                    if (!position_comp_2 || !hitbox_comp_2)
                        continue;
                    if (x1 < x2 + hitbox_comp_2->getValue().first &&
                        x1 + hitbox_comp_1->getValue().first> x2 &&
                        y1 < y2 + hitbox_comp_2->getValue().second &&
                        y1 + hitbox_comp_1->getValue().second > y2) {
                            std::cout << "HIT" << std::endl;
                    }
                }
            }
        }
};
