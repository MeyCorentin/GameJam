#include "scene/Scene.hpp"


Scene::Scene() {}
Scene::Scene( std::vector<std::shared_ptr<System>> arg_system_list,
        std::vector<std::shared_ptr<Entity>> arg_entity_list,
        std::vector<sf::Sprite> arg_sprite_list,
        std::vector<std::shared_ptr<sf::Music>> arg_music_list,
        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> arg_spawn_index,
        std::vector<std::pair<int,int>> arg_jump_index) :
    systems_(arg_system_list),
    list_entities_(arg_entity_list),
    sprites_(arg_sprite_list),
    musics_(arg_music_list),
    spawn_index_(arg_spawn_index),
    jump_index_(arg_jump_index)  {
        window_ = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(384, 256), "R-Type"));
        frames_this_second_ = 0;
        total_ticks_ = 0;
        event_ = std::shared_ptr<sf::Event>(new sf::Event());
        second_clock_ = std::shared_ptr<sf::Clock>(new sf::Clock());
        entities_nbr_ = std::shared_ptr<sf::Text>(new sf::Text());
        font_ = std::shared_ptr<sf::Font>(new sf::Font());
        font_->loadFromFile("../../rtype/sources/fonts/arial.ttf");
        tick_ = std::shared_ptr<sf::Text>(new sf::Text());
        tick_->setPosition(0, 0);
        tick_->setFillColor(sf::Color::White);
        tick_->setCharacterSize(10),
        tick_->setFont(*font_);

        entities_nbr_->setPosition(0, 11);
        entities_nbr_->setFillColor(sf::Color::White);
        entities_nbr_->setCharacterSize(10),
        entities_nbr_->setFont(*font_);


        current_tick_ = std::shared_ptr<sf::Text>(new sf::Text());
        current_tick_->setPosition(0, 22);
        current_tick_->setFillColor(sf::Color::White);
        current_tick_->setCharacterSize(10),
        current_tick_->setFont(*font_);

        for (int i = 0; i < sf::Keyboard::KeyCount; ++i) {
            key_states_[static_cast<sf::Keyboard::Key>(i)] = false;
        }
    }

void Scene::ClearWindow()
{
    window_->clear();
}

std::vector<std::shared_ptr<Entity>> Scene::GetEntities()
{
    return  entities_;
}

std::vector<std::shared_ptr<System>> Scene::GetSystems()
{
    return systems_;
}

void Scene::DisplayCurrentTick() {
    int &ref = total_ticks_;
    std::string tick_string;

    ref += 1;
    tick_string = std::to_string(ref) + " (ticks)";
    current_tick_->setString(tick_string);
    window_->draw(*current_tick_);
}

void Scene::DisplayEntities(int nbr) {
    std::string nbr_string = std::to_string(nbr) + " (enttities)";

    this->entities_nbr_->setString(nbr_string);
    window_->draw(*entities_nbr_);
}

void Scene::DisplayTicks() {
    int &ref = frames_this_second_;
    std::string tick_string;

    ref += 1;
    if (second_clock_->getElapsedTime().asSeconds() >= 1.0) {
        tick_string = std::to_string(ref) + " (t/s)";
        tick_->setString(tick_string);
        ref= 0;
        second_clock_->restart();
    }
    window_->draw(*tick_);
}


void Scene::AddNewPlayer(int arg_id)
{
    for (const auto& entity : list_entities_) {
        if (entity->GetId() == 1)
        {
            std::shared_ptr<C_Player<int>> index;
            entities_.push_back(std::make_shared<Entity>(*entity));
            index = entities_.back() ->template GetComponent<C_Player<int>>();
            index->setValue(arg_id);
            std::cout << index->getValue() << std::endl;
        }
    }
}


std::vector<EntityPosition> Scene::GetPlayerPosition()
{
    std::vector<EntityPosition> positions;
    std::shared_ptr<C_Player<int>> index;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
    EntityPosition pos;

    for (const auto& entity : entities_) {
        index = entity->template GetComponent<C_Player<int>>();
        position_comp =  entity->template GetComponent<C_Position<std::pair<double, double>>>();
        if (index && position_comp) {
            pos.id = index->getValue();
            pos.base_id = entity->GetBaseId();
            pos.x_position = position_comp->getValue().first;
            pos.y_position = position_comp->getValue().second;
            positions.push_back(pos);
        }
    }
    return positions;
}


std::vector<EntityPosition> Scene::GetEntityPosition()
{
    std::vector<EntityPosition> positions;
    for (const auto& entity : entities_) {
        std::shared_ptr<C_Player<int>> index = entity->template GetComponent<C_Player<int>>();
        std::shared_ptr<C_Position<std::pair<double, double>>> position_comp =  entity->template GetComponent<C_Position<std::pair<double, double>>>();
        if (!index && position_comp) {
            EntityPosition pos;
            pos.id = entity->GetId();
            pos.base_id = entity->GetBaseId();
            pos.x_position = position_comp->getValue().first;
            pos.y_position = position_comp->getValue().second;
            positions.push_back(pos);
        }
    }
    return positions;
}


