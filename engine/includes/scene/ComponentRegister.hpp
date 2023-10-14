#pragma once

#include "SceneBuilder.hpp"
#include "SystemRegister.hpp"

class ComponentRegistry {
    public:
        using ComponentConstructor = std::function<std::shared_ptr<ComponentBase>()>;

        static ComponentRegistry& Instance();

        void RegisterComponent(const std::string& arg_name, ComponentConstructor arg_constructor);

        std::shared_ptr<ComponentBase> CreateComponent(const std::string& arg_name);

        ComponentRegistry();

        std::unordered_map<std::string, ComponentConstructor> components;
};




