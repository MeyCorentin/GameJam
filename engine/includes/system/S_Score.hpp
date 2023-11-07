#include "ISystem.hpp"
#include "../scene/Scene.hpp"
#include "../components/C_Point.hpp"
#include "../components/C_Score.hpp"
#include "../components/C_ScoreText.hpp"

class S_Score : public ISystem {
    public:
        std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;

};