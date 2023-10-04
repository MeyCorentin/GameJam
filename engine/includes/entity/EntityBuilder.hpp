#pragma once

#include "Entity.hpp"
#include <memory>
#include <vector>
#include "../components/Component.hpp"

class EntityBuilder {
    private:
        std::shared_ptr<Entity> entity_;

    public:
        EntityBuilder(int arg_id) {
            entity_ = std::make_shared<Entity>(arg_id , std::vector<std::shared_ptr<ComponentBase>>());
        }

        template <typename T>
        EntityBuilder& addComponent(
                std::shared_ptr<ComponentBase> arg_component,
                T arg_value) {
            auto concreteComponent = std::dynamic_pointer_cast<Component<T>>(arg_component);

            if (concreteComponent) {
                concreteComponent->setValue(arg_value);
                entity_->components_.push_back(arg_component);
            }
            return *this;
        }

        EntityBuilder& setID(int arg_id) {
            entity_->setId(arg_id);
            return *this;
        }

        std::shared_ptr<Entity> build() {
            return entity_;
        }
};