#include "system/S_Collision.hpp"

std::vector<std::shared_ptr<Entity>> S_Collision::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Hitbox<std::pair<int, int>>)) &&
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Life<int>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

std::shared_ptr<Entity> S_Collision::reCreateEntity(
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        int id,
        std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp) {
    std::shared_ptr<Entity> new_entity;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
    std::string filepath = "../../rtype/scene_test.json";
    std::ifstream file(filepath);
    json data;
    S_Input input;

    file >> data;
    file.close();
    std::cout << "Before for" << std::endl;
    for (const auto& entity_config : data["entities"]) {
        if (entity_config["id"] == id) {
            new_entity = input.CreateEntityFromConfig(entity_config, data["components"]);
            arg_all_entities.push_back(new_entity);
        }
    }
    return new_entity;
}

void S_Collision::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
        std::shared_ptr<sf::Event> event_) {
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_1;
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_comp_1;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_2;
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_comp_2;
    std::shared_ptr<C_Player<int>> is_player;
    std::shared_ptr<C_PlayerAmmo<bool>> is_player_ammo;
    std::shared_ptr<C_Bonus<bool>> is_bonus;
    std::shared_ptr<C_Player<int>> is_player_2;
    std::shared_ptr<C_PlayerAmmo<bool>> is_player_ammo_2;
    std::shared_ptr<C_Bonus<bool>> is_bonus_2;
    std::shared_ptr<C_Follow<bool>> follow;
    std::shared_ptr<C_Follow<bool>> new_follow;
    std::shared_ptr<C_Life<int>> life_1;
    std::shared_ptr<C_Life<int>> life_2;
    std::shared_ptr<C_BonusPower<std::pair<int, int>>> power_1;
    std::shared_ptr<C_BonusPower<std::pair<int, int>>> power_2;
    std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon_1;
    std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon_2;
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<Entity>>>> vector_entities;
    std::shared_ptr<Entity> new_entity;
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<Entity>>>> vector_entities_1;
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<Entity>>>> vector_entities_2;
    float x1;
    float y1;
    float x2;
    float y2;

    for (const std::shared_ptr<Entity>& entity1 : arg_entities) {
        position_comp_1 = entity1->template GetComponent<C_Position<std::pair<double, double>>>();
        hitbox_comp_1 = entity1->template GetComponent<C_Hitbox<std::pair<int, int>>>();
        is_player = entity1->template GetComponent<C_Player<int>>();
        is_bonus = entity1->template GetComponent<C_Bonus<bool>>();
        is_player_ammo = entity1->template GetComponent<C_PlayerAmmo<bool>>();
        life_1 = entity1->template GetComponent<C_Life<int>>();
        power_1 = entity1->template GetComponent<C_BonusPower<std::pair<int, int>>>();
        weapon_1 = entity1->template GetComponent<C_Weapon<std::pair<int, int>>>();
        x1 = static_cast<float>(position_comp_1->getValue().first);
        y1 = static_cast<float>(position_comp_1->getValue().second);
        vector_entities_1 = entity1->template GetComponent<C_Inventory<std::vector<std::shared_ptr<Entity>>>>();
        for (const std::shared_ptr<Entity>& entity2 : arg_entities) {
            if (entity1 == entity2)
                continue;
            position_comp_2 = entity2->template GetComponent<C_Position<std::pair<double, double>>>();
            hitbox_comp_2 = entity2->template GetComponent<C_Hitbox<std::pair<int, int>>>();
            is_player_2 = entity2->template GetComponent<C_Player<int>>();
            is_bonus_2 = entity2->template GetComponent<C_Bonus<bool>>();
            is_player_ammo_2 = entity2->template GetComponent<C_PlayerAmmo<bool>>();
            follow = entity2->template GetComponent<C_Follow<bool>>();
            life_2 = entity2->template GetComponent<C_Life<int>>();
            power_2 = entity2->template GetComponent<C_BonusPower<std::pair<int, int>>>();
            weapon_2 = entity2->template GetComponent<C_Weapon<std::pair<int, int>>>();
            x2 = static_cast<float>(position_comp_2->getValue().first);
            y2 = static_cast<float>(position_comp_2->getValue().second);
            vector_entities_2 = entity2->template GetComponent<C_Inventory<std::vector<std::shared_ptr<Entity>>>>();
            if (!position_comp_2 || !hitbox_comp_2)
                continue;
            if (x1 < x2 + hitbox_comp_2->getValue().first &&
                x1 + hitbox_comp_1->getValue().first> x2 &&
                y1 < y2 + hitbox_comp_2->getValue().second &&
                y1 + hitbox_comp_1->getValue().second > y2) {
                    if (is_player && is_player_ammo_2 && follow) {
                        vector_entities = entity1->template GetComponent<C_Inventory<std::vector<std::shared_ptr<Entity>>>>();
                        if (!follow->getValue()) {
                            if (x2 - x1 > 0)
                                new_entity = reCreateEntity(arg_all_entities, 22, position_comp_2);
                            else
                                new_entity = reCreateEntity(arg_all_entities, 38, position_comp_2);
                            entity2->is_dead_ = true;
                            vector_entities->getValue().push_back(new_entity);
                            new_follow = new_entity->template GetComponent<C_Follow<bool>>();
                            new_follow->getValue() = true;
                        }
                    }
                    if ((is_player && is_player_2) ||
                        (is_player_ammo && is_player_ammo_2) ||
                        (is_player_ammo && is_player_2) ||
                        (is_player_ammo_2 && is_player))
                    continue;

                    if ((is_bonus && is_bonus_2) ||
                        (is_bonus && !is_player_2) ||
                        (is_bonus_2 && !is_player))
                    continue;

                    std::list<int> my_list = {22, 23, 24, 38, 39, 40};

                    if (is_bonus && is_player_2) {
                        for (std::shared_ptr<Entity>& v_entity: vector_entities_2->getValue()) {
                            if ((std::find(my_list.begin(), my_list.end(), v_entity->GetId()) != my_list.end())) {
                                std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
                                weapon->getValue() = power_1->getValue();
                                std::cout << weapon->getValue().first << " - " << weapon->getValue().second << std::endl;
                            }
                        }
                        weapon_2->getValue() = power_1->getValue();
                        entity1->is_dead_ = true;
                        continue;
                    }
                    if (is_bonus_2 && is_player) {
                        for (std::shared_ptr<Entity>& v_entity: vector_entities_1->getValue()) {
                            if ((std::find(my_list.begin(), my_list.end(), v_entity->GetId()) != my_list.end())) {
                                std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
                                weapon->getValue() = power_2->getValue();
                                std::cout << weapon->getValue().first << " - " << weapon->getValue().second << std::endl;
                            }
                        }
                        weapon_1->getValue() = power_2->getValue();
                        entity2->is_dead_ = true;
                        continue;
                    }
                    if ((!is_player && !is_player_2 && !is_player_ammo && !is_player_ammo_2 && !is_bonus && !is_bonus_2))
                        continue;
                    if (life_1->getValue() != 0)
                        life_1->setValue(life_1->getValue() - 1);
                    if (life_2->getValue() != 0)
                        life_2->setValue(life_2->getValue() - 1);
                    if (life_1->getValue() == 0)
                        entity1->is_dead_ = true;
                    if (life_2->getValue() == 0)
                        entity2->is_dead_ = true;
            }
        }
    }
}
