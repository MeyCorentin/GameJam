#pragma once

#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../system/ISystem.hpp"
#include "Scene.hpp"


class SceneBuilder {
    private:
        std::vector<std::shared_ptr<ISystem>> systems_;
        std::vector<std::shared_ptr<IEntity>> entities_;
        std::vector<sf::Sprite> sprites_;
        std::vector<std::shared_ptr<sf::Texture>> textures_;
        std::vector<std::shared_ptr<sf::Music>> music_;
        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> spawn_index_;
        std::vector<std::pair<int, int>> jump_index_;
        std::string path_;

    public:
        SceneBuilder& AddSystem(std::shared_ptr<ISystem> arg_system);

        SceneBuilder& AddEntity(std::shared_ptr<IEntity> arg_entity);

        SceneBuilder& AddSpawnIndex(std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> arg_spawn_index);

        SceneBuilder& AddJumpIndex(std::vector<std::pair<int,int>> arg_jump_index) ;

        SceneBuilder& AddSprite(sf::Sprite arg_sprite);

        SceneBuilder& AddTexture(std::shared_ptr<sf::Texture> arg_texture);

        SceneBuilder& AddMusic(std::shared_ptr<sf::Music> arg_music);

        std::vector<std::shared_ptr<IEntity>> GetEntities();

        std::vector<std::shared_ptr<ISystem>> GetSystems();

        SceneBuilder& AddPath(std::string arg_file_path);

        Scene Build();
};