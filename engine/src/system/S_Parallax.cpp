#include "system/S_Parallax.hpp"

std::vector<std::shared_ptr<IEntity>> S_Parallax::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Parallax<int>)) &&
            entity->HasComponent(typeid(C_ParallaxClock<sf::Clock>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Parallax::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::shared_ptr<C_Position<std::pair<double, double>>> position;
    std::shared_ptr<C_PositionStart<std::pair<double, double>>> position_start;
    std::shared_ptr<C_PositionEnd<std::pair<double, double>>> position_end;
    std::shared_ptr<C_Parallax<int>> parallax;
    std::shared_ptr<C_ParallaxClock<sf::Clock>> parallax_clock;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        position = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        parallax = entity->template GetComponent<C_Parallax<int>>();
        parallax_clock = entity->template GetComponent<C_ParallaxClock<sf::Clock>>();
        sf::Time elapsed1 = parallax_clock->getValue().getElapsedTime();
        // position->setValue(std::make_pair(  position->getValue().first + ((parallax->getValue() * elapsed1.asMilliseconds() / 10)),
        position->setValue(std::make_pair(  position->getValue().first + ((parallax->getValue())), //TODO Replace that
                                            position->getValue().second));
        parallax_clock->getValue().restart();
        position_start = entity->template GetComponent<C_PositionStart<std::pair<double, double>>>();
        position_end = entity->template GetComponent<C_PositionEnd<std::pair<double, double>>>();
        if (position_start && position_end)
        {
            if (position->getValue().first < position_end->getValue().first)
                position->setValue(std::make_pair(position_start->getValue().first, position->getValue().second));
            if (position->getValue().second < position_end->getValue().second)
                position->setValue(std::make_pair( position_start->getValue().first, position->getValue().second));
        }
    }
}
