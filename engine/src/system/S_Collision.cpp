#include "system/S_Collision.hpp"

std::vector<std::shared_ptr<IEntity>> S_Collision::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Hitbox<std::pair<int, int>>)) &&
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Life<int>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

std::shared_ptr<IEntity> S_Collision::reCreateEntity(
        std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
        int id,
        std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp,
        Scene * arg_scene) {
    std::shared_ptr<IEntity> new_entity;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
    std::ifstream file(arg_scene->filepath_);
    json data;

    file >> data;
    file.close();
    for (const auto& entity_config : data["entities"]) {
        if (entity_config["id"] == id) {
            new_entity = arg_scene->CreateEntityFromConfig(entity_config, data["components"]);
            std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
            std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
            sprite->getValue().setTextureRect(rect->getValue());
            new_entity->SetBaseId(entity_config["id"]);
            arg_all_entities.push_back(new_entity);
        }
    }
    return new_entity;
}

void S_Collision::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
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
    std::shared_ptr<C_Target<int>> target;
    std::shared_ptr<C_Life<int>> life_1;
    std::shared_ptr<C_Life<int>> life_2;
    std::shared_ptr<C_BonusPower<std::pair<int, int>>> power_1;
    std::shared_ptr<C_BonusPower<std::pair<int, int>>> power_2;
    std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon_1;
    std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon_2;
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<IEntity>>>> vector_entities;
    std::shared_ptr<IEntity> new_entity;
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<IEntity>>>> vector_entities_1;
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<IEntity>>>> vector_entities_2;
    std::shared_ptr<C_Invincibility<bool>> is_invincible_1;
    std::shared_ptr<C_Invincibility<bool>> is_invincible_2;
    std::shared_ptr<C_IsAutoMove<bool>> is_auto_move;
    std::shared_ptr<C_Invisible<bool>> is_invisible_1;
    std::shared_ptr<C_Invisible<bool>> is_invisible_2;
    std::shared_ptr<C_EnemyAmmo<bool>> enemy_ammo_1;
    std::shared_ptr<C_EnemyAmmo<bool>> enemy_ammo_2;
    std::shared_ptr<C_Breakable<bool>> is_breakable_1;
    std::shared_ptr<C_Breakable<bool>> is_breakable_2;
    float x1;
    float y1;
    float x2;
    float y2;

    for (const std::shared_ptr<IEntity>& entity1 : arg_entities) {
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
        vector_entities_1 = entity1->template GetComponent<C_Inventory<std::vector<std::shared_ptr<IEntity>>>>();
        is_invincible_1 = entity1->template GetComponent<C_Invincibility<bool>>();
        is_invisible_1 = entity1->template GetComponent<C_Invisible<bool>>();
        enemy_ammo_1 = entity1->template GetComponent<C_EnemyAmmo<bool>>();
        is_breakable_1 = entity1->template GetComponent<C_Breakable<bool>>();
        for (const std::shared_ptr<IEntity>& entity2 : arg_entities) {
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
            vector_entities_2 = entity2->template GetComponent<C_Inventory<std::vector<std::shared_ptr<IEntity>>>>();
            is_invincible_2 = entity2->template GetComponent<C_Invincibility<bool>>();
            is_invisible_2 = entity2->template GetComponent<C_Invisible<bool>>();
            enemy_ammo_2 = entity2->template GetComponent<C_EnemyAmmo<bool>>();
            is_auto_move = entity2->template GetComponent<C_IsAutoMove<bool>>();
            is_breakable_2 = entity2->template GetComponent<C_Breakable<bool>>();
            if (!position_comp_2 || !hitbox_comp_2)
                continue;
            if (x1 < x2 + hitbox_comp_2->getValue().first &&
                x1 + hitbox_comp_1->getValue().first> x2 &&
                y1 < y2 + hitbox_comp_2->getValue().second &&
                y1 + hitbox_comp_1->getValue().second > y2) {
                    if (is_breakable_2)
                    {
                        entity2->is_dead_ = true;
                        break;
                    }
                    if (is_breakable_1)
                    {
                        entity1->is_dead_ = true;
                        break;
                    }
                    std::list<int> my_list = {22, 23, 24, 38, 39, 40};

                    if (is_player && is_player_ammo_2 && follow) {
                        if (is_auto_move)
                            if (is_auto_move->getValue())
                                continue;
                        vector_entities = entity1->template GetComponent<C_Inventory<std::vector<std::shared_ptr<IEntity>>>>();
                        if (!follow->getValue()) {
                            if ((std::find(my_list.begin(), my_list.end(), entity2->GetBaseId()) != my_list.end())) {
                                if (x2 - x1 > 0) {
                                    new_entity = reCreateEntity(arg_scene->entities_, 22, position_comp_2, arg_scene);
                                } else {
                                    new_entity = reCreateEntity(arg_scene->entities_, 38, position_comp_2, arg_scene);
                                }
                                new_follow = new_entity->template GetComponent<C_Follow<bool>>();
                                target = new_entity->template GetComponent<C_Target<int>>();
                                target->setValue(entity1->GetId());
                                new_follow->getValue() = true;

                                std::shared_ptr<C_Weapon<std::pair<int, int>>> old_weapon = entity2->template GetComponent<C_Weapon<std::pair<int, int>>>();
                                std::shared_ptr<C_Weapon<std::pair<int, int>>> new_weapon = new_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();

                                new_weapon->getValue() = old_weapon->getValue();

                                vector_entities->getValue().push_back(new_entity);
                                remove_copy(vector_entities->getValue().begin(), vector_entities->getValue().end(), vector_entities->getValue().begin(), entity2);
                                entity2->is_dead_ = true;
                            } else {
                                follow->getValue() = true;
                                target = entity2->template GetComponent<C_Target<int>>();
                                target->setValue(entity1->GetId());
                                vector_entities->getValue().push_back(entity2);
                            }
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

                    if ((is_invisible_1 && enemy_ammo_2) || (is_invisible_2 && enemy_ammo_1))
                        continue;

                    if (is_bonus && is_player_2) {
                        for (std::shared_ptr<IEntity>& v_entity: vector_entities_2->getValue()) {
                            if ((std::find(my_list.begin(), my_list.end(), v_entity->GetId()) != my_list.end())) {
                                std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
                                weapon->getValue() = power_1->getValue();
                            }
                        }
                        weapon_2->getValue() = power_1->getValue();
                        entity1->is_dead_ = true;
                        continue;
                    }
                    if (is_bonus_2 && is_player) {
                        for (std::shared_ptr<IEntity>& v_entity: vector_entities_1->getValue()) {
                            if ((std::find(my_list.begin(), my_list.end(), v_entity->GetId()) != my_list.end())) {
                                std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
                                weapon->getValue() = power_2->getValue();
                            }
                        }
                        weapon_1->getValue() = power_2->getValue();
                        entity2->is_dead_ = true;
                        continue;
                    }
                    if ((!is_player && !is_player_2 && !is_player_ammo && !is_player_ammo_2 && !is_bonus && !is_bonus_2))
                        continue;

                    if (is_player_ammo && is_invincible_1) {
                        entity2->is_dead_ = true;
                    }

                    if (is_player_ammo_2 && is_invincible_2) {
                        entity1->is_dead_ = true;
                    }

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
