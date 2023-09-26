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

    template <typename T>
    EntityBuilder& addComponent(std::shared_ptr<TComponentBase> component, T value) {
        auto concreteComponent = std::dynamic_pointer_cast<TComponent<T>>(component);
        if (concreteComponent) {
            concreteComponent->setValue(value);
            entity->components.push_back(component);
        }
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