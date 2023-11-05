
#include "system/S_InputFromPlayer.hpp"


std::vector<std::shared_ptr<Entity>> S_InputFromPlayer::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Hitbox<std::pair<int, int>>)) &&
            entity->HasComponent(typeid(C_Player<int>)) &&
            entity->HasComponent(typeid(C_ShootCharging<bool>)) &&
            entity->HasComponent(typeid(C_Inventory<std::vector<std::shared_ptr<Entity>>>)) &&
            entity->HasComponent(typeid(C_ChargedShoot<sf::Clock>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_InputFromPlayer::Execute(
        int arg_is_server,
        Scene * arg_scene)
{
    std::vector<std::shared_ptr<Entity>> arg_entities =  Filter(arg_scene->entities_);
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size;
    std::shared_ptr<C_Player<int>> index;
    std::shared_ptr<C_ShootCharging<bool>> is_charging;
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<Entity>>>> vector_entities;
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock;
    for (std::pair<int, int> current_message: arg_scene->messages_) {
        for (const std::shared_ptr<Entity>& entity : arg_scene->entities_) {
            index = entity->template GetComponent<C_Player<int>>();
            if (!index)
                continue;
            if (index->getValue() != current_message.first)
                continue;
            position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
            hitbox_size = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();
            is_charging = entity->template GetComponent<C_ShootCharging<bool>>();
            vector_entities = entity->template GetComponent<C_Inventory<std::vector<std::shared_ptr<Entity>>>>();
            clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();
            if (!position_comp)
                continue;
            if (current_message.second == 0 || current_message.second == 100)
                continue;
            switch (current_message.second) {
                case 200: // Up
                    if (position_comp->getValue().second > 5)
                        position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second - 5));
                        arg_scene->messages_.erase(arg_scene->messages_.begin());
                    break;
                case 210: // Left
                    if (position_comp->getValue().first > 5)
                        position_comp->setValue(std::make_pair(position_comp->getValue().first - 5, position_comp->getValue().second));
                        arg_scene->messages_.erase(arg_scene->messages_.begin());
                    break;
                case 220: // Down
                    if (position_comp->getValue().second <  arg_scene->window_->getSize().y - 5 - hitbox_size->getValue().second)
                        position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second + 5));
                        arg_scene->messages_.erase(arg_scene->messages_.begin());
                    break;
                case 230: // Right
                    if (position_comp->getValue().first < arg_scene->window_->getSize().x - 5- hitbox_size->getValue().first)
                        position_comp->setValue(std::make_pair(position_comp->getValue().first + 5, position_comp->getValue().second));
                        arg_scene->messages_.erase(arg_scene->messages_.begin());
                    break;
                case 300:
                    std::cout << " CHARGING SHOOT " << std::endl;
                    if (is_charging->getValue() == false) {
                        std::cout << " CHARGING SHOOT 1 " << std::endl;
                        clock->getValue().restart();
                        for (const auto& entity_pick : arg_scene->list_entities_)
                        {
                            std::shared_ptr<Entity> new_entity = std::make_shared<Entity>(*entity_pick);
                            std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
                            if (entity_pick->GetId() != 27)
                                continue;
                            std::cout << " CHARGING SHOOT 2 " << std::endl;
                            new_entity->SetId(arg_scene->id_store_++);
                            new_entity->SetBaseId(entity_pick->GetId());
                            position_new = new_entity->template GetComponent<C_Position<std::pair<double, double>>>();
                            std::shared_ptr<C_PositionShot<std::pair<double, double>>> position_shot = new_entity->template GetComponent<C_PositionShot<std::pair<double, double>>>();
                            std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
                            std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
                            std::shared_ptr<C_Target<int>> target = new_entity->template GetComponent<C_Target<int>>();
                            target->setValue(entity->GetId());
                            sprite->getValue().setTextureRect(rect->getValue());
                            position_new->setValue(std::make_pair(position_comp->getValue().first + position_shot->getValue().first, position_comp->getValue().second + position_shot->getValue().second));
                            arg_scene->entities_.push_back(new_entity);
                            vector_entities->getValue().push_back(new_entity);
                        }
                        std::cout << " CHARGING SHOOT 3 " << std::endl;
                        is_charging->getValue() = true;
                    }
                    arg_scene->messages_.erase(arg_scene->messages_.begin());
                    break;
                default:
                    std::cerr << "Unknown message data: " << current_message.second << std::endl;
                    break;
            }
        }
    }
}
