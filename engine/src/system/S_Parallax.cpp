#include "system/S_Parallax.hpp"

std::vector<std::shared_ptr<Entity>> S_Parallax::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Parallax<int>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Parallax::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
        std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
        std::shared_ptr<sf::Event> event_) {
    std::shared_ptr<C_Position<std::pair<double, double>>> position;
    std::shared_ptr<C_PositionStart<std::pair<double, double>>> position_start;
    std::shared_ptr<C_PositionEnd<std::pair<double, double>>> position_end;
    std::shared_ptr<C_Parallax<int>> parallax;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        position = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        parallax = entity->template GetComponent<C_Parallax<int>>();
        position->setValue(std::make_pair(  position->getValue().first + parallax->getValue(),
                                            position->getValue().second));
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
