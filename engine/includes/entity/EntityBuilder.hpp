#pragma once

#include "IEntity.hpp"
#include <memory>
#include <vector>
#include "../components/AComponent.hpp"

class EntityBuilder {
    private:

    public:
        std::shared_ptr<IEntity> entity_;

        EntityBuilder(int arg_id);

        template <typename T>
        EntityBuilder& AddComponent(
                std::shared_ptr<IComponent> arg_component,
                T arg_value) {
            auto concrete_component = std::dynamic_pointer_cast<AComponent<T>>(arg_component);

            if (concrete_component) {
                concrete_component->setValue(arg_value);
                entity_->components_.push_back(concrete_component);
            }
            return *this;
        }

        EntityBuilder& SetID(int arg_id);

        std::shared_ptr<IEntity> Build();
};