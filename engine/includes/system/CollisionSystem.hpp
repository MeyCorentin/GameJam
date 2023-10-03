#pragma once

#include "TSystem.hpp"
#include "../components/Position.hpp"
#include "../components/Hitbox.hpp"

class CollisionSystem : public TSystem {
    public:
        std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) override {
            std::vector<std::shared_ptr<TEntity>> filteredEntities;
            for (const std::shared_ptr<TEntity>& entity : _entities) {
                if (entity->hasComponent(typeid(Hitbox<std::pair<int, int>>)) &&
                    entity->hasComponent(typeid(Position<std::pair<double, double>>))) {
                    filteredEntities.push_back(entity);
                }
            }
            return filteredEntities;
        }

        void drawHitbox(std::shared_ptr<sf::RenderWindow> _window, const std::shared_ptr<Position<std::pair<double, double>>>& positionComp, const std::shared_ptr<Hitbox<std::pair<int, int>>>& hitboxComp, bool isPlayer) {
            sf::RectangleShape hitbox;
            hitbox.setPosition(positionComp->getValue().first, positionComp->getValue().second);
            hitbox.setSize(sf::Vector2f(hitboxComp->getValue().first, hitboxComp->getValue().second));
            hitbox.setFillColor(sf::Color::Transparent);
            hitbox.setOutlineColor(isPlayer ? sf::Color::Green : sf::Color::Red);
            hitbox.setOutlineThickness(1.0f);
            _window->draw(hitbox);
        }

        void execute(std::vector<std::shared_ptr<TEntity>>& _entities, std::shared_ptr<sf::RenderWindow> _window, std::vector<int> _inputs, std::vector<std::shared_ptr<TEntity>>& allEntities, std::vector<std::shared_ptr<sf::Sprite>>& sprites, std::vector<std::shared_ptr<sf::Texture>>& textures) override {
            for (const std::shared_ptr<TEntity>& entity1 : _entities) {
                std::shared_ptr<Position<std::pair<double, double>>> positionComp1 = entity1->template getComponent<Position<std::pair<double, double>>>();
                std::shared_ptr<Hitbox<std::pair<int, int>>> hitboxComp1 = entity1->template getComponent<Hitbox<std::pair<int, int>>>();
                std::shared_ptr<Player<bool>> isPlayer = entity1->template getComponent<Player<bool>>();

                drawHitbox(_window, positionComp1, hitboxComp1, isPlayer ? isPlayer->getValue() : false);
                float x1 = static_cast<float>(positionComp1->getValue().first);
                float y1 = static_cast<float>(positionComp1->getValue().second);
                for (const std::shared_ptr<TEntity>& entity2 : _entities) {
                    if (entity1 == entity2)
                        continue;
                    std::shared_ptr<Position<std::pair<double, double>>> positionComp2 = entity2->template getComponent<Position<std::pair<double, double>>>();
                    std::shared_ptr<Hitbox<std::pair<int, int>>> hitboxComp2 = entity2->template getComponent<Hitbox<std::pair<int, int>>>();
                    if (!positionComp2 || !hitboxComp2)
                        continue;
                    float x2 = static_cast<float>(positionComp2->getValue().first);
                    float y2 = static_cast<float>(positionComp2->getValue().second);
                    if (x1 < x2 + hitboxComp2->getValue().first &&
                        x1 + hitboxComp1->getValue().first> x2 &&
                        y1 < y2 + hitboxComp2->getValue().second &&
                        y1 + hitboxComp1->getValue().second > y2) {
                            // std::cout << "HIT" << std::endl;
                    }
                }
            }
        }
};
