#include "system/S_Animation.hpp"

std::vector<std::shared_ptr<IEntity>> S_Animation::Filter(const std::vector<std::shared_ptr<IEntity>>& _entities)  {
    std::vector<std::shared_ptr<IEntity>> filteredEntities;
    for (const std::shared_ptr<IEntity>& entity : _entities) {
        if (entity->HasComponent(typeid(C_Sprite<sf::Sprite>)) &&
            entity->HasComponent(typeid(C_Clock<sf::Clock>)) &&
            entity->HasComponent(typeid(C_SpriteRect<sf::IntRect>)) &&
            // !entity->HasComponent(typeid(C_IsMoving<bool>)) &&
            entity->HasComponent(typeid(C_UniqueAnimation<bool>)) &&
            entity->HasComponent(typeid(C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>)) &&
            entity->HasComponent(typeid(C_ClockSpeed<double>)) &&
            entity->HasComponent(typeid(C_AnimationDirection<int>)) &&
            entity->HasComponent(typeid(C_Animation<bool>))) {
            filteredEntities.push_back(entity);
        }
    }
    return filteredEntities;
}

void S_Animation::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        std::shared_ptr<C_Sprite<sf::Sprite>> sprite = entity->template GetComponent<C_Sprite<sf::Sprite>>();
        std::shared_ptr<C_Clock<sf::Clock>> clock = entity->template GetComponent<C_Clock<sf::Clock>>();
        std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
        std::shared_ptr<C_UniqueAnimation<bool>> unique = entity->template GetComponent<C_UniqueAnimation<bool>>();
        std::shared_ptr<C_Life<int>> life = entity->template GetComponent<C_Life<int>>();
        std::shared_ptr<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>> size = entity->template GetComponent<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>();
        std::shared_ptr<C_ClockSpeed<double>> clock_speed = entity->template GetComponent<C_ClockSpeed<double>>();
        std::shared_ptr<C_SingleAnimation<bool>> single_animation = entity->template GetComponent<C_SingleAnimation<bool>>();
        std::shared_ptr<C_AnimationDirection<int>> animation_direction = entity->template GetComponent<C_AnimationDirection<int>>();
        std::shared_ptr<C_NextTimeline<std::string>> next_timeline =  entity->template GetComponent<C_NextTimeline<std::string>>();
        bool animaion = entity->template GetComponent<C_Animation<bool>>()->getValue();
        if (clock->getValue().getElapsedTime().asSeconds() <= 0.1f + clock_speed->getValue()) {
            continue;
        }
        if (animation_direction->getValue() == 0) {
            if (rect->getValue().left >= (size->getValue().first.first - rect->getValue().width) + size->getValue().second.first) {
                if (unique->getValue()) {
                    entity->is_dead_ = true;
                    if (next_timeline) {
                        arg_scene->need_switch_ = true;
                        arg_scene->next_timeline_ = next_timeline->getValue();
                    }
                }
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
        } else if (animation_direction->getValue() == 1) {
            if (rect->getValue().left <= (size->getValue().first.first - rect->getValue().width) + size->getValue().second.first) {
                if (unique->getValue()) {
                    entity->is_dead_ = true;
                    if (next_timeline) {
                        arg_scene->need_switch_ = true;
                        arg_scene->next_timeline_ = next_timeline->getValue();
                    }
                }
                else if (single_animation) {
                    if (single_animation->getValue()) {
                        size->getValue().first.first = rect->getValue().width;
                        size->getValue().first.second = rect->getValue().height;
                        rect->getValue().left = size->getValue().second.first;
                    }
                } else
                    rect->getValue().left = size->getValue().second.first;
            } else {
                rect->getValue().left -= rect->getValue().width;
            }
        }
        sprite->getValue().setTextureRect(rect->getValue());
        clock->getValue().restart();
    }
}

