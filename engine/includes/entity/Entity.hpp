#pragma once

#include "../main.hpp"
#include "../components/ComponentBase.hpp"

class Entity {
    public:
        int id_;
        bool is_dead_ = false;;
        std::vector<std::shared_ptr<ComponentBase>> components_;
        Entity(int arg_id, std::vector<std::shared_ptr<ComponentBase>> arg_components) : 
            id_(arg_id), components_(arg_components) {}

        Entity(const Entity& other) :
            id_(other.id_),
            is_dead_(other.is_dead_) {
            components_.reserve(other.components_.size());
            for (const auto& component : other.components_) {
                if (component) {
                    components_.emplace_back(component->Clone());
                }
            }
        }

        int GetId() {
            return id_;
        }

        void SetId(int arg_id) {
            id_ = arg_id;
        }

        std::shared_ptr<Entity> Clone() const {
            return std::make_shared<Entity>(*this);
        }

        bool HasComponent(const std::type_info& arg_type) const {
            for (const auto& component : components_) {
                if ((*component).GetType() == arg_type) {
                    return true;
                }
            }
            return false;
        }

        template <class ComponentType>
        std::shared_ptr<ComponentType> GetComponent() const {
            for (const auto& component : components_) {
                auto casted_component = std::dynamic_pointer_cast<ComponentType>(component);
                if (casted_component) {
                    return casted_component;
                }
            }
            return nullptr;
        }
};