#include "System.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Player.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../parser/jsonParser.hpp"
#include "../scene/SystemRegister.hpp"
#include "../scene/ComponentRegister.hpp"
#include "../scene/SceneBuilder.hpp"

class S_Input : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->HasComponent(typeid(C_Player<bool>)) &&
                    entity->HasComponent(typeid(C_Position<std::pair<double, double>>))) {
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
                std::vector<std::shared_ptr<sf::Sprite>>& sprites,
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
                auto all_ptr = std::get<std::pair<std::shared_ptr<sf::Texture>, std::shared_ptr<sf::Sprite>>>(value);
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
            } else {
                std::cerr << "Unsupported component type: " << value_type << std::endl;
                return false;
            }
            return true;
        }

        std::shared_ptr<Entity> CreateEntityFromConfig(
                const json& arg_entity_config,
                const json& arg_components_config,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
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
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
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
            std::cout << "New entity created!" << std::endl;
            for (const auto& entity_config : data["entities"]) {
                if (entity_config["id"] == id) {
                    new_entity = CreateEntityFromConfig(entity_config, data["components"], arg_sprites, arg_textures);
                    position_new = new_entity->template GetComponent<C_Position<std::pair<double, double>>>();
                    position_new->setValue(std::make_pair(arg_position_comp->getValue().first, arg_position_comp->getValue().second));
                    arg_all_entities.push_back(new_entity);
                    std::cout << "New entity created" << std::endl;
                }
            }
        }

        void Execute(
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) override {
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
                if (arg_inputs[0] == 1)
                    position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second - 5));
                if (arg_inputs[1] == 1)
                    position_comp->setValue(std::make_pair(position_comp->getValue().first - 5, position_comp->getValue().second));
                if (arg_inputs[2] == 1)
                    position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second  + 5));
                if (arg_inputs[3] == 1)
                    position_comp->setValue(std::make_pair(position_comp->getValue().first + 5, position_comp->getValue().second));
                if (arg_inputs[4] == 1)
                    createEntity(arg_all_entities, arg_sprites, arg_textures, 3, position_comp); //Change that (because is exec many times)
            }
        }
};