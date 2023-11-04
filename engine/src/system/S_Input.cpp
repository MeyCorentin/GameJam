#include "system/S_Input.hpp"

std::vector<std::shared_ptr<Entity>> S_Input::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Player<int>)) &&
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_IsMoving<bool>)) &&
            entity->HasComponent(typeid(C_Admin<bool>)) &&
            entity->HasComponent(typeid(C_Weapon<std::pair<int, int>>)) &&
            entity->HasComponent(typeid(C_ChargedShoot<sf::Clock>))
            ) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

json S_Input::FindComponentConfigById(const json& arg_components_config, int arg_id) {
    static json empty_json;

    for (auto component_config : arg_components_config)
        if (component_config["id"] == arg_id)
            return component_config;
    return empty_json;
}   

bool S_Input::ProcessComponent(
        const json& arg_entityComponent,
        const json& arg_componentConfig,
        JsonParser& arg_parser,
        EntityBuilder& arg_entityBuilder) {
    std::string component_name = arg_componentConfig["type"];
    std::string value_type = arg_componentConfig["value_type"];
    json component_value = arg_entityComponent["value"];
    std::shared_ptr<ComponentBase> component = ComponentRegistry::Instance().CreateComponent(component_name);
    Variant value = arg_parser.ParseValue(value_type, component_value);

    if (!component)
        return false;

    // std::cout << " - " << component_name << std::endl;
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
        arg_entityBuilder.AddComponent(component, std::get<std::vector<std::shared_ptr<Entity>>>(value));
    } else if (value_type == "SinFunc") {
        arg_entityBuilder.AddComponent(component, std::get<SinusoidalFunction>(value));
    } else if (value_type == "Sound") {
        arg_entityBuilder.AddComponent(component, std::get<sf::Sound>(value));
    } else if (value_type == "SoundBuffer") {
        arg_entityBuilder.AddComponent(component, std::get<sf::SoundBuffer>(value));
    } else if (value_type == "String") {
        arg_entityBuilder.AddComponent(component, std::get<std::string>(value));
    } else {
        std::cerr << "Unsupported component type: " << value_type << std::endl;
        return false;
    }
    return true;
}

