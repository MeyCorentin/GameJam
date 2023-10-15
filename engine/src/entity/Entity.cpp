#include "entity/Entity.hpp"

Entity::Entity(int arg_id, std::vector<std::shared_ptr<ComponentBase>> arg_components) : 
    id_(arg_id), components_(arg_components) {}

Entity::Entity(const Entity& other) :
    id_(other.id_),
    is_dead_(other.is_dead_) {
    components_.reserve(other.components_.size());
    for (const auto& component : other.components_) {
        if (component) {
            components_.emplace_back(component->Clone());
        }
    }
}

int Entity::GetId() {
    return id_;
}

void Entity::SetId(int arg_id) {
    id_ = arg_id;
}

std::shared_ptr<Entity> Entity::Clone() const {
    return std::make_shared<Entity>(*this);
}

bool Entity::HasComponent(const std::type_info& arg_type) const {
    for (const auto& component : components_) {
        if ((*component).GetType() == arg_type) {
            return true;
        }
    }
    return false;
}
