#include "system/S_Hit.hpp"

std::vector<std::shared_ptr<IEntity>> S_Hit::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Life<int>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Hit::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    int current_shield;
    int current_life;
    std::shared_ptr<C_Shield<int>> shield_comp;
    std::shared_ptr<C_Life<int>> life_comp;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        shield_comp = entity->template GetComponent<C_Shield<int>>();
        if (shield_comp && shield_comp->getValue() > 0) {
            current_shield = shield_comp->getValue();
            shield_comp->setValue(current_shield - 1);
        } else {
            life_comp = entity->template GetComponent<C_Life<int>>();
            current_life = life_comp->getValue();
            life_comp->setValue(current_life - 1);
        }
    }
}