std::shared_ptr<Entity> S_Input::CreateEntityFromConfig(
        const json& arg_entity_config,
        const json& arg_components_config) {
    JsonParser parser;
    json component_config;
    int component_id;
    int entity_id = arg_entity_config["id"];
    EntityBuilder entity_builder(entity_id);
    const json& entity_components = arg_entity_config["components"];

    // std::cout << "Create Entity: " << entity_id << std::endl;
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

std::shared_ptr<Entity> S_Input::createEntity(
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        int id,
        std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp) {
    std::shared_ptr<Entity> new_entity;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_new;
    std::string filepath = "../../rtype/scene_test.json";
    std::ifstream file(filepath);
    json data;

    file >> data;
    file.close();
    for (const auto& entity_config : data["entities"]) {
        if (entity_config["id"] == id) {
            new_entity = CreateEntityFromConfig(entity_config, data["components"]);
            position_new = new_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            std::shared_ptr<C_PositionShot<std::pair<double, double>>> position_shot = new_entity->template GetComponent<C_PositionShot<std::pair<double, double>>>();
            std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
            std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
            sprite->getValue().setTextureRect(rect->getValue());
            // std::cout << position_shot->getValue().first << std::endl;
            position_new->setValue(std::make_pair(arg_position_comp->getValue().first + position_shot->getValue().first, arg_position_comp->getValue().second + position_shot->getValue().second));
            arg_all_entities.push_back(new_entity);
        }
    }
    return new_entity;
}

void DrawEntityID(
    std::shared_ptr<sf::RenderWindow> arg_window,
    const std::shared_ptr<Entity>& entity,
    sf::Font arg_font,
    sf::Text arg_entity_id) {
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
    if (position_comp)
    {
        arg_entity_id.setPosition(position_comp->getValue().first, position_comp->getValue().second);
        arg_entity_id.setString(std::to_string(entity->GetId()));
        arg_window->draw(arg_entity_id);
    }
}


void DrawEntityHitbox(
    std::shared_ptr<sf::RenderWindow> arg_window,
    const std::shared_ptr<Entity>& entity,
    sf::Color outlineColor) {
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_comp = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
    sf::RectangleShape hitbox;
    hitbox.setPosition(position_comp->getValue().first, position_comp->getValue().second);
    hitbox.setSize(sf::Vector2f(hitbox_comp->getValue().first, hitbox_comp->getValue().second));
    hitbox.setFillColor(sf::Color::Transparent);
    hitbox.setOutlineColor(outlineColor);
    hitbox.setOutlineThickness(1.0f);
    arg_window->draw(hitbox);
}


void S_Input::Move(
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp, 
    std::shared_ptr<sf::RenderWindow> arg_window,
    const std::shared_ptr<Entity>& entity,
    std::vector<std::shared_ptr<Entity>>& arg_entities,
    sf::Font arg_font,
    sf::Text arg_entity_id)
{
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();


    if (inputs_[0] == 1)
    {
        if (position_comp->getValue().second > 5)
            position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second - 5));
    }
    if (inputs_[1] == 1)
    {
        if (position_comp->getValue().first > 5)
            position_comp->setValue(std::make_pair(position_comp->getValue().first - 5, position_comp->getValue().second));
    }
    if (inputs_[2] == 1)
    {
        if (position_comp->getValue().second < arg_window->getSize().y - 5 - hitbox_size->getValue().second)
            position_comp->setValue(std::make_pair(position_comp->getValue().first, position_comp->getValue().second  + 5));
    }
    if (inputs_[3] == 1)
    {
        if (position_comp->getValue().first < arg_window->getSize().x - 5- hitbox_size->getValue().first)
            position_comp->setValue(std::make_pair(position_comp->getValue().first + 5, position_comp->getValue().second));
    }
    if (inputs_[5] == 1)
    {
        for (const std::shared_ptr<Entity>& entity : arg_entities) {
            std::shared_ptr<C_Player<int>> is_player = entity->template GetComponent<C_Player<int>>();
            std::shared_ptr<C_PlayerAmmo<bool>> is_player_ammo = entity->template GetComponent<C_PlayerAmmo<bool>>();
            std::shared_ptr<C_Bonus<bool>> is_bonus =  entity->template GetComponent<C_Bonus<bool>>();
            std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_comp = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
            sf::Color outlineColor;
            if (!hitbox_comp || !position_comp)
                continue;
            if (is_player || is_player_ammo) {
                outlineColor = sf::Color::Green;
            }
            else if (is_bonus) {
                outlineColor = sf::Color::Blue;
            }
            else {
                outlineColor = sf::Color::Red;
            }
            DrawEntityHitbox(arg_window, entity, outlineColor);
            DrawEntityID(arg_window, entity, arg_font, arg_entity_id);
        }

    }
}

void S_Input::ChangeAdminMode(
    const std::shared_ptr<Entity>& entity,
    std::shared_ptr<sf::Event> event_)
{
    std::shared_ptr<C_Life<int>> life = entity->template GetComponent<C_Life<int>>();
    std::shared_ptr<C_Admin<bool>> is_admin = entity->template GetComponent<C_Admin<bool>>();

    if (event_->key.code == sf::Keyboard::A) {
        if (is_admin->getValue()) {
            life->getValue() = 1;
            is_admin->getValue() = false;
        } else {
            life->getValue() = -1;
            is_admin->getValue() = true;
        }
    }
}

void S_Input::BasicShot(
    const std::shared_ptr<Entity>& entity,
    std::vector<std::shared_ptr<Entity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp)
{
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();

    if (clock->getValue().getElapsedTime().asSeconds() > 1)
        createEntity(arg_all_entities, 9, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.6)
        createEntity(arg_all_entities, 8, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.4)
        createEntity(arg_all_entities, 7, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.2)
        createEntity(arg_all_entities, 6, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.1)
        createEntity(arg_all_entities, 5, position_comp);
    else
        createEntity(arg_all_entities, 3, position_comp);
}

