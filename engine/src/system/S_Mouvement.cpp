#include "system/S_Mouvement.hpp"

std::vector<std::shared_ptr<Entity>> S_Mouvement::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Direction<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Speed<double>)) &&
            entity->HasComponent(typeid(C_EntityMovementClock<sf::Clock>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Mouvement::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
        std::shared_ptr<sf::Event> event_) {
    std::shared_ptr<C_Direction<std::pair<double, double>>> direction;
    std::shared_ptr<C_Position<std::pair<double, double>>> position;
    std::shared_ptr<C_Speed<double>> speed;
    std::shared_ptr<C_EntityMovementClock<sf::Clock>> entities_clock;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        entities_clock = entity->template GetComponent<C_EntityMovementClock<sf::Clock>>();
        sf::Time elapsed = entities_clock->getValue().getElapsedTime();
        direction = entity->template GetComponent<C_Direction<std::pair<double, double>>>();
        position = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        speed = entity->template GetComponent<C_Speed<double>>();
        position->setValue(std::make_pair(  position->getValue().first  + (speed->getValue() * ((elapsed.asMilliseconds() / 20))) * direction->getValue().first,
                                            position->getValue().second + (speed->getValue() * ((elapsed.asMilliseconds() / 20))) * direction->getValue().second));
        entities_clock->getValue().restart();
    }
}   
