#include "entity/IEntity.hpp"

IEntity::IEntity(int arg_id, std::vector<std::shared_ptr<IComponent>> arg_components) : 
    id_(arg_id), components_(arg_components) {}

IEntity::IEntity(const IEntity& other) :
    id_(other.id_),
    is_dead_(other.is_dead_) {
    components_.reserve(other.components_.size());
    for (const auto& component : other.components_) {
        if (component) {
            components_.emplace_back(component->Clone());
        }
    }
}

int IEntity::GetId() {
    return id_;
}

void IEntity::SetId(int arg_id) {
    id_ = arg_id;
}


int IEntity::GetBaseId() {
    return base_id_;
}

void IEntity::SetBaseId(int arg_id) {
    base_id_ = arg_id;
}

std::shared_ptr<IEntity> IEntity::Clone() const {
    return std::make_shared<IEntity>(*this);
}

bool IEntity::HasComponent(const std::type_info& arg_type) const {
    for (const auto& component : components_) {
        if ((*component).GetType() == arg_type) {
            return true;
        }
    }
    return false;
}
