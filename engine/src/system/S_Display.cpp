#include "system/S_Display.hpp"

std::vector<std::shared_ptr<IEntity>> S_Display::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Sprite<sf::Sprite>)) &&
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Display::Execute(
        int arg_is_server,
        Scene * arg_scene) {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::shared_ptr<C_Sprite<sf::Sprite>>sprite_comp;
    std::shared_ptr<C_Texture<sf::Texture>>texture_comp;
    std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
    std::shared_ptr<C_Background<bool>> is_background;
    float x_position;
    float y_position;
    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        is_background = entity->template GetComponent<C_Background<bool>>();
        if (!is_background)
            continue;
        sprite_comp = entity->template GetComponent<C_Sprite<sf::Sprite>>();
        texture_comp = entity->template GetComponent<C_Texture<sf::Texture>>();
        if (texture_comp)
        {
            const sf::Texture* texture = sprite_comp->getValue().getTexture();
            if (texture == nullptr)
            {
                sprite_comp->getValue().setTexture(texture_comp->getValue());
            }
        }
        position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        x_position = static_cast<float>(position_comp->getValue().first);
        y_position = static_cast<float>(position_comp->getValue().second);
        sprite_comp->getValue().setPosition(x_position, y_position);
        arg_scene->window_->draw(sprite_comp->getValue());
    }

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        is_background = entity->template GetComponent<C_Background<bool>>();
        if (is_background)
            continue;
        sprite_comp = entity->template GetComponent<C_Sprite<sf::Sprite>>();
        position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
        texture_comp = entity->template GetComponent<C_Texture<sf::Texture>>();
        if (texture_comp)
        {
            const sf::Texture* texture = sprite_comp->getValue().getTexture();
            if (texture == nullptr)
            {
                sprite_comp->getValue().setTexture(texture_comp->getValue());
            }
        }
        x_position = static_cast<float>(position_comp->getValue().first);
        y_position = static_cast<float>(position_comp->getValue().second);
        sprite_comp->getValue().setPosition(x_position, y_position);
        arg_scene->window_->draw(sprite_comp->getValue());
    }
}
