#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Grass.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_SpawnClock.hpp"
#include "../components/C_IsFighting.hpp"
#include "../components/C_Text.hpp"
#include "../components/C_TextMessage.hpp"
#include "../components/C_Experience.hpp"


class S_SpawnPokemon : public ISystem {
    public:
    std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

    void Execute(
            int arg_is_server,
            Scene * arg_scene) override;
};
