#pragma once

#include "SceneBuilder.hpp"
#include "../parser/jsonParser.hpp"
#include "SystemRegister.hpp"
#include "ComponentRegister.hpp"

class SceneDirector {
    private:
        SceneBuilder sceneBuilder;
        std::vector<std::shared_ptr<TSystem>> systems;
        std::vector<std::shared_ptr<TEntity>> entities;

        std::shared_ptr<TSystem> createSystemFromConfig(const json& _systemConfig)
        {
            std::string type = _systemConfig["type"];
            std::cout << type << std::endl;
            return SystemRegistry::instance().createSystem(type);
        }

        const json& FindComponentConfigById(const json& _componentsConfig, int _id) {
            int componentId;
            static const json empty_json;

            for (const auto& componentConfig : _componentsConfig)
                if (componentConfig["id"] == _id)
                    return componentConfig;
            return empty_json;
        }


        bool processComponent(const json& _entityComponent, const json& _componentConfig, JsonParser& _parser, EntityBuilder& _entityBuilder)
        {
            std::string componentName = _componentConfig["type"];
            std::string value_type = _componentConfig["value_type"];
            json componentValue = _entityComponent["value"];
            std::shared_ptr<TComponentBase> component = ComponentRegistry::instance().createComponent(componentName);
            Variant value = _parser.parseValue(value_type, componentValue);

            if (!component)
                return false;

            std::cout << " - " << componentName << std::endl;
            if (value_type == "Sprite") {
                auto allPtr = std::get<std::pair<std::shared_ptr<sf::Texture>, std::shared_ptr<sf::Sprite>>>(value);
                sceneBuilder.addSprite( allPtr.second);
                sceneBuilder.addTexture(allPtr.first);
                _entityBuilder.addComponent(component,  allPtr.second);
            } else if (value_type == "Int") {
                _entityBuilder.addComponent(component, std::get<int>(value));
            } else if (value_type == "PairDouble") {
                _entityBuilder.addComponent(component, std::get<std::pair<double, double>>(value));
            } else if (value_type == "PairInt") {
                _entityBuilder.addComponent(component, std::get<std::pair<int, int>>(value));
            } else if (value_type == "Bool") {
                _entityBuilder.addComponent(component, std::get<bool>(value));
            } else if (value_type == "Double") {
                _entityBuilder.addComponent(component, std::get<double>(value));
            } else if (value_type == "Clock") {
                _entityBuilder.addComponent(component, std::get<std::shared_ptr<sf::Clock>>(value));
            } else if (value_type == "IntRect") {
                _entityBuilder.addComponent(component, std::get<std::shared_ptr<sf::IntRect>>(value));
            } else {
                std::cerr << "Unsupported component type: " << value_type << std::endl;
                return false;
            }
            return true;
        }

    public:
        std::shared_ptr<TEntity> createEntityFromConfig(const json& _entityConfig, const json& _componentsConfig)
        {
            JsonParser parser;
            int entityId = _entityConfig["id"];
            EntityBuilder entityBuilder(entityId);
            int componentId;

            std::cout << "Create Entity: " << entityId << std::endl;
            const json& entityComponents = _entityConfig["components"];
            for (const auto& entityComponent : entityComponents) {
                componentId = entityComponent["component_id"];
                const json& componentConfig = FindComponentConfigById(_componentsConfig, componentId);
                if (componentConfig.is_null())
                {
                    std::cout << "NULL" << std::endl;
                    return entityBuilder.build();
                }
                if (!processComponent(entityComponent, componentConfig, parser, entityBuilder))
                    return entityBuilder.build();
            }
            return entityBuilder.build();
        }

        SceneDirector(std::string _file_path) {
            std::ifstream file(_file_path);
            json data;

            file >> data;
            file.close();
            std::cout << "------[LOAD SYSTEMS]-------" << std::endl;
            for (const auto& systemConfig : data["systems"])
                sceneBuilder.addSystem(createSystemFromConfig(systemConfig));
            std::cout << "------[LOAD ENTITIES]-------" << std::endl;
            for (const auto& entityConfig : data["entities"])
                sceneBuilder.addEntity(createEntityFromConfig(entityConfig, data["components"]));
        }

        TScene constructScene() {
            std::cout << "[CONSTRUCTOR] Scene construct" << std::endl;
            return sceneBuilder.build();
        }
};
