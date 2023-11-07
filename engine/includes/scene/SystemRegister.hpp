#pragma once

#include "SceneBuilder.hpp"

class SystemRegistry {
    public:
        using SystemConstructor = std::function<std::shared_ptr<ISystem>()>;

        static SystemRegistry& Instance();

        void RegisterSystem(const std::string& arg_name, SystemConstructor arg_constructor);

        std::shared_ptr<ISystem> CreateSystem(const std::string& arg_name);

        SystemRegistry();

        std::unordered_map<std::string, SystemConstructor> systems;
};