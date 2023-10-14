#pragma once

#include "System.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_ChargedShoot.hpp"
#include "../components/C_ShootCharging.hpp"
#include "../components/C_AnimatedMove.hpp"
#include "../components/C_IsMoving.hpp"
#include "../components/C_Size.hpp"
#include "../components/C_Admin.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../parser/jsonParser.hpp"
#include "../scene/SystemRegister.hpp"
#include "../scene/ComponentRegister.hpp"
#include "../scene/SceneBuilder.hpp"

class S_Input : public System {
    private:
        std::vector<int> inputs_ = {0, 0, 0, 0, 0};
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->HasComponent(typeid(C_Player<int>)) &&
                    entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
                    entity->HasComponent(typeid(C_AnimatedMove<sf::Clock>)) &&
                    entity->HasComponent(typeid(C_IsMoving<bool>)) &&
                    entity->HasComponent(typeid(C_Admin<bool>)) &&
                    entity->HasComponent(typeid(C_ChargedShoot<sf::Clock>))
                    ) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        json FindComponentConfigById(const json& arg_components_config, int arg_id) {
            static json empty_json;

            for (auto component_config : arg_components_config)
                if (component_config["id"] == arg_id)
                    return component_config;
            return empty_json;
        }

        bool ProcessComponent(
                const json& arg_entityComponent,
                const json& arg_componentConfig,
                JsonParser& arg_parser,
                EntityBuilder& arg_entityBuilder,
                std::vector<sf::Sprite>& sprites,
                std::vector<std::shared_ptr<sf::Texture>>& textures) {
            std::string component_name = arg_componentConfig["type"];
            std::string value_type = arg_componentConfig["value_type"];
            json component_value = arg_entityComponent["value"];
            std::shared_ptr<ComponentBase> component = ComponentRegistry::Instance().CreateComponent(component_name);
            Variant value = arg_parser.ParseValue(value_type, component_value);

            if (!component)
                return false;

            std::cout << " - " << component_name << std::endl;
            if (value_type == "Sprite") {
                auto all_ptr = std::get<std::pair<std::shared_ptr<sf::Texture>, sf::Sprite>>(value);
                sprites.push_back(all_ptr.second);
                textures.push_back(all_ptr.first);
                arg_entityBuilder.AddComponent(component,  all_ptr.second);
            } else if (value_type == "Int") {
                arg_entityBuilder.AddComponent(component, std::get<int>(value));
            } else if (value_type == "PairDouble") {
                arg_entityBuilder.AddComponent(component, std::get<std::pair<double, double>>(value));
            } else if (value_type == "PairInt") {
                arg_entityBuilder.AddComponent(component, std::get<std::pair<int, int>>(value));
            } else if (value_type == "Bool") {
                arg_entityBuilder.AddComponent(component, std::get<bool>(value));
            } else if (value_type == "Double") {
                arg_entityBuilder.AddComponent(component, std::get<double>(value));
            } else if (value_type == "Clock") {
                arg_entityBuilder.AddComponent(component, std::get<sf::Clock>(value));
            } else if (value_type == "IntRect") {
                arg_entityBuilder.AddComponent(component, std::get<sf::IntRect>(value));
            } else if (value_type == "PairPairInt") {
                arg_entityBuilder.AddComponent(component, std::get<std::pair<std::pair<int, int>, std::pair<int, int>>>(value));
            } else if (value_type == "SinFunc") {
                arg_entityBuilder.AddComponent(component, std::get<SinusoidalFunction>(value));
            }else {
                std::cerr << "Unsupported component type: " << value_type << std::endl;
                return false;
            }
            return true;
        }

        std::shared_ptr<Entity> CreateEntityFromConfig(
                const json& arg_entity_config,
                const json& arg_components_config,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) {
            JsonParser parser;
            json component_config;
            int component_id;
            int entity_id = arg_entity_config["id"];
            EntityBuilder entity_builder(entity_id);
            const json& entity_components = arg_entity_config["components"];

            std::cout << "Create Entity: " << entity_id << std::endl;
            for (const auto& entity_component : entity_components) {
                component_id = entity_component["component_id"];
                component_config = FindComponentConfigById(arg_components_config, component_id);
                if (component_config.is_null())
                    return entity_builder.Build();
                if (!ProcessComponent(entity_component, component_config, parser, entity_builder, arg_sprites, arg_textures))
                    return entity_builder.Build();
            }
            return entity_builder.Build();
        }

        void createEntity(
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                int id,
                std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp) {
            std::shared_ptr<Entity> new_entity;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
            std::string filepath = "../../rtype/scene_test.json";
            std::ifstream file(filepath);
            json data;

            file >> data;
            file.close();
            for (const auto& entity_config : data["entities"]) {
                if (entity_config["id"] == id) {
                    new_entity = CreateEntityFromConfig(entity_config, data["components"], arg_sprites, arg_textures);
                    position_new = new_entity->template GetComponent<C_Position<std::pair<double, double>>>();
                    std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
                    std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
                    sprite->getValue().setTextureRect(rect->getValue());
                    position_new->setValue(std::make_pair(arg_position_comp->getValue().first, arg_position_comp->getValue().second));
                    arg_all_entities.push_back(new_entity);
                }
            }
        }

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::shared_ptr<sf::Event> event_) override { //TODO rename event_
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
            std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size;
            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (arg_is_server == 1)
                    continue;
                position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
                hitbox_size = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();
                std::shared_ptr<C_ChargedShoot<sf::Clock>> clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();
                std::shared_ptr<C_ShootCharging<bool>> is_charging = entity->template GetComponent<C_ShootCharging<bool>>();
                std::shared_ptr<C_AnimatedMove<sf::Clock>> clock_move = entity->template GetComponent<C_AnimatedMove<sf::Clock>>();
                std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
                std::shared_ptr<C_Sprite<sf::Sprite>> sprite = entity->template GetComponent<C_Sprite<sf::Sprite>>();
                std::shared_ptr<C_IsMoving<bool>> moving = entity->template GetComponent<C_IsMoving<bool>>();
                std::shared_ptr<C_Life<int>> life = entity->template GetComponent<C_Life<int>>();
                std::shared_ptr<C_Admin<bool>> is_admin = entity->template GetComponent<C_Admin<bool>>();
                std::shared_ptr<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>> size = entity->template GetComponent<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>();
                while (arg_window->pollEvent(*event_)) {
                    if (event_->type == sf::Event::Closed)
                        arg_window->close();
                    if (event_->type == sf::Event::KeyPressed) {
                        if (event_->key.code == sf::Keyboard::Up) {
                            inputs_[0] = 1;
                            if (moving->getValue() == false) {
                                moving->getValue() = true;
                                clock_move->getValue().restart();
                            }
                            rect->getValue().left = size->getValue().second.first + (rect->getValue().width * 2);
                            sprite->getValue().setTextureRect(rect->getValue());
                        }
                        if (event_->key.code == sf::Keyboard::Left)
                            inputs_[1] = 1;
                        if (event_->key.code == sf::Keyboard::Down) {
                            inputs_[2] = 1;
                            if (moving->getValue() == false) {
                                moving->getValue() = true;
                                clock_move->getValue().restart();
                            }
                            rect->getValue().left = size->getValue().second.first - (rect->getValue().width * 2);
                            sprite->getValue().setTextureRect(rect->getValue());
                        }
                        if (event_->key.code == sf::Keyboard::Right)
                            inputs_[3] = 1;
                        if (event_->key.code == sf::Keyboard::Space) {
                            if (is_charging->getValue() == false) {
                                clock->getValue().restart();
                                is_charging->getValue() = true;
                            }
                        }
                    }
                    if (event_->type == sf::Event::KeyReleased) {
                        if (event_->key.code == sf::Keyboard::Up) {
                            inputs_[0] = 0;
                            moving->getValue() = false;
                            rect->getValue().left = size->getValue().second.first;
                            sprite->getValue().setTextureRect(rect->getValue());
                        }
                        if (event_->key.code == sf::Keyboard::Left)
                            inputs_[1] = 0;
                        if (event_->key.code == sf::Keyboard::Down) {
                            inputs_[2] = 0;
                            moving->getValue() = false;
                            rect->getValue().left = size->getValue().second.first;
                            sprite->getValue().setTextureRect(rect->getValue());
                        }
                        if (event_->key.code == sf::Keyboard::Right)
                            inputs_[3] = 0;
                        if (event_->key.code == sf::Keyboard::Space) { // ADD CLOCK TO INPUT
                            std::cout << "Time : " << clock->getValue().getElapsedTime().asSeconds() << std::endl;
                            if (clock->getValue().getElapsedTime().asSeconds() > 1)
                                createEntity(arg_all_entities, arg_sprites, arg_textures, 9, position_comp);
                            else if (clock->getValue().getElapsedTime().asSeconds() > 0.6)
                                createEntity(arg_all_entities, arg_sprites, arg_textures, 8, position_comp);
                            else if (clock->getValue().getElapsedTime().asSeconds() > 0.4)
                                createEntity(arg_all_entities, arg_sprites, arg_textures, 7, position_comp);
                            else if (clock->getValue().getElapsedTime().asSeconds() > 0.2)
                                createEntity(arg_all_entities, arg_sprites, arg_textures, 6, position_comp);
                            else if (clock->getValue().getElapsedTime().asSeconds() > 0.1)
                                createEntity(arg_all_entities, arg_sprites, arg_textures, 5, position_comp);
                            else
                                createEntity(arg_all_entities, arg_sprites, arg_textures, 3, position_comp);
                            is_charging->getValue() = false;
                        }
                        if (event_->key.code == sf::Keyboard::A) {
                            if (is_admin->getValue()) {
                                life->getValue() = 1;
                                is_admin->getValue() = false;
                            } else {
                                life->getValue() = -1;
                                is_admin->getValue() = true;
                            }
                        }
                    }
                }
                if (inputs_[0] == 1)
                {
                    if (position_comp->getValue().second > 5)
                        position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second - 5));
                }
                if (inputs_[1] == 1)
                {
                    if (position_comp->getValue().first > 5)
                        position_comp->setValue(std::make_pair(position_comp->getValue().first - 5, position_comp->getValue().second));
                }
                if (inputs_[2] == 1)
                {
                    if (position_comp->getValue().second < arg_window->getSize().x - 5 - hitbox_size->getValue().second)
                        position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second  + 5));
                }
                if (inputs_[3] == 1)
                {
                    if (position_comp->getValue().first < arg_window->getSize().y - 5 - hitbox_size->getValue().first)
                        position_comp->setValue(std::make_pair(position_comp->getValue().first + 5, position_comp->getValue().second));
                }
            }
        }
};