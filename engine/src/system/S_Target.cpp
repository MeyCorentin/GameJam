#include "system/S_Target.hpp"

std::vector<std::shared_ptr<Entity>> S_Target::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities)  {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Target<int>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Target::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_input,
        std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
        std::shared_ptr<sf::Event> event_) {
    int current_mana;
    std::shared_ptr<C_Target<int>> target;
    std::shared_ptr<C_Ammo<int>> ammo;
    std::shared_ptr<C_Follow<bool>> follow;
    std::shared_ptr<C_Shoot<bool>> shoot;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_1;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_2;
    std::shared_ptr<C_Direction<std::pair<double, double>>> direction_new;
    std::shared_ptr<C_FireRate<sf::Clock>>  fire_rate;
    std::shared_ptr<C_FireRateSpeed<double>>  fire_rate_speed;
    std::shared_ptr<C_Range<int>>  range;
    std::shared_ptr<Entity> new_entity;
    std::vector<std::shared_ptr<Entity>> temp_entities;
    std::string filepath = "../../rtype/scene_test.json";
    std::ifstream file(filepath);
    std::pair<double, double> direction;
    double length;
    json data;
    file >> data;
    file.close();
    S_Input input;

    for (const std::shared_ptr<Entity>& entity1 : arg_entities) {
        for (const std::shared_ptr<Entity>& entity2 : arg_all_Entities) {
            target = entity1->template GetComponent<C_Target<int>>();
            follow = entity1->template GetComponent<C_Follow<bool>>();
            shoot = entity1->template GetComponent<C_Shoot<bool>>();
            ammo = entity1->template GetComponent<C_Ammo<int>>();
            position_comp_1 = entity1->template GetComponent<C_Position<std::pair<double, double>>>();
            position_comp_2 = entity2->template GetComponent<C_Position<std::pair<double, double>>>();
            fire_rate = entity1->template GetComponent<C_FireRate<sf::Clock>>();
            fire_rate_speed =  entity1->template GetComponent<C_FireRateSpeed<double>>();
            range =  entity1->template GetComponent<C_Range<int>>();

            if (entity1 == entity2)
                continue;
            if (follow &&
                position_comp_1 &&
                position_comp_2 &&
                target->getValue() == entity2->GetId())
            {
                if (follow->getValue() == true)
                {
                    position_comp_1->getValue().first = position_comp_2->getValue().first;
                    position_comp_1->getValue().second = position_comp_2->getValue().second;
                }
            }
            if (shoot &&
                ammo &&
                position_comp_1 &&
                position_comp_2 &&
                target->getValue() == entity2->GetId() &&
                fire_rate &&
                fire_rate_speed)
            {
                if (shoot->getValue() == false)
                    continue;
                if (fire_rate->getValue().getElapsedTime().asSeconds() < fire_rate_speed->getValue())
                    continue;
                for (const auto& entity_config : data["entities"]) {
                    if (entity_config["id"] != ammo->getValue())
                        continue;
                    direction.first = position_comp_2->getValue().first - position_comp_1->getValue().first;
                    direction.second = position_comp_2->getValue().second - position_comp_1->getValue().second;
                    length = std::sqrt(direction.first * direction.first + direction.second * direction.second);
                    if (length > range->getValue())
                        continue;
                    new_entity = input.CreateEntityFromConfig(entity_config, data["components"], arg_sprites, arg_textures);
                    direction_new = new_entity->template GetComponent<C_Direction<std::pair<double, double>>>();
                    position_new = new_entity->template GetComponent<C_Position<std::pair<double, double>>>();
                    if (!direction_new || !position_new)
                        continue;
                    if (new_entity->HasComponent(typeid(C_SpriteRect<sf::IntRect>)) &&
                        new_entity->HasComponent(typeid(C_Sprite<sf::Sprite>))) {
                        std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
                        std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
                        sprite->getValue().setTextureRect(rect->getValue());
                    }
                    position_new->setValue(std::make_pair(position_comp_1->getValue().first, position_comp_1->getValue().second));
                    direction_new->setValue(std::make_pair(direction.first /= length, direction.second /= length));
                    temp_entities.push_back(new_entity);
                    fire_rate->getValue().restart();
                }
            }
        }
    }
    for (const std::shared_ptr<Entity>& temp_entity : temp_entities) {
        arg_all_Entities.push_back(temp_entity);
    }
}