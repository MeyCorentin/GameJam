#pragma once

#include "Component.hpp"
#include <SFML/Audio.hpp>

class C_Sound : public ComponentBase {
public:
    C_Sound() {}
    C_Sound(const sf::SoundBuffer& buffer) {
        sound.setBuffer(buffer);
    }
    const std::type_info& GetType() const override {
        return typeid(C_Sound);
    }
    std::shared_ptr<ComponentBase> Clone() const override {
        return std::make_shared<C_Sound>(*this);
    }
    void Play() {
        sound.play();
    }
private:
    sf::Sound sound;
};
