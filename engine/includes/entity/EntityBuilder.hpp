#pragma once

#include "TEntity.hpp"
#include <memory>
#include <vector>

class EntityBuilder {
private:
    std::shared_ptr<TEntity> entity;

public:
    EntityBuilder(int id) {
        entity = std::make_shared<TEntity>(id , std::vector<std::shared_ptr<TComponentBase>>());
    }

    template <typename ComponentType>
    EntityBuilder& addComponent(std::shared_ptr<ComponentType> component) {
        entity->components.push_back(component);
        return *this;
    }

    EntityBuilder& setID(int id) {
        entity->setId(id);
        return *this;
    }

    std::shared_ptr<TEntity> build() {
        return entity;
    }
};