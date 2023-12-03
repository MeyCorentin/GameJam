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

    int level = 0;

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
                                spawn_id.push_back(502);
                                spawn_id.push_back(601);
                                spawn_id.push_back(602);
                                for (const std::shared_ptr<IEntity>& mew : arg_scene->entities_) {
                                    if (mew->GetBaseId() == 5)
                                    {
                                        std::shared_ptr<C_Position<std::pair<double, double>>> mew_pos = mew->template GetComponent<C_Position<std::pair<double, double>>>();
                                        std::pair<double, double> pos =std::make_pair(300,300);
                                        mew_pos->setValue(pos);
                                        std::shared_ptr<C_Experience<int>> xp = mew->template GetComponent<C_Experience<int>>();
                                        level = (xp->getValue() / 100);
                                    }
                                }
                                spawn_id.push_back(1000 + (rand() % 151));
                                spawn_id.push_back(503);
                                spawn_id.push_back(505);
                                spawn_id.push_back(504);
                                spawn_id.push_back(506);
                                spawn_id.push_back(507);
                            }
                        }
                    break;
                }
            }
            for (int id: spawn_id)
            {
                arg_scene->createEntity(arg_scene->entities_, id, position_comp);
            }
            for (const std::shared_ptr<IEntity>& entity_mob : arg_scene->entities_) {
                if (entity_mob->GetId() > 1000 && entity_mob->GetId() < 1152)
                {
                    std::shared_ptr<C_Experience<int>> xp = entity_mob->template GetComponent<C_Experience<int>>();
                    if (xp->getValue() < 100)
                    {
                        xp->setValue((level + rand() % 5 ) * 100);
                        std::cout << "level: " << xp->getValue() / 100 << std::endl;
                    }
                }
            }
        spawn_id.clear();
    }
    for (const std::shared_ptr<IEntity>& entity_mob : arg_scene->entities_) {
        if (entity_mob->GetBaseId() == 5)
        {
            std::shared_ptr<C_Experience<int>> xp = entity_mob->template GetComponent<C_Experience<int>>();
            level = (xp->getValue() / 100);
        }
        // std::cout << "test" << std::endl;
        // std::cout << entity_mob->GetId()<< std::endl;
        // std::cout << entity_mob->GetBaseId()<< std::endl;
        //     std::cout << "test" << std::endl;
        if (entity_mob->GetBaseId() > 1000 && entity_mob->GetBaseId() < 1152)
        {
            std::shared_ptr<C_TextMessage<std::string>> name = entity_mob->template GetComponent<C_TextMessage<std::string>>();
            std::shared_ptr<C_Experience<int>> xp = entity_mob->template GetComponent<C_Experience<int>>();
            for (const std::shared_ptr<IEntity>& entity_mob_2 : arg_scene->entities_) {
                if (entity_mob_2->GetBaseId() == 502)
                {
                    std::shared_ptr<C_TextMessage<std::string>> display_name = entity_mob_2->template GetComponent<C_TextMessage<std::string>>();
                    display_name->setValue(name->getValue());
                }
                if (entity_mob_2->GetBaseId() == 507)
                {
                    std::shared_ptr<C_TextMessage<std::string>> display_level = entity_mob_2->template GetComponent<C_TextMessage<std::string>>();
                    display_level->setValue("Lv" + std::to_string(xp->getValue() / 100));
                }
            }
        }
        if (entity_mob->GetBaseId() == 506)
        {
            std::shared_ptr<C_TextMessage<std::string>> display_level = entity_mob->template GetComponent<C_TextMessage<std::string>>();
            display_level->setValue("Lv" + std::to_string(level));
        }
    }
}