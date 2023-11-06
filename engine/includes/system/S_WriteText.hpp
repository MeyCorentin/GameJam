#pragma once

#include "System.hpp"

#include "../scene/Scene.hpp"

#include "../components/C_Text.hpp"
#include "../components/C_TextMessage.hpp"

class S_WriteText : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};
