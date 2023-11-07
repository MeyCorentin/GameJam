#include "scene/Scene.hpp"


template <typename T>
T Scene::getRandomInRange(T min, T max)
{
    if (max <= min)
        return min;

    std::mt19937_64 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<long long> distribution(min, max);

    T nbr = (T)distribution(gen);

    return nbr;
}

std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> Scene::CreateMap(const json& arg_spawn_config)
{
    std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> map;
    for (const auto& spawn_entry : arg_spawn_config)
    {
        int tick = spawn_entry.at("tick").get<int>();
        std::vector<std::pair<int, std::pair<int, int>> > entities;

        if (spawn_entry.find("mob_id") == spawn_entry.end())
            continue;
        for (const auto& entity : spawn_entry.at("mob_id"))
        {
            int id_value = entity.at("entity_id").get<int>();
            int x;
            int y;
            if (entity.find("position") != entity.end())
            {
                x = entity.at("position").at("x").get<int>();
                y = entity.at("position").at("y").get<int>();
            } else {
                x = 384;
                y = Scene::getRandomInRange(0,180);
            }
            entities.push_back(std::make_pair(id_value, std::make_pair(x, y)));
        }

        map.push_back(std::make_pair(tick, entities));
    }
    return map;
}


std::vector<std::pair<int,int>> Scene::CreateJump(const json& arg_spawn_config)
{
    std::vector<std::pair<int, int>> jump;
    for (const auto& spawn_entry : arg_spawn_config)
    {


        if (spawn_entry.find("jump") == spawn_entry.end())
            continue;
        int tick = spawn_entry.at("tick").get<int>();
        int jump_value = spawn_entry.at("jump").get<int>();

        jump.push_back(std::make_pair(tick, jump_value));
    }
    return jump;
}

void Scene::LoadSettings() {
    std::string directory = filepath_.substr(0, filepath_.find_last_of("/\\"));

    std::string settings_file_path = directory + "/settings.json";

    std::ifstream settings_file(settings_file_path);
    json settings_data;

    settings_file >> settings_data;
    settings_file.close();

    std::string window_name = settings_data["settings"]["name"];
    int window_x = settings_data["settings"]["window"]["x"];
    int window_y = settings_data["settings"]["window"]["y"];

    window_ = std::shared_ptr<sf::RenderWindow>(new sf::RenderWindow(sf::VideoMode(window_x, window_y), window_name));
}

Scene::Scene() {}
Scene::Scene( std::vector<std::shared_ptr<ISystem>> arg_system_list,
        std::vector<std::shared_ptr<IEntity>> arg_entity_list,
        std::vector<sf::Sprite> arg_sprite_list,
        std::vector<std::shared_ptr<sf::Music>> arg_music_list,
        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> arg_spawn_index,
        std::vector<std::pair<int,int>> arg_jump_index,
        std::string arg_file_path) :
    systems_(arg_system_list),
    list_entities_(arg_entity_list),
    sprites_(arg_sprite_list),
    musics_(arg_music_list),
    spawn_index_(arg_spawn_index),
    jump_index_(arg_jump_index),
    filepath_(arg_file_path)  {
        LoadSettings();
        frames_this_second_ = 0;
        total_ticks_ = 0;
        event_ = std::shared_ptr<sf::Event>(new sf::Event());
        second_clock_ = std::shared_ptr<sf::Clock>(new sf::Clock());
        entities_nbr_ = std::shared_ptr<sf::Text>(new sf::Text());
        font_ = std::shared_ptr<sf::Font>(new sf::Font());
        font_->loadFromFile("../../rtype/sources/fonts/r-type.ttf");
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

        std::ifstream file(filepath_);
        std::pair<double, double> direction;
        double length;
        file >> data_;
        file.close();
    }

void Scene::ClearWindow()
{
    window_->clear();
}

std::vector<std::shared_ptr<IEntity>> Scene::GetEntities()
{
    return  entities_;
}

std::vector<std::shared_ptr<ISystem>> Scene::GetSystems()
{
    return systems_;
}

