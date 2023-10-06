#pragma once

#include "SceneBuilder.hpp"
#include "SystemRegister.hpp"

class ComponentRegistry {
    public:
        using ComponentConstructor = std::function<std::shared_ptr<ComponentBase>()>;

        static ComponentRegistry& Instance() {
            static ComponentRegistry registry;
            return registry;
        }

        void RegisterComponent(const std::string& arg_name, ComponentConstructor arg_constructor) {
            components[arg_name] = arg_constructor;
        }

        std::shared_ptr<ComponentBase> CreateComponent(const std::string& arg_name) {
            std::unordered_map<std::string, ComponentRegistry::ComponentConstructor>::iterator it = components.find(arg_name);

            if (it != components.end())
                return it->second();
            return nullptr;
        }

    private:
        ComponentRegistry() {}
        std::unordered_map<std::string, ComponentConstructor> components;
};




