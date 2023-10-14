#include "scene/SceneBuilder.hpp"


SceneBuilder& SceneBuilder::AddSystem(std::shared_ptr<System> arg_system) {
    systems_.push_back(arg_system);
    return *this;
}

SceneBuilder& SceneBuilder::AddEntity(std::shared_ptr<Entity> arg_entity) {
    entities_.push_back(arg_entity);
    return *this;
}

SceneBuilder& SceneBuilder::AddSpawnIndex(std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> arg_spawn_index) {
    spawn_index_ = arg_spawn_index;
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

std::vector<std::shared_ptr<Entity>> SceneBuilder::GetEntities()
{
    return  entities_;
}

std::vector<std::shared_ptr<System>> SceneBuilder::GetSystems()
{
    return systems_;
}

Scene SceneBuilder::Build() {
    std::cout << "[BUILDER] Scene build" << std::endl;
    Scene scene(systems_, entities_, sprites_, textures_, spawn_index_);
    return scene;
}