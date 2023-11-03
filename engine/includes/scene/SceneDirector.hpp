#pragma once

#include "SceneBuilder.hpp"
#include "../parser/jsonParser.hpp"
#include "SystemRegister.hpp"
#include "ComponentRegister.hpp"

class SceneDirector {
    private:
        SceneBuilder scene_builder_;
        std::vector<std::shared_ptr<System>> systems_;
        std::vector<std::shared_ptr<Entity>> entities_;

    public:

        std::shared_ptr<System> CreateSystemFromConfig(const json& arg_systemConfig);
        std::shared_ptr<System> CreateSystemFromType(std::string arg_type);

        const json& FindComponentConfigById(
                const json& arg_componentsConfig,
                int arg_id);

        bool ProcessComponent(
                const json& arg_entity_component,
                const json& arg_component_config,
                JsonParser& arg_parser,
                EntityBuilder& arg_entity_builder);

        std::shared_ptr<Entity> CreateEntityFromConfig(
                const json& arg_entity_config,
                const json& arg_components_config);

        template <typename T>
        T getRandomInRange(T min, T max);

        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> CreateMap(const json& arg_spawn_config);

        std::vector<std::pair<int,int>> CreateJump(const json& arg_spawn_config);

        SceneDirector();

        SceneDirector(std::string arg_file_path, int value);

        Scene ConstructScene();
};
