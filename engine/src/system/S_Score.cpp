#include "system/S_Score.hpp"

std::vector<std::shared_ptr<IEntity>> S_Score::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Point<int>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_Score::Execute(
        int arg_is_server,
        Scene * arg_scene)  {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
        std::shared_ptr<C_Point<int>> point_;
        std::shared_ptr<C_Score<int>> score_;
        std::shared_ptr<C_ScoreText<sf::Text>> score_text_;

        for (const std::shared_ptr<IEntity>& entity2 : arg_scene->entities_) {
            score_ = entity2->template GetComponent<C_Score<int>>();
            score_text_ = entity2->template GetComponent<C_ScoreText<sf::Text>>();
            if (score_ && score_text_) {
                score_text_->getValue().setString(std::to_string(score_->getValue()));
                score_text_->getValue().setPosition(arg_scene->window_->getSize().x/2,0);
                std::shared_ptr<sf::Font> font = std::shared_ptr<sf::Font>(new sf::Font());
                font->loadFromFile("../../rtype/sources/fonts/r-type.ttf");
                score_text_->getValue().setFont(*font);
                score_text_->getValue().setFillColor(sf::Color::Cyan);
                score_text_->getValue().setCharacterSize(10);
                arg_scene->window_->draw(score_text_->getValue());
                break;
            }
        }

        for (const std::shared_ptr<IEntity>& entity : arg_entities) {
            if (!entity->is_dead_)
                continue;
            point_ = entity->template GetComponent<C_Point<int>>();
            for (const std::shared_ptr<IEntity>& entity2 : arg_scene->entities_) {
                score_ = entity2->template GetComponent<C_Score<int>>();
                score_text_ = entity2->template GetComponent<C_ScoreText<sf::Text>>();
                if (score_) {
                    score_->getValue() += point_->getValue();
                    break;
                }
            }
        }
}