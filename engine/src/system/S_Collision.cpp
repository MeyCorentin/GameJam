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

void S_Collision::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
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
    std::shared_ptr<C_Life<int>> life_1;
    std::shared_ptr<C_Life<int>> life_2;
    std::shared_ptr<C_BonusPower<int>> power_1;
    std::shared_ptr<C_BonusPower<int>> power_2;
    std::shared_ptr<C_Weapon<int>> weapon_1;
    std::shared_ptr<C_Weapon<int>> weapon_2;
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
        power_1 = entity1->template GetComponent<C_BonusPower<int>>();
        weapon_1 = entity1->template GetComponent<C_Weapon<int>>();
        x1 = static_cast<float>(position_comp_1->getValue().first);
        y1 = static_cast<float>(position_comp_1->getValue().second);
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
            power_2 = entity2->template GetComponent<C_BonusPower<int>>();
            weapon_2 = entity2->template GetComponent<C_Weapon<int>>();
            x2 = static_cast<float>(position_comp_2->getValue().first);
            y2 = static_cast<float>(position_comp_2->getValue().second);
            if (!position_comp_2 || !hitbox_comp_2)
                continue;
            if (x1 < x2 + hitbox_comp_2->getValue().first &&
                x1 + hitbox_comp_1->getValue().first> x2 &&
                y1 < y2 + hitbox_comp_2->getValue().second &&
                y1 + hitbox_comp_1->getValue().second > y2) {
                    if (is_player && is_player_ammo_2 && follow) {
                        std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<Entity>>>> vector_entities = entity1->template GetComponent<C_Inventory<std::vector<std::shared_ptr<Entity>>>>();
                        if (!follow->getValue()) {
                            vector_entities->getValue().push_back(entity2);
                            follow->getValue() = true;
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

                    if (is_bonus && is_player_2) {
                        weapon_2->getValue() = power_1->getValue();
                        entity1->is_dead_ = true;
                        continue;
                    }
                    if (is_bonus_2 && is_player) {
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
