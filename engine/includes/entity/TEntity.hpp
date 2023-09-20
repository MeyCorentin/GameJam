#pragma once

#include "../main.hpp"
#include "../component/TComponentBase.hpp"

class TEntity {
    private:
        int id;
        std::vector<std::shared_ptr<TComponentBase>> components;

    public:
        TEntity(int n, std::initializer_list<std::shared_ptr<TComponentBase>> components) : id(n), components(components)  {}

        int getId() {
            return id;
        }

        bool hasComponent(const std::type_info& type) const {
            for (const auto& component : components) {
                if ((*component).getType() == type)
                    return true;
            }
            return false;
        }

        template <class ComponentType>
        std::shared_ptr<ComponentType> getComponent() const {
            for (const auto& component : components) {
                auto castedComponent = std::dynamic_pointer_cast<ComponentType>(component);
                if (castedComponent) {
                    return castedComponent;
                }
            }
            return nullptr;
        }
};