#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Sound.hpp"
#include "../components/C_SoundBuffer.hpp"
#include "../components/C_SoundIsActive.hpp"

class S_PlaySound : public ISystem {
    public:
        std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;

};