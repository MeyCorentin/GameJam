#pragma once

#include "SceneBuilder.hpp"

class SystemRegistry {
    public:
        using SystemConstructor = std::function<std::shared_ptr<TSystem>()>;

        static SystemRegistry& instance() {
            static SystemRegistry registry;
            return registry;
        }

        void registerSystem(const std::string& _name, SystemConstructor _constructor) {
            systems[_name] = _constructor;
        }

        std::shared_ptr<TSystem> createSystem(const std::string& _name) {
            std::unordered_map<std::string, SystemRegistry::SystemConstructor>::iterator it = systems.find(_name);
            if (it != systems.end())
                return it->second();
            return nullptr;
        }

    private:
        SystemRegistry() {}
        std::unordered_map<std::string, SystemConstructor> systems;
};