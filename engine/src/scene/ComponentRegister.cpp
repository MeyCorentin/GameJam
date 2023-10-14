#include "scene/ComponentRegister.hpp"

void ComponentRegistry::RegisterComponent(const std::string& arg_name, ComponentConstructor arg_constructor) {
    components[arg_name] = arg_constructor;
}

std::shared_ptr<ComponentBase> ComponentRegistry::CreateComponent(const std::string& arg_name) {
    std::unordered_map<std::string, ComponentRegistry::ComponentConstructor>::iterator it = components.find(arg_name);

    if (it != components.end())
        return it->second();
    return nullptr;
}

ComponentRegistry::ComponentRegistry() {}