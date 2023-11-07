#pragma once

#include "ISystem.hpp"
#include "../scene/Scene.hpp"

#include "../components/C_TimeAutoMove.hpp"
#include "../components/C_ClockAutoMove.hpp"
#include "../components/C_IsAutoMove.hpp"

class S_AutoMove : public ISystem {
    public:
        std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;
};