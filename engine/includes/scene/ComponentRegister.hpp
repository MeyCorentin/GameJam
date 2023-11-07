#pragma once

#include "SceneBuilder.hpp"
#include "SystemRegister.hpp"

class ComponentRegistry {
    public:
        using ComponentConstructor = std::function<std::shared_ptr<IComponent>()>;

        static ComponentRegistry& Instance();

        void RegisterComponent(const std::string& arg_name, ComponentConstructor arg_constructor);

        std::shared_ptr<IComponent> CreateComponent(const std::string& arg_name);

        ComponentRegistry();

        std::unordered_map<std::string, ComponentConstructor> components;
};




