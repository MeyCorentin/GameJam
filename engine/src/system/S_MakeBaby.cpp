#include "system/S_MakeBaby.hpp"

std::vector<std::shared_ptr<IEntity>> S_MakeBaby::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Child<int>)) &&
            entity->HasComponent(typeid(C_Sprite<sf::Sprite>)) &&
            entity->HasComponent(typeid(C_SpriteRect<sf::IntRect>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_MakeBaby::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::shared_ptr<IEntity> new_entity;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
    std::shared_ptr<C_Child<int>> id_child;
    std::ifstream file(arg_scene->filepath_);
    json data;

    file >> data;
    file.close();
    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (!entity->is_dead_ ||!entity->HasComponent(typeid(C_Child<int>)))
            continue;
        id_child = entity->template GetComponent<C_Child<int>>();
        for (const auto& entity_config : data["entities"]) {
            if (entity_config["id"] != id_child->getValue())
                continue;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
            new_entity = arg_scene->CreateEntityFromConfig(entity_config, data["components"]);
            position_new = new_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
            std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
            sprite->getValue().setTextureRect(rect->getValue());
            position_new->setValue(std::make_pair(position_comp->getValue().first - position_new->getValue().first, position_comp->getValue().second - position_new->getValue().second));
            arg_scene->entities_.push_back(new_entity);
            }
        }
}