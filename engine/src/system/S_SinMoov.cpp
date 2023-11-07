#include "system/S_SinMoov.hpp"


std::vector<std::shared_ptr<IEntity>> S_SinMoov::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities)  {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_SinMoov<SinusoidalFunction>)) &&
            entity->HasComponent(typeid(C_SinClock<sf::Clock>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_SinMoov::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::shared_ptr<C_Position<std::pair<double, double>>> position;
    std::shared_ptr<C_Parallax<int>> parallax;
    std::shared_ptr<C_SinMoov<SinusoidalFunction>> sinusoidal_moov;
    std::shared_ptr<C_SinClock<sf::Clock>> sin_clock;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        position = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        parallax = entity->template GetComponent<C_Parallax<int>>();
        sinusoidal_moov = entity->template GetComponent<C_SinMoov<SinusoidalFunction>>();
        sin_clock = entity->template GetComponent<C_SinClock<sf::Clock>>();
        if (!sinusoidal_moov)
            continue;
        double amplitude = sinusoidal_moov->getValue().amplitude;
        double frequency = sinusoidal_moov->getValue().frequency;
        double phase = sinusoidal_moov->getValue().phase;

        double player_x = position->getValue().first;
        double player_y = position->getValue().second;

        double x = player_x;
        double y = amplitude * std::sin(2 * M_PI * sin_clock->getValue().getElapsedTime().asSeconds() * frequency + phase) + player_y;
        position->setValue(std::make_pair(x, y));
    }
}