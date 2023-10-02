#pragma once

#include "TSystem.hpp"
#include "../components/Direction.hpp"
#include "../components/Speed.hpp"
#include "../components/Position.hpp"

class MouvementSystem : public TSystem {
    public:
        std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) override {
            std::vector<std::shared_ptr<TEntity>> filteredEntities;
            for (const std::shared_ptr<TEntity>& entity : _entities) {
                if (entity->hasComponent(typeid(Direction<std::pair<double, double>>)) &&
                    entity->hasComponent(typeid(Position<std::pair<double, double>>)) &&
                    entity->hasComponent(typeid(Speed<double>))) {
                    filteredEntities.push_back(entity);
                }
            }
            return filteredEntities;
        }

        void execute(std::vector<std::shared_ptr<TEntity>>& _entities, sf::RenderWindow &_window, std::vector<int> _inputs) override {
            for (const std::shared_ptr<TEntity>& entity : _entities) {
                std::shared_ptr<Direction<std::pair<double, double>>> direction = entity->template getComponent<Direction<std::pair<double, double>>>();
                std::shared_ptr<Position<std::pair<double, double>>> position = entity->template getComponent<Position<std::pair<double, double>>>();
                std::shared_ptr<Speed<double>> speed = entity->template getComponent<Speed<double>>();
                position->setValue(std::make_pair(  position->getValue().first + speed->getValue() * direction->getValue().first,
                                                    position->getValue().second+ speed->getValue() * direction->getValue().second));
            }
        }
};
