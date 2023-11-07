#include "system/S_Mana.hpp"


std::vector<std::shared_ptr<IEntity>> S_Mana::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Mana<int>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Mana::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    int current_mana;
    std::shared_ptr<C_Mana<int>> mana_comp;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        mana_comp = entity->template GetComponent<C_Mana<int>>();
        current_mana = mana_comp->getValue();
        mana_comp->setValue(current_mana + 1);
    }
}