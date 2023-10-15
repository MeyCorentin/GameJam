#include "entity/EntityBuilder.hpp"

EntityBuilder::EntityBuilder(int arg_id) {
    Entity* temp = new Entity(arg_id, std::vector<std::shared_ptr<ComponentBase>>());
    entity_ = std::shared_ptr<Entity>(temp);
}

EntityBuilder& EntityBuilder::SetID(int arg_id) {
    entity_->SetId(arg_id);
    return *this;
}

std::shared_ptr<Entity> EntityBuilder::Build() {
    return entity_;
}