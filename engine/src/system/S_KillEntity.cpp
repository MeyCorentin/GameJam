#include "system/S_KillEntity.hpp"

std::vector<std::shared_ptr<Entity>> S_KillEntity::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        filtered_entities.push_back(entity);
    }
    return filtered_entities;
}

void S_KillEntity::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
        std::shared_ptr<sf::Event> event_) {
    std::pair<double, double> position_comp;
    std::vector<std::shared_ptr<Entity>> temp_entities;

    for (std::shared_ptr<Entity>& entity : arg_entities) {
        position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>()->getValue();
        if (position_comp.first > arg_window.get()->getSize().x * 1.5  ||
            position_comp.first < -((int)arg_window.get()->getSize().x  * 1.5) ||
            position_comp.second > arg_window.get()->getSize().y * 1.5 ||
            position_comp.second < -((int)arg_window.get()->getSize().y * 1.5))
        {
            entity->is_dead_ = true;
        }
    }
}
