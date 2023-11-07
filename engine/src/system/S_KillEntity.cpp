#include "system/S_KillEntity.hpp"

std::vector<std::shared_ptr<IEntity>> S_KillEntity::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        filtered_entities.push_back(entity);
    }
    return filtered_entities;
}

void S_KillEntity::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::pair<double, double> position_comp;
    std::vector<std::shared_ptr<IEntity>> temp_entities;

    for (std::shared_ptr<IEntity>& entity : arg_entities) {
        position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>()->getValue();
        if (position_comp.first > arg_scene->window_.get()->getSize().x * 1.5  ||
            position_comp.first < -((int)arg_scene->window_.get()->getSize().x  * 1.5) ||
            position_comp.second > arg_scene->window_.get()->getSize().y * 1.5 ||
            position_comp.second < -((int)arg_scene->window_.get()->getSize().y * 1.5))
        {
            entity->is_dead_ = true;
        }
    }
}
