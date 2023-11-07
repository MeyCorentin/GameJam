#include "system/S_BasicInput.hpp"

std::vector<std::shared_ptr<IEntity>> S_BasicInput::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Player<int>)) &&
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_IsMoving<bool>)) &&
            entity->HasComponent(typeid(C_Admin<bool>)) &&
            entity->HasComponent(typeid(C_Weapon<std::pair<int, int>>)) &&
            entity->HasComponent(typeid(C_ChargedShoot<sf::Clock>)) &&
            entity->HasComponent(typeid(C_PlayerMovementClock<sf::Clock>)) 
            ) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_BasicInput::DrawEntityID(
    std::shared_ptr<sf::RenderWindow> arg_window,
    const std::shared_ptr<IEntity>& entity,
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


void S_BasicInput::DrawEntityHitbox(
    std::shared_ptr<sf::RenderWindow> arg_window,
    const std::shared_ptr<IEntity>& entity,
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


void S_BasicInput::Move(
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    Scene * arg_scene,
    const std::shared_ptr<IEntity>& entity,
    std::vector<std::shared_ptr<IEntity>>& arg_entities,
    sf::Font arg_font,
    sf::Text arg_entity_id,
    sf::Time elapsed)
{
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size = entity->template GetComponent<C_Hitbox<std::pair<int, int>>>();
    std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size_2;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_2;
    std::shared_ptr<C_PlayerAmmo<bool>> is_friendly;
    int block_left = 0;
    int block_right = 0;
    int movement_elapsed = 10 * elapsed.asMilliseconds() / 30;



    if (arg_scene->inputs_[1] == 1) {
        for (const std::shared_ptr<IEntity>& entity2 : arg_entities) {
            block_left = 0;
            is_friendly = entity2->template GetComponent<C_PlayerAmmo<bool>>();
            if (entity != entity2 && is_friendly) {
                std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size_2 = entity2->template GetComponent<C_Hitbox<std::pair<int, int>>>();
                std::shared_ptr<C_Position<std::pair<double, double>>> position_2 = entity2->template GetComponent<C_Position<std::pair<double, double>>>();
                if (hitbox_size_2 && position_2) {
                    if ( position_comp->getValue().first < position_2->getValue().first + hitbox_size_2->getValue().first + movement_elapsed &&
                        position_comp->getValue().first + hitbox_size->getValue().first > position_2->getValue().first  &&
                        position_comp->getValue().second < position_2->getValue().second + hitbox_size_2->getValue().second &&
                        position_comp->getValue().second + hitbox_size->getValue().second > position_2->getValue().second)  {
                        block_left = 1;
                        break;
                    }
                }
            }
        }
        if (position_comp->getValue().first > movement_elapsed  && !block_left) {
            position_comp->setValue(std::make_pair(position_comp->getValue().first - movement_elapsed, position_comp->getValue().second));
        }
    }

    if (arg_scene->inputs_[3] == 1) {
        for (const std::shared_ptr<IEntity>& entity2 : arg_entities) {
            block_right = 0;
            is_friendly = entity2->template GetComponent<C_PlayerAmmo<bool>>();
            if (entity != entity2 && is_friendly) {
                std::shared_ptr<C_Hitbox<std::pair<int, int>>> hitbox_size_2 = entity2->template GetComponent<C_Hitbox<std::pair<int, int>>>();
                std::shared_ptr<C_Position<std::pair<double, double>>> position_2 = entity2->template GetComponent<C_Position<std::pair<double, double>>>();
                if (hitbox_size_2 && position_2) {
                    if ( position_comp->getValue().first < position_2->getValue().first + hitbox_size_2->getValue().first &&
                        position_comp->getValue().first + hitbox_size->getValue().first> position_2->getValue().first - movement_elapsed &&
                        position_comp->getValue().second < position_2->getValue().second + hitbox_size_2->getValue().second &&
                        position_comp->getValue().second + hitbox_size->getValue().second > position_2->getValue().second)  {
                        std::cout << "BLOCK RIGHT" << entity2->GetId() << std::endl;
                        block_right = 1;
                        break;
                    }
                }
            }
        }
        if (position_comp->getValue().first < arg_scene->window_->getSize().x - movement_elapsed - hitbox_size->getValue().first  && !block_right) {
            position_comp->setValue(std::make_pair(position_comp->getValue().first + movement_elapsed, position_comp->getValue().second));
        }
    }
    if (arg_scene->inputs_[5] == 1)
    {
        for (const std::shared_ptr<IEntity>& entity : arg_entities) {
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
            DrawEntityHitbox(arg_scene->window_, entity, outlineColor);
            DrawEntityID(arg_scene->window_, entity, arg_font, arg_entity_id);
        }

    }
}

void S_BasicInput::ChangeAdminMode(
    const std::shared_ptr<IEntity>& entity,
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

void S_BasicInput::BasicShot(
    const std::shared_ptr<IEntity>& entity,
    std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    Scene * arg_scene)
{
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();

    if (clock->getValue().getElapsedTime().asSeconds() > 1)
        arg_scene->createEntity(arg_all_entities, 9, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.6)
        arg_scene->createEntity(arg_all_entities, 8, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.4)
        arg_scene->createEntity(arg_all_entities, 7, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.2)
        arg_scene->createEntity(arg_all_entities, 6, position_comp);
    else if (clock->getValue().getElapsedTime().asSeconds() > 0.1)
        arg_scene->createEntity(arg_all_entities, 5, position_comp);
    else
        arg_scene->createEntity(arg_all_entities, 3, position_comp);
}

void S_BasicInput::CheckTouchPressed(
    const std::shared_ptr<IEntity>& entity,
    std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    std::shared_ptr<sf::Event> event_,
    Scene * arg_scene)
{
    std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
    std::shared_ptr<C_Sprite<sf::Sprite>> sprite = entity->template GetComponent<C_Sprite<sf::Sprite>>();
    std::shared_ptr<C_IsMoving<bool>> moving = entity->template GetComponent<C_IsMoving<bool>>();
    std::shared_ptr<C_Grounded<bool>> grounded = entity->template GetComponent<C_Grounded<bool>>();
    std::shared_ptr<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>> size = entity->template GetComponent<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>();
    std::shared_ptr<C_ShootCharging<bool>> is_charging = entity->template GetComponent<C_ShootCharging<bool>>();
    std::shared_ptr<C_Inventory<std::vector<std::shared_ptr<IEntity>>>> vector_entities = entity->template GetComponent<C_Inventory<std::vector<std::shared_ptr<IEntity>>>>();
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();

    if (event_->type == sf::Event::KeyPressed) {
        if (event_->key.code == sf::Keyboard::Left)
            arg_scene->inputs_[1] = 1;
        if (event_->key.code == sf::Keyboard::Right)
            arg_scene->inputs_[3] = 1;
        if (event_->key.code == sf::Keyboard::Space) {
            if (is_charging->getValue() == false) {
                clock->getValue().restart();
                vector_entities->getValue().push_back(arg_scene->createEntity(arg_all_entities, 27, position_comp));
                is_charging->getValue() = true;
            }
        }
        if (grounded)
        {
            if (event_->key.code == sf::Keyboard::V && arg_scene->inputs_[6] == 0 && grounded->getValue() == true) {
                arg_scene->inputs_[6] = 1;
                std::cout << " PRESS JUMP " << std::endl;
            }
        }
        if (event_->key.code == sf::Keyboard::Z && arg_scene->inputs_[5] == 1)
            arg_scene->inputs_[5] = 0;
        else if (event_->key.code == sf::Keyboard::Z && arg_scene->inputs_[5] == 0)
            arg_scene->inputs_[5] = 1;
    }
}


void S_BasicInput::CheckTouchReleased(
    const std::shared_ptr<IEntity>& entity,
    std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
    std::shared_ptr<sf::Event> event_,
    Scene * arg_scene)
    {
    std::shared_ptr<C_ShootCharging<bool>> is_charging = entity->template GetComponent<C_ShootCharging<bool>>();
    std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
    std::shared_ptr<C_Sprite<sf::Sprite>> sprite = entity->template GetComponent<C_Sprite<sf::Sprite>>();
    std::shared_ptr<C_IsMoving<bool>> moving = entity->template GetComponent<C_IsMoving<bool>>();
    std::shared_ptr<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>> size = entity->template GetComponent<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>();
    std::shared_ptr<C_ChargedShoot<sf::Clock>> clock = entity->template GetComponent<C_ChargedShoot<sf::Clock>>();

    if (event_->type == sf::Event::KeyReleased) {
        if (event_->key.code == sf::Keyboard::Up) {
            arg_scene->inputs_[0] = 0;
            moving->getValue() = false;
            rect->getValue().left = size->getValue().second.first;
            sprite->getValue().setTextureRect(rect->getValue());
        }
        if (event_->key.code == sf::Keyboard::Num1) {
            arg_scene->need_switch_ = true;
            arg_scene->next_timeline_ = "1";
        }
        if (event_->key.code == sf::Keyboard::Num2) {
            arg_scene->need_switch_ = true;
            arg_scene->next_timeline_ = "2";
        }
        if (event_->key.code == sf::Keyboard::Num3) {
            arg_scene->need_switch_ = true;
            arg_scene->next_timeline_ = "3";
        }
        if (event_->key.code == sf::Keyboard::Left)
            arg_scene->inputs_[1] = 0;
        if (event_->key.code == sf::Keyboard::Right)
            arg_scene->inputs_[3] = 0;
        if (event_->key.code == sf::Keyboard::Space) {
            BasicShot(entity, arg_all_entities, position_comp, arg_scene);
            is_charging->getValue() = false;
        }
        ChangeAdminMode(entity, event_);
    }
}


void S_BasicInput::Execute(
        int arg_is_server,
        Scene * arg_scene)  {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    sf::Font font_arg_;
    font_arg_.loadFromFile("../../rtype/sources/fonts/arial.ttf");
    sf::Text entity_id;
    std::shared_ptr<C_PlayerMovementClock<sf::Clock>> player_movement_clock;
    entity_id.setFillColor(sf::Color::Magenta);
    entity_id.setCharacterSize(10);
    entity_id.setFont(font_arg_);

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        std::shared_ptr<C_Position<std::pair<double, double>>> position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        std::shared_ptr<C_Player<int>> player_id =  entity->template GetComponent<C_Player<int>>();
        player_movement_clock = entity->template GetComponent<C_PlayerMovementClock<sf::Clock>>();
        sf::Time elapsed = player_movement_clock->getValue().getElapsedTime();
        if (arg_is_server == 1)
            continue;
        if (!player_id)
            continue;
        if (&entity != &arg_entities.front())
            continue;
        while (arg_scene->window_->pollEvent(*arg_scene->event_)) {
            if (arg_scene->event_->type == sf::Event::Closed)
                arg_scene->window_->close();
            CheckTouchPressed(entity, arg_scene->entities_, position_comp, arg_scene->event_, arg_scene);
            CheckTouchReleased(entity, arg_scene->entities_, position_comp, arg_scene->event_, arg_scene);
        }
        Move(position_comp, arg_scene, entity, arg_scene->entities_, font_arg_, entity_id, elapsed);
        player_movement_clock->getValue().restart();
    }
}