void S_Input::SpecialShot(
    const std::shared_ptr<Entity>& entity,
    std::vector<std::shared_ptr<Entity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp)
{
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<Entity>>>> vector_entities = entity->template GetComponent<C_Inventory<std::vector<std::shared_ptr<Entity>>>>();

    //Player attacks
    std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon_player = entity->template GetComponent<C_Weapon<std::pair<int, int>>>();

    std::list<int> my_list_1 = {22, 23, 24};
    std::list<int> my_list_2 = {38, 39, 40};
    std::list<int> my_list_3 = {4, 29};

    for (std::shared_ptr<Entity>& v_entity: vector_entities->getValue()) {
        if ((std::find(my_list_1.begin(), my_list_1.end(), v_entity->GetId()) != my_list_1.end())) {
            std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
            std::shared_ptr<C_Position<std::pair<double, double>>> position_force = v_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            if (weapon->getValue().first != -1) {
                if (weapon->getValue().first == 25) {
                    for (int i = 0; i < 1; i++) { //TODO Set to 5
                        createEntity(arg_all_entities, weapon->getValue().first, position_force);
                        createEntity(arg_all_entities, 32, position_force); //TODO Change that
                    }
                }
                if (weapon->getValue().first == 26) {
                    createEntity(arg_all_entities, weapon->getValue().first, position_force);
                }
            }
        }
        if ((std::find(my_list_2.begin(), my_list_2.end(), v_entity->GetId()) != my_list_2.end())) {
            std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
            std::shared_ptr<C_Position<std::pair<double, double>>> position_force = v_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            if (weapon->getValue().second != -1) {
                if (weapon->getValue().second == 32) {
                    for (int i = 0; i < 1; i++) { //TODO Set to 5
                        createEntity(arg_all_entities, weapon->getValue().second, position_force);
                        createEntity(arg_all_entities, 25, position_force); //TODO Change that
                    }
                }
                if (weapon->getValue().second == 43) {
                    createEntity(arg_all_entities, weapon->getValue().second, position_force);
                }
            }
        }
    }

    //Drone attacks
    for (std::shared_ptr<Entity>& v_entity: vector_entities->getValue()) { //Check if vector_entities contain a drone left or right
        if (v_entity->GetId() == 27)
            v_entity->is_dead_ = true;
        if ((std::find(my_list_3.begin(), my_list_3.end(), v_entity->GetBaseId()) != my_list_3.end()) && weapon_player->getValue().first == 26) {
            std::shared_ptr<C_Position<std::pair<double, double>>> position_drone = v_entity->template GetComponent<C_Position<std::pair<double, double>>>();
            std::shared_ptr<C_Weapon<std::pair<int, int>>> weapon = v_entity->template GetComponent<C_Weapon<std::pair<int, int>>>();
            for (std::shared_ptr<Entity>& v_entity: vector_entities->getValue()) {
                if ((std::find(my_list_1.begin(), my_list_1.end(), v_entity->GetId()) != my_list_1.end())) {
                    createEntity(arg_all_entities, weapon->getValue().first, position_drone);
                }
            }
            for (std::shared_ptr<Entity>& v_entity: vector_entities->getValue()) {
                if ((std::find(my_list_2.begin(), my_list_2.end(), v_entity->GetId()) != my_list_2.end())) {
                    createEntity(arg_all_entities, weapon->getValue().second, position_drone);
                }
            }
        }
    }
}

