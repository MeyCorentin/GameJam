#include "system/S_WriteText.hpp"

std::vector<std::shared_ptr<IEntity>> S_WriteText::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Text<sf::Text>)) &&
            entity->HasComponent(typeid(C_Position<std::pair<double, double>>)) &&
            entity->HasComponent(typeid(C_TextMessage<std::string>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_WriteText::Execute(
        int arg_is_server,
        Scene * arg_scene) {

    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    std::shared_ptr<C_Text<sf::Text>> my_text;
    std::shared_ptr<C_TextMessage<std::string>> message;
    std::shared_ptr<C_Position<std::pair<double, double>>> position;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        my_text = entity->template GetComponent<C_Text<sf::Text>>();
        message = entity->template GetComponent<C_TextMessage<std::string>>();
        position = entity->template GetComponent<C_Position<std::pair<double, double>>>();

        my_text->getValue().setString(message->getValue());
        my_text->getValue().setPosition(position->getValue().first, position->getValue().second);

        std::shared_ptr<sf::Font> font = std::shared_ptr<sf::Font>(new sf::Font());
        font->loadFromFile("../../rtype/sources/fonts/r-type.ttf");
        my_text->getValue().setFont(*font);
        my_text->getValue().setFillColor(sf::Color::Cyan);
        my_text->getValue().setCharacterSize(10);

        arg_scene->window_->draw(my_text->getValue());
    }
}
