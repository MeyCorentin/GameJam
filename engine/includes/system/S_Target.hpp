#pragma once

#include "System.hpp"
#include "../components/C_Target.hpp"
#include "../components/C_Follow.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Shoot.hpp"
#include "../components/C_FireRate.hpp"
#include "../components/C_FireRateSpeed.hpp"
#include "../components/C_Range.hpp"
#include "S_Input.hpp"

class S_Target : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->HasComponent(typeid(C_Target<int>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void Execute(
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int>arg_input,
                std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) override {
            int current_mana;
            std::shared_ptr<C_Target<int>> target;
            std::shared_ptr<C_Follow<bool>> follow;
            std::shared_ptr<C_Shoot<bool>> shoot;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_1;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_2;
            std::shared_ptr<C_Direction<std::pair<double, double>>> direction_new;
            std::shared_ptr<C_FireRate<std::shared_ptr<sf::Clock>>>  fire_rate;
            std::shared_ptr<C_FireRateSpeed<double>>  fire_rate_speed;
            std::shared_ptr<C_Range<int>>  range;
            std::shared_ptr<Entity> new_entity;
            std::vector<std::shared_ptr<Entity>> temp_entities;
            std::string filepath = "../../rtype/scene_test.json";
            std::ifstream file(filepath);
            std::pair<double, double> direction;
            double length;
            json data;
            file >> data;
            file.close();
            S_Input input;

            for (const std::shared_ptr<Entity>& entity1 : arg_entities) {
                for (const std::shared_ptr<Entity>& entity2 : arg_all_Entities) {
                    target = entity1->template GetComponent<C_Target<int>>();
                    follow = entity1->template GetComponent<C_Follow<bool>>();
                    shoot = entity1->template GetComponent<C_Shoot<bool>>();
                    position_comp_1 = entity1->template GetComponent<C_Position<std::pair<double, double>>>();
                    position_comp_2 = entity2->template GetComponent<C_Position<std::pair<double, double>>>();
                    fire_rate = entity1->template GetComponent<C_FireRate<std::shared_ptr<sf::Clock>>>();
                    fire_rate_speed =  entity1->template GetComponent<C_FireRateSpeed<double>>();
                    range =  entity1->template GetComponent<C_Range<int>>();

                    if (entity1 == entity2)
                        continue;
                    if (follow &&
                        position_comp_1 &&
                        position_comp_2 &&
                        target->getValue() == entity2->GetId())
                    {
                        position_comp_1->getValue().first = position_comp_2->getValue().first;
                        position_comp_1->getValue().second = position_comp_2->getValue().second;
                    }
                    if (shoot &&
                        position_comp_1 &&
                        position_comp_2 &&
                        target->getValue() == entity2->GetId() &&
                        fire_rate &&
                        fire_rate_speed)
                    {
                        if (fire_rate->getValue()->getElapsedTime().asSeconds() < fire_rate_speed->getValue())
                            continue;
                        for (const auto& entity_config : data["entities"]) {
                            if (entity_config["id"] == 3) {
                                direction.first = position_comp_2->getValue().first - position_comp_1->getValue().first;
                                direction.second = position_comp_2->getValue().second - position_comp_1->getValue().second;
                                length = std::sqrt(direction.first * direction.first + direction.second * direction.second);
                                if (length > range->getValue())
                                    continue;
                                std::cout << length  << " : " << range->getValue() << std::endl;
                                new_entity = input.CreateEntityFromConfig(entity_config, data["components"], arg_sprites, arg_textures);
                                direction_new = new_entity->template GetComponent<C_Direction<std::pair<double, double>>>();
                                position_new = new_entity->template GetComponent<C_Position<std::pair<double, double>>>();
                                position_new->setValue(std::make_pair(position_comp_1->getValue().first, position_comp_1->getValue().second));
                                direction_new->setValue(std::make_pair(direction.first /= length, direction.second /= length));
                                temp_entities.push_back(new_entity);
                                fire_rate->getValue()->restart();
                            }
                        }
                    }
                }
            }
            for (const std::shared_ptr<Entity>& temp_entity : temp_entities) {
                arg_all_Entities.push_back(temp_entity);
            }
        }
};