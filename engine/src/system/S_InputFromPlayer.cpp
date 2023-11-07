
#include "system/S_InputFromPlayer.hpp"


void S_InputFromPlayer::BasicShot(
    const std::shared_ptr<IEntity>& entity,
    std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    Scene * arg_scene)
{
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();

    if (clock->getValue().getElapsedTime().asSeconds() > 1)
        arg_scene->createEntity(arg_all_entities, 9, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.6)
        arg_scene->createEntity(arg_all_entities, 8, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.4)
        arg_scene->createEntity(arg_all_entities, 7, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.2)
        arg_scene->createEntity(arg_all_entities, 6, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.1)
        arg_scene->createEntity(arg_all_entities, 5, position_comp);
    else
        arg_scene->createEntity(arg_all_entities, 3, position_comp);
}


bool S_InputFromPlayer::IsInInventory(
    int base_id,
    const std::shared_ptr<IEntity>& entity,
    std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    Scene * arg_scene)
{
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<IEntity>>>> vector_entities = entity->template GetComponent<C_Inventory<std::vector<std::shared_ptr<IEntity>>>>();
    for (std::shared_ptr<IEntity>& v_entity: vector_entities->getValue()) {
        std::cout << "ID : " << v_entity->GetBaseId() << std::endl;
        if (v_entity->GetBaseId() == base_id)
        {
            return true;
        }
    }
    return false;
}


void S_InputFromPlayer::DeleteFromInventory(
    int base_id,
    const std::shared_ptr<IEntity>& entity,
    std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    Scene * arg_scene)
{
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<IEntity>>>> vector_entities = entity->template GetComponent<C_Inventory<std::vector<std::shared_ptr<IEntity>>>>();
    for (auto it = vector_entities->getValue().begin(); it != vector_entities->getValue().end();)
    {
        if ((*it)->GetBaseId() == 27)
        {
            (*it)->is_dead_ = true;
            it = vector_entities->getValue().erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void S_InputFromPlayer::SpecialShot(
    const std::shared_ptr<IEntity>& entity,
    std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    Scene * arg_scene)
{
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<IEntity>>>> vector_entities = entity->template GetComponent<C_Inventory<std::vector<std::shared_ptr<IEntity>>>>();

    //Player attacks
    std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon_player = entity->template GetComponent<C_Weapon<std::pair<int, int>>>();

    std::list<int> my_list_1 = {22, 23, 24};
    std::list<int> my_list_2 = {38, 39, 40};
    std::list<int> my_list_3 = {4, 29};

    for (std::shared_ptr<IEntity>& v_entity: vector_entities->getValue()) {
        if ((std::find(my_list_1.begin(), my_list_1.end(), v_entity->GetId()) != my_list_1.end())) {
            std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
            std::shared_ptr<C_Position<std::pair<double, double>>> position_force = v_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            if (weapon->getValue().first != -1) {
                if (weapon->getValue().first == 25) {
                    for (int i = 0; i < 1; i++) { //TODO Set to 5
                        arg_scene->createEntity(arg_all_entities, weapon->getValue().first, position_force);
                        arg_scene->createEntity(arg_all_entities, 32, position_force); //TODO Change that
                    }
                }
                if (weapon->getValue().first == 26) {
                    arg_scene->createEntity(arg_all_entities, weapon->getValue().first, position_force);
                }
            }
        }
        if ((std::find(my_list_2.begin(), my_list_2.end(), v_entity->GetId()) != my_list_2.end())) {
            std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
            std::shared_ptr<C_Position<std::pair<double, double>>> position_force = v_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            if (weapon->getValue().second != -1) {
                if (weapon->getValue().second == 32) {
                    for (int i = 0; i < 1; i++) { //TODO Set to 5
                        arg_scene->createEntity(arg_all_entities, weapon->getValue().second, position_force);
                        arg_scene->createEntity(arg_all_entities, 25, position_force); //TODO Change that
                    }
                }
                if (weapon->getValue().second == 43) {
                    arg_scene->createEntity(arg_all_entities, weapon->getValue().second, position_force);
                }
            }
        }
    }

    //Drone attacks
    for (std::shared_ptr<IEntity>& v_entity: vector_entities->getValue()) {
        if ((std::find(my_list_3.begin(), my_list_3.end(), v_entity->GetId()) != my_list_3.end()) && weapon_player->getValue().first == 26) {
            std::shared_ptr<C_Position<std::pair<double, double>>> position_drone = v_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
            for (std::shared_ptr<IEntity>& v_entity: vector_entities->getValue()) {
                if ((std::find(my_list_1.begin(), my_list_1.end(), v_entity->GetId()) != my_list_1.end())) {
                    arg_scene->createEntity(arg_all_entities, weapon->getValue().first, position_drone);
                }
            }
            for (std::shared_ptr<IEntity>& v_entity: vector_entities->getValue()) {
                if ((std::find(my_list_2.begin(), my_list_2.end(), v_entity->GetId()) != my_list_2.end())) {
                    arg_scene->createEntity(arg_all_entities, weapon->getValue().second, position_drone);
                }
            }
        }
    }
}

std::vector<std::shared_ptr<IEntity>> S_InputFromPlayer::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Hitbox<std::pair<int, int>>)) &&
            entity->HasComponent(typeid(C_Player<int>)) &&
            entity->HasComponent(typeid(C_ShootCharging<bool>)) &&
            entity->HasComponent(typeid(C_Inventory<std::vector<std::shared_ptr<IEntity>>>)) &&
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
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size;
    std::shared_ptr<C_Player<int>> index;
    std::shared_ptr<C_ShootCharging<bool>> is_charging;
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<IEntity>>>> vector_entities;
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock;
    for (std::pair<int, int> current_message: arg_scene->messages_) {
        for (const std::shared_ptr<IEntity>& entity : arg_scene->entities_) {
            index = entity->template GetComponent<C_Player<int>>();
            if (!index)
                continue;
            if (index->getValue() != current_message.first)
                continue;
            position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
            hitbox_size = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();
            is_charging = entity->template GetComponent<C_ShootCharging<bool>>();
            vector_entities = entity->template GetComponent<C_Inventory<std::vector<std::shared_ptr<IEntity>>>>();
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
                    if (is_charging->getValue() == false && !IsInInventory(27,entity, arg_scene->entities_, position_comp, arg_scene)) {
                        clock->getValue().restart();
                        is_charging->getValue() = true;
                    }
                    arg_scene->messages_.erase(arg_scene->messages_.begin());
                    break;
                case 301:
                    BasicShot(entity, arg_scene->entities_, position_comp, arg_scene);
                    SpecialShot(entity, arg_scene->entities_, position_comp, arg_scene);
                    is_charging->getValue() = false;
                    arg_scene->messages_.erase(arg_scene->messages_.begin());
                    break;
                default:
                    std::cerr << "Unknown message data: " << current_message.second << std::endl;
                    break;
            }
        }
    }
}
