#include "system/S_Animation.hpp"

std::vector<std::shared_ptr<Entity>> S_Animation::Filter(const std::vector<std::shared_ptr<Entity>>& _entities)  {
    std::vector<std::shared_ptr<Entity>> filteredEntities;
    for (const std::shared_ptr<Entity>& entity : _entities) {
        if (entity->HasComponent(typeid(C_Sprite<sf::Sprite>)) &&
            entity->HasComponent(typeid(C_Clock<sf::Clock>)) &&
            entity->HasComponent(typeid(C_SpriteRect<sf::IntRect>)) &&
            !entity->HasComponent(typeid(C_IsMoving<bool>)) &&
            entity->HasComponent(typeid(C_UniqueAnimation<bool>)) &&
            entity->HasComponent(typeid(C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>)) &&
            entity->HasComponent(typeid(C_ClockSpeed<double>)) &&
            entity->HasComponent(typeid(C_Animation<bool>))) {
            filteredEntities.push_back(entity);
        }
    }
    return filteredEntities;
}

void S_Animation::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& _entities,
        std::shared_ptr<sf::RenderWindow> _window,
        std::vector<int> _inputs,
        std::vector<std::shared_ptr<Entity>>& allEntities,
        std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
        std::shared_ptr<sf::Event> event_) {
    for (const std::shared_ptr<Entity>& entity : _entities) {
        std::shared_ptr<C_Sprite<sf::Sprite>> sprite = entity->template GetComponent<C_Sprite<sf::Sprite>>();
        std::shared_ptr<C_Clock<sf::Clock>> clock = entity->template GetComponent<C_Clock<sf::Clock>>();
        std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
        std::shared_ptr<C_UniqueAnimation<bool>> unique = entity->template GetComponent<C_UniqueAnimation<bool>>();
        std::shared_ptr<C_Life<int>> life = entity->template GetComponent<C_Life<int>>();
        std::shared_ptr<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>> size = entity->template GetComponent<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>();
        std::shared_ptr<C_ClockSpeed<double>> clock_speed = entity->template GetComponent<C_ClockSpeed<double>>();
        std::shared_ptr<C_SingleAnimation<bool>> single_animation = entity->template GetComponent<C_SingleAnimation<bool>>();
        bool animaion = entity->template GetComponent<C_Animation<bool>>()->getValue();
        if (clock->getValue().getElapsedTime().asSeconds() <= 0.1f + clock_speed->getValue())
            continue;
        if (rect->getValue().left >= (size->getValue().first.first - rect->getValue().width) + size->getValue().second.first) {
            if (unique->getValue())
                entity->is_dead_ = true;
            else if (single_animation) {
                if (single_animation->getValue()) {
                    size->getValue().first.first = rect->getValue().width;
                    size->getValue().first.second = rect->getValue().height;
                    rect->getValue().left = size->getValue().second.first;
                }
            } else
                rect->getValue().left = size->getValue().second.first;
        } else {
            rect->getValue().left += rect->getValue().width;
        }
        sprite->getValue().setTextureRect(rect->getValue());
        clock->getValue().restart();
    }
}

