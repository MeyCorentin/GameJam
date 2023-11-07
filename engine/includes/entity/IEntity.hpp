#pragma once

#include "../components/IComponent.hpp"

class IEntity {
    public:
        int id_;
        int base_id_;
        bool is_dead_ = false;;
        std::vector<std::shared_ptr<IComponent>> components_;
        IEntity(int arg_id, std::vector<std::shared_ptr<IComponent>> arg_components);

        IEntity(const IEntity& other);

        int GetId();

        void SetId(int arg_id);

        int GetBaseId();

        void SetBaseId(int arg_id);

        std::shared_ptr<IEntity> Clone() const;

        bool HasComponent(const std::type_info& arg_type) const;

        template <class ComponentType>
        std::shared_ptr<ComponentType> GetComponent() const {
            auto it = std::find_if(components_.begin(), components_.end(), [](const auto& component) {
                return std::dynamic_pointer_cast<ComponentType>(component) != nullptr;
            });

            if (it != components_.end()) {
                auto casted_component = std::dynamic_pointer_cast<ComponentType>(*it);
                return casted_component;
            }

            return nullptr;
        }
};