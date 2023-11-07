#include "system/ISystem.hpp"

void ISystem::Compute(
    int arg_is_server,
    Scene * arg_scene) {
        Execute(arg_is_server, arg_scene);
}