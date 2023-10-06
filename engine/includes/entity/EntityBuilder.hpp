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
        EntityBuilder& AddComponent(
                std::shared_ptr<ComponentBase> arg_component,
                T arg_value) {
            auto concrete_component = std::dynamic_pointer_cast<Component<T>>(arg_component);

            if (concrete_component) {
                concrete_component->setValue(arg_value);
                entity_->components_.push_back(arg_component);
            }
            return *this;
        }

        EntityBuilder& SetID(int arg_id) {
            entity_->SetId(arg_id);
            return *this;
        }

        std::shared_ptr<Entity> Build() {
            return entity_;
        }
};