void Scene::SetClientPlayerId(int arg_id)
{
    std::shared_ptr<C_Player<int>> index;
    for (const std::shared_ptr<Entity>& entity : entities_) {
        index = entity->template GetComponent<C_Player<int>>();
        if (!index)
            continue;
        index->setValue(arg_id);
    }
}

void Scene::SetPlayerPosition(int arg_id, float arg_x, float arg_y)
{
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size;
    std::shared_ptr<C_Player<int>> index;
    for (const std::shared_ptr<Entity>& entity : entities_) {
        index = entity->template GetComponent<C_Player<int>>();
        if (!index)
            continue;
        if (index->getValue() != arg_id)
            continue;
        position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        position_comp->setValue(std::make_pair(arg_x, arg_y));
    }
}

void Scene::InputFromPlayer(std::pair<int,int> arg_message)
{
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size;
    std::shared_ptr<C_Player<int>> index;
    for (const std::shared_ptr<Entity>& entity : entities_) {
        index = entity->template GetComponent<C_Player<int>>();
        if (!index)
            continue;
        if (index->getValue() != arg_message.first)
            continue;
        position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        hitbox_size = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();
        if (!position_comp)
            continue;
        if (arg_message.second == 0 || arg_message.second == 100)
            continue;
        switch (arg_message.second) {
            case 200: // Up
                if (position_comp->getValue().second > 5)
                    position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second - 5));
                break;
            case 210: // Left
                if (position_comp->getValue().first > 5)
                    position_comp->setValue(std::make_pair(position_comp->getValue().first - 5, position_comp->getValue().second));
                break;
            case 220: // Down
                if (position_comp->getValue().second <  window_->getSize().y - 5 - hitbox_size->getValue().second)
                    position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second + 5));
                break;
            case 230: // Right
                if (position_comp->getValue().first < window_->getSize().x - 5- hitbox_size->getValue().first)
                    position_comp->setValue(std::make_pair(position_comp->getValue().first + 5, position_comp->getValue().second));
                break;
            case 300: // Shoot
                break;
            default:
                std::cerr << "Unknown message data: " << arg_message.second << std::endl;
                break;
        }
    }
}

void Scene::Update(int arg_is_server)
{
    this->ClearWindow();

    ComputeSystems(arg_is_server);

    std::vector<std::shared_ptr<Entity>> newEntities = SpawnEntities(arg_is_server);

    for (const auto& newEntity : newEntities) {
        entities_.push_back(newEntity);
    }

    JumpTicks();
    DisplayTicks();
    DisplayEntities(entities_.size());
    DisplayCurrentTick();
    RemoveOrCreateEntities();
    window_->display();
}
void Scene::ComputeSystems(int arg_is_server)
{
    for (const auto& system : systems_)
        system->Compute(arg_is_server, entities_, window_, inputs_, musics_, event_);
}
std::vector<std::shared_ptr<Entity>> Scene::SpawnEntities(int arg_is_server)
{
    std::vector<std::shared_ptr<Entity>> newEntities;

    std::shared_ptr<C_Position<std::pair<double,double>>> position;
    std::shared_ptr<C_SinClock<sf::Clock>> sin_clock;
    std::shared_ptr<C_Clock<sf::Clock>> clock_basic;
    int entity_id;
    int x;
    int y;

    for (const auto& spawn_info : spawn_index_)
    {
        if (spawn_info.first != total_ticks_)
            continue;

        for (const auto& entity_info : spawn_info.second)
        {
            entity_id = entity_info.first;
            x = entity_info.second.first;
            y = entity_info.second.second;

            for (const auto& entity : list_entities_)
            {
                if (entity_id != entity->GetId())
                    continue;
                if (entity->GetId() == arg_is_server)
                    continue;
                std::shared_ptr<Entity> newEntity = std::make_shared<Entity>(*entity);
                newEntity->SetId(id_store_++);
                newEntity->SetBaseId(entity->GetId());
                position = newEntity->template GetComponent<C_Position<std::pair<double,double>>>();
                position->setValue(std::make_pair(x,y));

                sin_clock = newEntity->template GetComponent<C_SinClock<sf::Clock>>();
                if (sin_clock)
                    sin_clock->getValue().restart();

                clock_basic = newEntity->template GetComponent<C_Clock<sf::Clock>>();
                if (clock_basic)
                    clock_basic->getValue().restart();

                newEntities.push_back(newEntity);
            }
        }
    }

    return newEntities;
}

void Scene::JumpTicks()
{
    for (const auto& jump_info : jump_index_)
    {
        if (jump_info.first == total_ticks_)
            total_ticks_ = jump_info.second;
    }
}

void Scene::RemoveOrCreateEntities()
{
    auto it = entities_.begin();
    while (it != entities_.end())
    {
        if ((*it)->is_dead_)
        {
            it = entities_.erase(it);
        }
        else
        {
            if ((*it)->GetId() == -1)
            {
                (*it)->SetId(id_store_++);
            }
            ++it;
        }
    }
}