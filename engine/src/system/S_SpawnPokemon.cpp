#include "system/S_SpawnPokemon.hpp"


std::vector<std::shared_ptr<IEntity>> S_SpawnPokemon::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_Hitbox<std::pair<int, int>>)) &&
            entity->HasComponent(typeid(C_Player<int>)) &&
            entity->HasComponent(typeid(C_SpawnClock<sf::Clock>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_SpawnPokemon::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::vector<int> spawn_id;

    std::shared_ptr<C_Position<std::pair<double, double>>> spawn_position;
    spawn_position->SetValue(std::pair(500,500));

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        std::shared_ptr<C_Position<std::pair<double, double>>> position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();
        std::shared_ptr<C_SpawnClock<sf::Clock>> spawn_clock = entity->template GetComponent<C_SpawnClock<sf::Clock>>();
        std::shared_ptr<C_IsFighting<bool>> is_fighting = entity->template GetComponent<C_IsFighting<bool>>();
        for (const std::shared_ptr<IEntity>& entity_check : arg_scene->entities_) {
            std::shared_ptr<C_Position<std::pair<double, double>>> position_check = entity_check->template GetComponent<C_Position<std::pair<double, double>>>();
            std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_check = entity_check->template GetComponent<C_Hitbox<std::pair<int, int>>>();
            std::shared_ptr<C_Grass<bool>> c_grass_check = entity_check->template GetComponent<C_Grass<bool>>();
            if (is_fighting->getValue() == true)
                continue;
            if (!position_check || !hitbox_check || !c_grass_check)
                continue;
            if (entity_check ==  entity)
                continue;
                if (position_comp->getValue().first < position_check->getValue().first + hitbox_check->getValue().first &&
                    position_comp->getValue().first + hitbox_size->getValue().first > position_check->getValue().first  &&
                    position_comp->getValue().second < position_check->getValue().second + hitbox_check->getValue().second &&
                    position_comp->getValue().second + hitbox_size->getValue().second > position_check->getValue().second)  {
                        if (spawn_clock->getValue().getElapsedTime().asSeconds() >= 3)
                        {
                            if (rand() % 3 == 0)
                            {
                                std::cout << " spawn " << std::endl;
                                is_fighting->setValue(true);
                                spawn_id.push_back(501);
                                spawn_id.push_back(601);
                                spawn_id.push_back( 1000 + (rand() % 151));
                                spawn_clock->getValue().restart();
                            }
                        }
                    break;
                }
            }
            for (int id: spawn_id)
            {
                arg_scene->createEntity(arg_scene->entities_, id, position_comp);
            }
        spawn_id.clear();
    }
}