void Scene::DisplayCurrentTick() {
    total_ticks_++;
    std::string tick_string;

    tick_string = std::to_string(total_ticks_) + " ticks";
    current_tick_->setString(tick_string);
    window_->draw(*current_tick_);
}

void Scene::DisplayEntities(int nbr) {
    std::string nbr_string = std::to_string(nbr) + " enttities";

    this->entities_nbr_->setString(nbr_string);
    window_->draw(*entities_nbr_);
}

void Scene::DisplayTicks() {
    int &ref = frames_this_second_;
    std::string tick_string;

    ref += 1;
    if (second_clock_->getElapsedTime().asSeconds() >= 1.0) {
        tick_string = std::to_string(ref) + " t/s";
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
            entities_.push_back(std::make_shared<IEntity>(*entity));
            index = entities_.back() ->template GetComponent<C_Player<int>>();
            index->setValue(arg_id);
            std::cout << index->getValue() << std::endl;
        }
    }
}


json Scene::FindComponentConfigById(const json& arg_components_config, int arg_id) {
    static json empty_json;

    for (auto component_config : arg_components_config)
        if (component_config["id"] == arg_id)
            return component_config;
    return empty_json;
}

bool Scene::ProcessComponent(
        const json& arg_entityComponent,
        const json& arg_componentConfig,
        JsonParser& arg_parser,
        EntityBuilder& arg_entityBuilder) {
    std::string component_name = arg_componentConfig["type"];
    std::string value_type = arg_componentConfig["value_type"];
    json component_value = arg_entityComponent["value"];
    std::shared_ptr<IComponent> component = ComponentRegistry::Instance().CreateComponent(component_name);
    Variant value = arg_parser.ParseValue(value_type, component_value);

    if (!component)
        return false;

    if (value_type == "Sprite") {
        arg_entityBuilder.AddComponent(component,  std::get<sf::Sprite>(value));
    } else if (value_type == "Int") {
        arg_entityBuilder.AddComponent(component, std::get<int>(value));
    } else if (value_type == "Texture") {
        arg_entityBuilder.AddComponent(component, std::get<sf::Texture>(value));
    } else if (value_type == "PairDouble") {
        arg_entityBuilder.AddComponent(component, std::get<std::pair<double, double>>(value));
    } else if (value_type == "PairInt") {
        arg_entityBuilder.AddComponent(component, std::get<std::pair<int, int>>(value));
    } else if (value_type == "Bool") {
        arg_entityBuilder.AddComponent(component, std::get<bool>(value));
    } else if (value_type == "Double") {
        arg_entityBuilder.AddComponent(component, std::get<double>(value));
    } else if (value_type == "Clock") {
        arg_entityBuilder.AddComponent(component, std::get<sf::Clock>(value));
    } else if (value_type == "IntRect") {
        arg_entityBuilder.AddComponent(component, std::get<sf::IntRect>(value));
    } else if (value_type == "PairPairInt") {
        arg_entityBuilder.AddComponent(component, std::get<std::pair<std::pair<int, int>, std::pair<int, int>>>(value));
    } else if (value_type == "VectorEntity") {
        arg_entityBuilder.AddComponent(component, std::get<std::vector<std::shared_ptr<IEntity>>>(value));
    } else if (value_type == "SinFunc") {
        arg_entityBuilder.AddComponent(component, std::get<SinusoidalFunction>(value));
    } else if (value_type == "Sound") {
        arg_entityBuilder.AddComponent(component, std::get<sf::Sound>(value));
    } else if (value_type == "SoundBuffer") {
        arg_entityBuilder.AddComponent(component, std::get<sf::SoundBuffer>(value));
    } else if (value_type == "Text") {
        arg_entityBuilder.AddComponent(component, std::get<sf::Text>(value));
    } else if (value_type == "String") {
        arg_entityBuilder.AddComponent(component, std::get<std::string>(value));
    } else {
        std::cerr << "Unsupported component type: " << value_type << std::endl;
        return false;
    }
    return true;
}

