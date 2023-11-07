#include "system/S_Gravity.hpp"

std::vector<std::shared_ptr<IEntity>> S_Gravity::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;
    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Velocity<std::pair<int, int>>)) &&
            entity->HasComponent(typeid(C_Gravity<double>)) &&
            entity->HasComponent(typeid(C_Grounded<bool>)) &&
            entity->HasComponent(typeid(C_Jump<bool>)) &&
            entity->HasComponent(typeid(C_Hitbox<std::pair<int, int>>)) && 
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_PositionStorage<std::pair<double, double>>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Gravity::Execute(int arg_is_server, Scene* arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities = Filter(arg_scene->entities_);
    std::shared_ptr<C_Velocity<std::pair<int, int>>> velocity_1;
    std::shared_ptr<C_Gravity<double>> gravity_1;
    std::shared_ptr<C_Grounded<bool>> grounded_1;
    std::shared_ptr<C_Jump<bool>> jump_1;
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_comp_1;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_1;
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_comp_2;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_2;
    std::shared_ptr<C_PositionStorage<std::pair<double, double>>> position_storage_1;
    std::shared_ptr<C_PlayerAmmo<bool>> is_friendly;

    for (const std::shared_ptr<IEntity>& entity1 : arg_entities) {
        velocity_1 = entity1->template GetComponent<C_Velocity<std::pair<int, int>>>();
        gravity_1 = entity1->template GetComponent<C_Gravity<double>>();
        grounded_1 = entity1->template GetComponent<C_Grounded<bool>>();
        jump_1 = entity1->template GetComponent<C_Jump<bool>>();
        hitbox_comp_1 = entity1->template GetComponent<C_Hitbox<std::pair<int, int>>>();
        position_1 = entity1->template GetComponent<C_Position<std::pair<double, double>>>();
        position_storage_1 = entity1->template GetComponent<C_PositionStorage<std::pair<double, double>>>();

        if (velocity_1 && gravity_1 && grounded_1 && position_1) {
            if(arg_scene->inputs_[6] == 1)
            {
                if (jump_1->getValue() == false)
                {
                    position_storage_1->setValue(position_1->getValue());
                    if (velocity_1->getValue().second == 0 && grounded_1->getValue())
                        velocity_1->getValue().second  = gravity_1->getValue() * 20;
                    if (velocity_1->getValue().second != 0)
                    {
                        velocity_1->getValue().second -= gravity_1->getValue();
                        position_1->getValue().second -= velocity_1->getValue().second;
                    }
                    else
                    {
                        jump_1->setValue(true);
                    }
                }
                else {
                    jump_1->setValue(false);
                    velocity_1->getValue().second = 0;
                    arg_scene->inputs_[6] = 0;
                }
            }
            for (const std::shared_ptr<IEntity>& entity2 : arg_scene->entities_) {

                hitbox_comp_2 = entity2->template GetComponent<C_Hitbox<std::pair<int, int>>>();
                position_2 = entity2->template GetComponent<C_Position<std::pair<double, double>>>();
                is_friendly = entity2->template GetComponent<C_PlayerAmmo<bool>>();
                if (hitbox_comp_2 && position_2 && is_friendly) {
                    if (position_1->getValue().second + hitbox_comp_1->getValue().second <= position_2->getValue().second &&
                        position_1->getValue().second + hitbox_comp_1->getValue().second + (velocity_1->getValue().second / 4) >= position_2->getValue().second && // FLOTTY
                        position_1->getValue().first + hitbox_comp_1->getValue().first >= position_2->getValue().first &&
                        position_1->getValue().first <= position_2->getValue().first + hitbox_comp_2->getValue().first) {
                        grounded_1->setValue(true);
                        velocity_1->getValue().second = 0;
                        break;
                    } else {
                        grounded_1->setValue(false);
                    }
                }
            }
            if (!grounded_1->getValue() && arg_scene->inputs_[6] != 1) {
                velocity_1->getValue().second += gravity_1->getValue();
                position_1->getValue().second += velocity_1->getValue().second / 4;
            }
        }
    }
}