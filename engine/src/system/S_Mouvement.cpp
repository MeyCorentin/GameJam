#include "system/S_Mouvement.hpp"

std::vector<std::shared_ptr<IEntity>> S_Mouvement::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
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
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::shared_ptr<C_Direction<std::pair<double, double>>> direction;
    std::shared_ptr<C_Position<std::pair<double, double>>> position;
    std::shared_ptr<C_Speed<double>> speed;
    std::shared_ptr<C_EntityMovementClock<sf::Clock>> entities_clock;
    std::shared_ptr<C_IsAutoMove<bool>> is_auto_move;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        entities_clock = entity->template GetComponent<C_EntityMovementClock<sf::Clock>>();
        sf::Time elapsed = entities_clock->getValue().getElapsedTime();
        direction = entity->template GetComponent<C_Direction<std::pair<double, double>>>();
        position = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        speed = entity->template GetComponent<C_Speed<double>>();
        is_auto_move = entity->template GetComponent<C_IsAutoMove<bool>>();

        if (is_auto_move)
            if (!is_auto_move->getValue())
                continue;

        position->setValue(std::make_pair(  position->getValue().first  + (speed->getValue()) * direction->getValue().first,
                                            position->getValue().second + (speed->getValue()) * direction->getValue().second));
        entities_clock->getValue().restart();
    }
}
