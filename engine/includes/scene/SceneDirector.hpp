#pragma once

#include "SceneBuilder.hpp"
#include "../parser/jsonParser.hpp"
#include "SystemRegister.hpp"
#include "ComponentRegister.hpp"

class SceneDirector {
    private:
        SceneBuilder scene_builder_;
        std::vector<std::shared_ptr<System>> systems_;
        std::vector<std::shared_ptr<Entity>> entities_;

        std::shared_ptr<System> CreateSystemFromConfig(const json& arg_systemConfig)
        {
            std::string type = arg_systemConfig["type"];

            std::cout << type << std::endl;
            return SystemRegistry::Instance().CreateSystem(type);
        }

        const json& FindComponentConfigById(
                const json& arg_componentsConfig,
                int arg_id) {
            static const json empty_json;

            for (const auto& component_config : arg_componentsConfig)
                if (component_config["id"] == arg_id)
                    return component_config;
            return empty_json;
        }


        bool ProcessComponent(
                const json& arg_entity_component,
                const json& arg_component_config,
                JsonParser& arg_parser,
                EntityBuilder& arg_entity_builder) {
            std::string component_name = arg_component_config["type"];
            std::string value_type = arg_component_config["value_type"];
            json component_value = arg_entity_component["value"];
            std::shared_ptr<ComponentBase> component = ComponentRegistry::Instance().CreateComponent(component_name);
            Variant value = arg_parser.ParseValue(value_type, component_value);

            if (!component)
                return false;
            std::cout << " - " << component_name << std::endl;
            if (value_type == "Sprite") {
                auto all_ptr = std::get<std::pair<std::shared_ptr<sf::Texture>, sf::Sprite>>(value);
                scene_builder_.AddSprite( all_ptr.second);
                scene_builder_.AddTexture(all_ptr.first);
                arg_entity_builder.AddComponent(component,  all_ptr.second);
            } else if (value_type == "Int") {
                arg_entity_builder.AddComponent(component, std::get<int>(value));
            } else if (value_type == "PairDouble") {
                arg_entity_builder.AddComponent(component, std::get<std::pair<double, double>>(value));
            } else if (value_type == "PairInt") {
                arg_entity_builder.AddComponent(component, std::get<std::pair<int, int>>(value));
            } else if (value_type == "Bool") {
                arg_entity_builder.AddComponent(component, std::get<bool>(value));
            } else if (value_type == "Double") {
                arg_entity_builder.AddComponent(component, std::get<double>(value));
            } else if (value_type == "Clock") {
                arg_entity_builder.AddComponent(component, std::get<sf::Clock>(value));
            } else if (value_type == "IntRect") {
                arg_entity_builder.AddComponent(component, std::get<sf::IntRect>(value));
            } else if (value_type == "PairPairInt") {
                arg_entity_builder.AddComponent(component, std::get<std::pair<std::pair<int, int>, std::pair<int, int>>>(value));
            } else {
                std::cerr << "Unsupported component type: " << value_type << std::endl;
                return false;
            }
            return true;
        }

    public:
        std::shared_ptr<Entity> CreateEntityFromConfig(
                const json& arg_entity_config,
                const json& arg_components_config) {
            JsonParser parser;
            int component_id;
            int entity_id = arg_entity_config["id"];
            EntityBuilder entity_builder(entity_id);
            const json& entity_components = arg_entity_config["components"];

            std::cout << "Create Entity: " << entity_id << std::endl;
            for (const auto& entity_component : entity_components) {
                component_id = entity_component["component_id"];
                const json& component_config = FindComponentConfigById(arg_components_config, component_id);
                if (component_config.is_null()) {
                    return entity_builder.Build();
                }
                if (!ProcessComponent(entity_component, component_config, parser, entity_builder)) {
                    return entity_builder.Build();
                }
            }
            return entity_builder.Build();
        }

        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> CreateMap(const json& arg_spawn_config)
        {
            std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> map;
            for (const auto& spawn_entry : arg_spawn_config)
            {
                int tick = spawn_entry.at("tick").get<int>();
                std::vector<std::pair<int, std::pair<int, int>> > entities;

                for (const auto& entity : spawn_entry.at("mob_id"))
                {
                    int id_value = entity.at("entity_id").get<int>();
                    int x = entity.at("position").at("x").get<int>();
                    int y = entity.at("position").at("y").get<int>();

                    entities.push_back(std::make_pair(id_value, std::make_pair(x, y)));
                }

                map.push_back(std::make_pair(tick, entities));
            }
            return map;
        }
        SceneDirector() {}

        SceneDirector(std::string arg_file_path, int value) {
            std::ifstream file(arg_file_path);
            json data;

            file >> data;
            file.close();
            std::cout << "------[LOAD SYSTEMS]-------" << std::endl;
            for (const auto& system_config : data["systems"])
                scene_builder_.AddSystem(CreateSystemFromConfig(system_config));
            std::cout << "------[LOAD ENTITIES]-------" << std::endl;
            for (const auto& entity_config : data["entities"]) {
                std::shared_ptr<Entity> new_entity = CreateEntityFromConfig(entity_config, data["components"]);
                if (new_entity->HasComponent(typeid(C_SpriteRect<sf::IntRect>)) &&
                    new_entity->HasComponent(typeid(C_Sprite<sf::Sprite>))) {
                    std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
                    std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
                    sprite->getValue().setTextureRect(rect->getValue());
                }
                scene_builder_.AddEntity(new_entity);
            }
                
            scene_builder_.AddSpawnIndex(CreateMap(data["spawn"]));
        }

        Scene ConstructScene() {
            std::cout << "[CONSTRUCTOR] Scene construct" << std::endl;
            return scene_builder_.Build();
        }
};
