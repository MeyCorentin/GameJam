#include "system/S_Position.hpp"

std::vector<std::shared_ptr<IEntity>> S_Position::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Position<std::pair<double, double>>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Position::Execute(
        int arg_is_server,
        Scene * arg_scene)  {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::pair<double, double> position_comp;

    for (std::shared_ptr<IEntity>& entity : arg_entities) {
        position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>()->getValue();
    }
}