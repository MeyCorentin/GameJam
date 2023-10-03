#include "TSystem.hpp"
#include "../components/Position.hpp"
#include "../components/Player.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../parser/jsonParser.hpp"
#include "../scene/SystemRegister.hpp"
#include "../scene/ComponentRegister.hpp"
#include "../scene/SceneBuilder.hpp"

/**
 * @brief A system for processing player input and updating entity positions.
 *
 * This system filters entities that have both Player and Position components, and it updates
 * the position of those entities based on the provided input.
 */
class InputSystem : public TSystem {
public:
    /**
     * @brief Filters entities with Player and Position components.
     *
     * @param _entities The list of entities to filter.
     * @return Filtered entities with Player and Position components.
     */
    std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) override {
        std::vector<std::shared_ptr<TEntity>> filteredEntities;
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            if (entity->hasComponent(typeid(Player<bool>)) && entity->hasComponent(typeid(Position<std::pair<double, double>>))) {
                filteredEntities.push_back(entity);
            }
        }
        return filteredEntities;
    }

    const json& FindComponentConfigById(const json& _componentsConfig, int _id) {
        int componentId;
        static const json empty_json;

        for (const auto& componentConfig : _componentsConfig)
            if (componentConfig["id"] == _id)
                return componentConfig;
        return empty_json;
    }

    bool processComponent(const json& _entityComponent, const json& _componentConfig, JsonParser& _parser, EntityBuilder& _entityBuilder, std::vector<std::shared_ptr<sf::Sprite>>& sprites, std::vector<std::shared_ptr<sf::Texture>>& textures)
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
            sprites.push_back(allPtr.second);
            textures.push_back(allPtr.first);
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
        } else {
            std::cerr << "Unsupported component type: " << value_type << std::endl;
            return false;
        }
        return true;
    }

    std::shared_ptr<TEntity> createEntityFromConfig(const json& _entityConfig, const json& _componentsConfig, std::vector<std::shared_ptr<sf::Sprite>>& sprites, std::vector<std::shared_ptr<sf::Texture>>& textures)
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
                return entityBuilder.build();
            if (!processComponent(entityComponent, componentConfig, parser, entityBuilder, sprites, textures))
                return entityBuilder.build();
        }
        return entityBuilder.build();
    }

    void createEntity(std::vector<std::shared_ptr<TEntity>>& allEntities, std::vector<std::shared_ptr<sf::Sprite>>& sprites, std::vector<std::shared_ptr<sf::Texture>>& textures, int id, std::shared_ptr<Position<std::pair<double, double>>> positionComp) {
        std::string filepath = "../scene_test.json";
        std::ifstream file(filepath);
        json data;
        file >> data;
        file.close();
        for (const auto& entityConfig : data["entities"]) {
            if (entityConfig["id"] == id) {
                std::shared_ptr<TEntity> newEntity = createEntityFromConfig(entityConfig, data["components"], sprites, textures);
                std::shared_ptr<Position<std::pair<double, double>>> positionNew = newEntity->template getComponent<Position<std::pair<double, double>>>();
                positionNew->setValue(std::make_pair(positionComp->getValue().first, positionComp->getValue().second));
                allEntities.push_back(newEntity);
                std::cout << "New entity created" << std::endl;
            }
        }
    }

    /**
     * @brief Updates the positions of entities based on player input.
     *
     * This method iterates through the filtered entities and adjusts their positions
     * based on the input provided in the _inputs vector.
     *
     * @param _entities Vector of entities to update.
     * @param _window SFML window (not used in this function).
     * @param _inputs Vector of integers representing player input.
     */
    void execute(std::vector<std::shared_ptr<TEntity>>& _entities, sf::RenderWindow &_window, std::vector<int> _inputs, std::vector<std::shared_ptr<TEntity>>& allEntities, std::vector<std::shared_ptr<sf::Sprite>>& sprites, std::vector<std::shared_ptr<sf::Texture>>& textures) override {
        for (const std::shared_ptr<TEntity>& entity : _entities) {
            std::shared_ptr<Position<std::pair<double, double>>> positionComp = entity->template getComponent<Position<std::pair<double, double>>>();
            if (_inputs[0] == 1)
                positionComp->setValue(std::make_pair(positionComp->getValue().first, positionComp->getValue().second - 5));
            if (_inputs[1] == 1)
                positionComp->setValue(std::make_pair(positionComp->getValue().first - 5, positionComp->getValue().second));
            if (_inputs[2] == 1)
                positionComp->setValue(std::make_pair(positionComp->getValue().first, positionComp->getValue().second  + 5));
            if (_inputs[3] == 1)
                positionComp->setValue(std::make_pair(positionComp->getValue().first + 5, positionComp->getValue().second));
            if (_inputs[4] == 1)
                createEntity(allEntities, sprites, textures, 3, positionComp); //Change that (because is exec many times)
        }
    }
};