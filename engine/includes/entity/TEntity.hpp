#pragma once

#include "../main.hpp"
#include "../components/TComponentBase.hpp"
/**
 * @brief An entity representing a game object with associated components.
 *
 * The `TEntity` class represents a game entity that can have various components.
 * Each entity is identified by a unique ID and can have multiple components attached to it.
 */
class TEntity {
    public:
        int id; ///< The unique identifier for the entity.
        std::vector<std::shared_ptr<TComponentBase>> components; ///< The list of components associated with the entity.
        /**
        int id; ///< The unique identifier for the entity.
        std::vector<std::shared_ptr<TComponentBase>> components; ///< The list of components associated with the entity.
        * @brief Constructs an entity with the given ID and components.
        *
        * @param n The unique ID for the entity.
        * @param components A vector of shared pointers to components associated with the entity.
        */
        TEntity(int n, std::vector<std::shared_ptr<TComponentBase>> components) : id(n), components(components) {}

        /**
         * @brief Get the unique identifier of the entity.
         *
         * @return The ID of the entity.
         */
        int getId() {
            return id;
        }

        void setId(int _id) {
            this->id = _id;
        }

        /**
         * @brief Check if the entity has a component of a specific type.
         *
         * @param _type The type of component to check for.
         * @return `true` if the entity has a component of the specified type, otherwise `false`.
         */
        bool hasComponent(const std::type_info& _type) const {
            for (const auto& component : components) {
                if ((*component).getType() == _type) {
                    return true;
                }
            }
            return false;
        }

        /**
         * @brief Get a specific type of component attached to the entity.
         *
         * @tparam ComponentType The type of component to retrieve.
         * @return A shared pointer to the component if found, or nullptr if not found.
         */
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