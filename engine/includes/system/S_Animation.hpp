#include "System.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Clock.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../components/C_Size.hpp"
#include "../components/C_Animation.hpp"

class S_Animation : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& _entities) override {
            std::vector<std::shared_ptr<Entity>> filteredEntities;
            for (const std::shared_ptr<Entity>& entity : _entities) {
                if (entity->HasComponent(typeid(C_Sprite<sf::Sprite>)) &&
                    entity->HasComponent(typeid(C_Clock<sf::Clock>)) &&
                    entity->HasComponent(typeid(C_SpriteRect<sf::IntRect>)) &&
                    entity->HasComponent(typeid(C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>)) &&
                    entity->HasComponent(typeid(C_Animation<bool>))) {
                    filteredEntities.push_back(entity);
                }
            }
            return filteredEntities;
        }

        void Execute(std::vector<std::shared_ptr<Entity>>& _entities, std::shared_ptr<sf::RenderWindow> _window, std::vector<int> _inputs, std::vector<std::shared_ptr<Entity>>& allEntities, std::vector<sf::Sprite>& sprites, std::vector<std::shared_ptr<sf::Texture>>& textures, std::shared_ptr<sf::Event> event_) override {
            for (const std::shared_ptr<Entity>& entity : _entities) {
                std::shared_ptr<C_Sprite<sf::Sprite>> sprite = entity->template GetComponent<C_Sprite<sf::Sprite>>();
                std::shared_ptr<C_Clock<sf::Clock>> clock = entity->template GetComponent<C_Clock<sf::Clock>>();
                std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
                std::pair<std::pair<int, int>, std::pair<int, int>> size = entity->template GetComponent<C_Size<std::pair<std::pair<int, int>, std::pair<int, int>>>>()->getValue();
                bool animaion = entity->template GetComponent<C_Animation<bool>>()->getValue();
                if (clock->getValue().getElapsedTime().asSeconds() > 0.1f) {
                    if (rect->getValue().left >= rect->getValue().width + size.second.first) {
                        rect->getValue().left = size.second.first;
                    } else {
                        rect->getValue().left += rect->getValue().width;
                    }
                    sprite->getValue().setTextureRect(rect->getValue());
                    clock->getValue().restart();
                }
            }
        }
};

