#include "scene/SystemRegister.hpp"

SystemRegistry& SystemRegistry::Instance() {
    static SystemRegistry registry;
    return registry;
}

void SystemRegistry::RegisterSystem(
        const std::string& arg_name,
        SystemConstructor arg_constructor) {
    systems[arg_name] = arg_constructor;
}

std::shared_ptr<ISystem> SystemRegistry::CreateSystem(const std::string& arg_name) {
    std::unordered_map<std::string, SystemRegistry::SystemConstructor>::iterator it = systems.find(arg_name);

    if (it != systems.end())
        return it->second();
    return nullptr;
}

SystemRegistry::SystemRegistry() {}