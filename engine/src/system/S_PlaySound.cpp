#include "system/S_PlaySound.hpp"

std::vector<std::shared_ptr<Entity>> S_PlaySound::Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) {
    std::vector<std::shared_ptr<Entity>> filtered_entities;

    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Sound<sf::Sound>)) &&
            entity->HasComponent(typeid(C_SoundIsActive<bool>)) &&
            entity->HasComponent(typeid(C_SoundBuffer<sf::SoundBuffer>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_PlaySound::Execute(
        int arg_is_server,
        std::vector<std::shared_ptr<Entity>>& arg_entities,
        std::shared_ptr<sf::RenderWindow> arg_window,
        std::vector<int> arg_inputs,
        std::vector<std::shared_ptr<Entity>>& arg_all_entities,
        std::vector<sf::Sprite>& arg_sprites,
        std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
        std::shared_ptr<sf::Event> event_)  {
    for (const std::shared_ptr<Entity>& entity : arg_entities) {
        std::shared_ptr<C_Sound<sf::Sound>> sound = entity->template GetComponent<C_Sound<sf::Sound>>();
        std::shared_ptr<C_SoundBuffer<sf::SoundBuffer>> buffer = entity->template GetComponent<C_SoundBuffer<sf::SoundBuffer>>();
        std::shared_ptr<C_SoundIsActive<bool>> is_active = entity->template GetComponent<C_SoundIsActive<bool>>();

        if (is_active->getValue()) {
            sound->getValue().setBuffer(buffer->getValue());
            sound->getValue().play();
            is_active->getValue() = false;
        }
    }
}