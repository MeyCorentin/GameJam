#pragma once

#include "ISystem.hpp"

#include "../scene/Scene.hpp"

#include "../components/C_Text.hpp"
#include "../components/C_TextMessage.hpp"

class S_WriteText : public ISystem {
    public:
        std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};