std::shared_ptr<IEntity> Scene::CreateEntityFromConfig(
        const json& arg_entity_config,
        const json& arg_components_config) {
    JsonParser parser;
    json component_config;
    int component_id;
    int entity_id = arg_entity_config["id"];
    EntityBuilder entity_builder(entity_id);
    const json& entity_components = arg_entity_config["components"];

    for (const auto& entity_component : entity_components) {
        component_id = entity_component["component_id"];
        component_config = FindComponentConfigById(arg_components_config, component_id);
        if (component_config.is_null())
            return entity_builder.Build();
        if (!ProcessComponent(entity_component, component_config, parser, entity_builder))
            return entity_builder.Build();
    }
    return entity_builder.Build();
}

void Scene::LoadTimeline(
    const std::string& timeline_id)
{

    std::string directory = filepath_.substr(0, filepath_.find_last_of("/\\"));
    std::string timeline_file_path;
    for (const auto& timeline : data_["timeline"]) {
        if (timeline.find(timeline_id) != timeline.end()) {
            timeline_file_path = directory + "/" + timeline[timeline_id].get<std::string>();
            std::ifstream timeline_file(timeline_file_path);
            json timeline_data;
            timeline_file >> timeline_data;
            timeline_file.close();

            spawn_index_ = CreateMap(timeline_data["spawn"]);
            jump_index_ = CreateJump(timeline_data["spawn"]);
            total_ticks_ = 0;
            second_clock_->restart();
            id_store_ = 0;
            entities_.clear();
            break;
        }
    }
}

std::shared_ptr<IEntity> Scene::createEntity(
        std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
        int id,
        std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp) {
    std::shared_ptr<IEntity> new_entity;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
    std::ifstream file(filepath_);
    json data;

    file >> data;
    file.close();
    for (const auto& entity_config : data["entities"]) {
        if (entity_config["id"] == id) {

            new_entity = CreateEntityFromConfig(entity_config, data["components"]);
            new_entity->SetBaseId(entity_config["id"]);
            position_new = new_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            std::shared_ptr<C_PositionShot<std::pair<double, double>>> position_shot = new_entity->template GetComponent<C_PositionShot<std::pair<double, double>>>();
            std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
            std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
            sprite->getValue().setTextureRect(rect->getValue());
            position_new->setValue(std::make_pair(arg_position_comp->getValue().first + position_shot->getValue().first, arg_position_comp->getValue().second + position_shot->getValue().second));
            arg_all_entities.push_back(new_entity);
        }
    }
    return new_entity;
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
    for (const std::shared_ptr<IEntity>& entity : entities_) {
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
    for (const std::shared_ptr<IEntity>& entity : entities_) {
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
    messages_.push_back(arg_message);
}

void Scene::CheckSwitchTimeline() {
    if (need_switch_) {
        LoadTimeline(next_timeline_);
        need_switch_ = false;
    }
}

void Scene::Update(int arg_is_server)
{
    this->ClearWindow();

    ComputeSystems(arg_is_server);

    std::vector<std::shared_ptr<IEntity>> newEntities = SpawnEntities(arg_is_server);

    for (const auto& newEntity : newEntities) {
        entities_.push_back(newEntity);
    }

    JumpTicks();
    DisplayTicks();
    DisplayEntities(entities_.size());
    DisplayCurrentTick();
    RemoveOrCreateEntities();
    window_->display();
    CheckSwitchTimeline();
}

void Scene::ComputeSystems(int arg_is_server)
{
    Scene* scene_ptr = this; 
    for (const auto& system : systems_)
        system->Compute(arg_is_server, scene_ptr);
}

std::vector<std::shared_ptr<IEntity>> Scene::SpawnEntities(int arg_is_server)
{
    std::vector<std::shared_ptr<IEntity>> newEntities;

    std::shared_ptr<C_Position<std::pair<double,double>>> position;
    std::shared_ptr<C_SinClock<sf::Clock>> sin_clock;
    std::shared_ptr<C_Clock<sf::Clock>> clock_basic;
    std::shared_ptr<C_ParallaxClock<sf::Clock>> parallax_clock;
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
                std::shared_ptr<IEntity> newEntity = std::make_shared<IEntity>(*entity);
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

                parallax_clock = newEntity->template GetComponent<C_ParallaxClock<sf::Clock>>();
                if (parallax_clock)
                    parallax_clock->getValue().restart();

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