void S_Input::CheckTouchPressed(
    const std::shared_ptr<Entity>& entity,
    std::vector<std::shared_ptr<Entity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    std::shared_ptr<sf::Event> event_)
{
    std::shared_ptr<C_ShootCharging<bool>> is_charging = entity->template GetComponent<C_ShootCharging<bool>>();
    std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
    std::shared_ptr<C_Sprite<sf::Sprite>> sprite = entity->template GetComponent<C_Sprite<sf::Sprite>>();
    std::shared_ptr<C_IsMoving<bool>> moving = entity->template GetComponent<C_IsMoving<bool>>();
    std::shared_ptr<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>> size = entity->template GetComponent<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>();
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<Entity>>>> vector_entities = entity->template GetComponent<C_Inventory<std::vector<std::shared_ptr<Entity>>>>();
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();

    if (event_->type == sf::Event::KeyPressed) {
        if (event_->key.code == sf::Keyboard::Up) {
            inputs_[0] = 1;
            if (moving->getValue() == false) {
                moving->getValue() = true;
                rect->getValue().left = size->getValue().second.first + (rect->getValue().width * 2);
                sprite->getValue().setTextureRect(rect->getValue());
            }
        }
        if (event_->key.code == sf::Keyboard::Left)
            inputs_[1] = 1;
        if (event_->key.code == sf::Keyboard::Down) {
            inputs_[2] = 1;
            if (moving->getValue() == false) {
                moving->getValue() = true;
                rect->getValue().left = size->getValue().second.first - (rect->getValue().width * 2);
                sprite->getValue().setTextureRect(rect->getValue());
            }
        }
        if (event_->key.code == sf::Keyboard::Right)
            inputs_[3] = 1;
        if (event_->key.code == sf::Keyboard::Space) {
            if (is_charging->getValue() == false) {
                clock->getValue().restart();
                vector_entities->getValue().push_back(createEntity(arg_all_entities, 27, position_comp));
                is_charging->getValue() = true;
            }
        }
        if (event_->key.code == sf::Keyboard::Z && inputs_[5] == 1)
            inputs_[5] = 0;
        else if (event_->key.code == sf::Keyboard::Z && inputs_[5] == 0)
            inputs_[5] = 1;
    }
}

void S_Input::CheckTouchReleased(
    const std::shared_ptr<Entity>& entity,
    std::vector<std::shared_ptr<Entity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    std::shared_ptr<sf::Event> event_)
{
    std::shared_ptr<C_ShootCharging<bool>> is_charging = entity->template GetComponent<C_ShootCharging<bool>>();
    std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
    std::shared_ptr<C_Sprite<sf::Sprite>> sprite = entity->template GetComponent<C_Sprite<sf::Sprite>>();
    std::shared_ptr<C_IsMoving<bool>> moving = entity->template GetComponent<C_IsMoving<bool>>();
    std::shared_ptr<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>> size = entity->template GetComponent<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>();
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();

    if (event_->type == sf::Event::KeyReleased) {
        if (event_->key.code == sf::Keyboard::Up) {
            inputs_[0] = 0;
            moving->getValue() = false;
            rect->getValue().left = size->getValue().second.first;
            sprite->getValue().setTextureRect(rect->getValue());
        }
        if (event_->key.code == sf::Keyboard::Left)
            inputs_[1] = 0;
        if (event_->key.code == sf::Keyboard::Down) {
            inputs_[2] = 0;
            moving->getValue() = false;
            rect->getValue().left = size->getValue().second.first;
            sprite->getValue().setTextureRect(rect->getValue());
        }
        if (event_->key.code == sf::Keyboard::Right)
            inputs_[3] = 0;
        if (event_->key.code == sf::Keyboard::Space) {
            BasicShot(entity, arg_all_entities, position_comp);
            SpecialShot(entity, arg_all_entities, position_comp);
            is_charging->getValue() = false;
        }
        ChangeAdminMode(entity, event_);
    }
}

void S_Input::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
        std::shared_ptr<sf::Event> event_)  {
    sf::Font font_arg_;
    font_arg_.loadFromFile("../../rtype/sources/fonts/arial.ttf");
    sf::Text entity_id;
    entity_id.setFillColor(sf::Color::Magenta);
    entity_id.setCharacterSize(10);
    entity_id.setFont(font_arg_);
    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        std::shared_ptr<C_Position<std::pair<double, double>>> position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        std::shared_ptr<C_Player<int>> player_id =  entity->template GetComponent<C_Player<int>>();
        if (arg_is_server == 1)
            continue;
        if (!player_id)
            continue;
        if (&entity != &arg_entities.front())
            continue;
        while (arg_window->pollEvent(*event_)) {
            if (event_->type == sf::Event::Closed)
                arg_window->close();
            CheckTouchPressed(entity, arg_all_entities, position_comp, event_);
            CheckTouchReleased(entity, arg_all_entities, position_comp, event_);
        }
        Move(position_comp, arg_window, entity, arg_all_entities, font_arg_, entity_id);
    }
}