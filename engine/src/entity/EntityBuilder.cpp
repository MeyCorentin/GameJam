#include "entity/EntityBuilder.hpp"

EntityBuilder::EntityBuilder(int arg_id) {
    IEntity* temp = new IEntity(arg_id, std::vector<std::shared_ptr<IComponent>>());
    entity_ = std::shared_ptr<IEntity>(temp);
}

EntityBuilder& EntityBuilder::SetID(int arg_id) {
    entity_->SetId(arg_id);
    return *this;
}

std::shared_ptr<IEntity> EntityBuilder::Build() {
    return entity_;
}