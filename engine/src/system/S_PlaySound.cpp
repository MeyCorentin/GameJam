#include "system/S_PlaySound.hpp"

std::vector<std::shared_ptr<IEntity>> S_PlaySound::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
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
        Scene * arg_scene)  {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);
    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
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