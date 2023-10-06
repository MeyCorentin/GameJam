#pragma once

#include "SceneBuilder.hpp"

class SystemRegistry {
    public:
        using SystemConstructor = std::function<std::shared_ptr<System>()>;

        static SystemRegistry& Instance() {
            static SystemRegistry registry;
            return registry;
        }

        void RegisterSystem(
                const std::string& arg_name,
                SystemConstructor arg_constructor) {
            systems[arg_name] = arg_constructor;
        }

        std::shared_ptr<System> CreateSystem(const std::string& arg_name) {
            std::unordered_map<std::string, SystemRegistry::SystemConstructor>::iterator it = systems.find(arg_name);

            if (it != systems.end())
                return it->second();
            return nullptr;
        }

    private:
        SystemRegistry() {}
        std::unordered_map<std::string, SystemConstructor> systems;
};