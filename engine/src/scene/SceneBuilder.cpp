#include "scene/SceneBuilder.hpp"



SceneBuilder& SceneBuilder::AddPath(std::string arg_file_path) {
    path_ = arg_file_path;
    return *this;
}


SceneBuilder& SceneBuilder::AddSystem(std::shared_ptr<ISystem> arg_system) {
    systems_.push_back(arg_system);
    return *this;
}

SceneBuilder& SceneBuilder::AddEntity(std::shared_ptr<IEntity> arg_entity) {
    entities_.push_back(arg_entity);
    return *this;
}

SceneBuilder& SceneBuilder::AddSpawnIndex(std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> arg_spawn_index) {
    spawn_index_ = arg_spawn_index;
    return *this;
}


SceneBuilder& SceneBuilder::AddJumpIndex(std::vector<std::pair<int,int>> arg_jump_index) {
    jump_index_ = arg_jump_index;
    return *this;
}


SceneBuilder& SceneBuilder::AddSprite(sf::Sprite arg_sprite) {
    sprites_.push_back(arg_sprite);
    return *this;
}

SceneBuilder& SceneBuilder::AddTexture(std::shared_ptr<sf::Texture> arg_texture) {
    textures_.push_back(arg_texture);
    return *this;
}

SceneBuilder& SceneBuilder::AddMusic(std::shared_ptr<sf::Music> arg_music) {
    music_.push_back(arg_music);
    return *this;
}

std::vector<std::shared_ptr<IEntity>> SceneBuilder::GetEntities()
{
    return  entities_;
}

std::vector<std::shared_ptr<ISystem>> SceneBuilder::GetSystems()
{
    return systems_;
}

Scene SceneBuilder::Build() {
    std::cout << "[BUILDER] Scene build" << std::endl;
    Scene scene(systems_, entities_, sprites_, music_, spawn_index_, jump_index_, path_);
    return scene;
}