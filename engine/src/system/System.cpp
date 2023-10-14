#include "system/System.hpp"

void System::Compute(
    int arg_is_server,
    std::vector<std::shared_ptr<Entity>>& arg_entities,
    std::shared_ptr<sf::RenderWindow> arg_window,
    std::vector<int> arg_inputs,
    std::vector<sf::Sprite>& arg_sprites,
    std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
    std::shared_ptr<sf::Event> event_) {
        std::vector<std::shared_ptr<Entity>> entities = Filter(arg_entities);
        Execute(arg_is_server, entities, arg_window, arg_inputs, arg_entities, arg_sprites, arg_textures, event_);
}