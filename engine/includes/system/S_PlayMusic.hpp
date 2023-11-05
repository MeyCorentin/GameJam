#include "System.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Music.hpp"
#include "../components/C_MusicIsActive.hpp"
#include <SFML/Audio.hpp>

class S_PlayMusic : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;

};