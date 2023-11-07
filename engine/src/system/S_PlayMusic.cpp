#include "system/S_PlayMusic.hpp"

std::vector<std::shared_ptr<IEntity>> S_PlayMusic::Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) {
    std::vector<std::shared_ptr<IEntity>> filtered_entities;

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        if (entity->HasComponent(typeid(C_Music<std::string>)) &&
            entity->HasComponent(typeid(C_MusicIsActive<bool>))) {
            filtered_entities.push_back(entity);
        }
    }
    return filtered_entities;
}

void S_PlayMusic::Execute(
        int arg_is_server,
        Scene * arg_scene)  {
    std::vector<std::shared_ptr<IEntity>> arg_entities =  Filter(arg_scene->entities_);

    for (const std::shared_ptr<IEntity>& entity : arg_entities) {
        std::shared_ptr<C_Music<std::string>> music_path = entity->template GetComponent<C_Music<std::string>>();
        std::shared_ptr<C_MusicIsActive<bool>> is_active = entity->template GetComponent<C_MusicIsActive<bool>>();

        auto music = arg_scene->musics_.begin();

        if (!is_active->getValue()) {
            (*music)->setVolume(30);
            if (!(*music)->openFromFile(music_path->getValue()))
                std::cerr << "Failed to open file : " << music_path->getValue() << std::endl;
            (*music)->play();
            is_active->getValue() = true;
        }
    }
}