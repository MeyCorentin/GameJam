#pragma once

#include "SceneBuilder.hpp"
#include "SystemRegister.hpp"

class ComponentRegistry {
    public:
        using ComponentConstructor = std::function<std::shared_ptr<TComponentBase>()>;

        static ComponentRegistry& instance() {
            static ComponentRegistry registry;
            return registry;
        }

        void registerComponent(const std::string& _name, ComponentConstructor _constructor) {
            components[_name] = _constructor;
        }

        std::shared_ptr<TComponentBase> createComponent(const std::string& _name) {
            std::unordered_map<std::string, ComponentRegistry::ComponentConstructor>::iterator it = components.find(_name);
            if (it != components.end())
                return it->second();
            return nullptr;
        }

    private:
        ComponentRegistry() {}
        std::unordered_map<std::string, ComponentConstructor> components;
};




