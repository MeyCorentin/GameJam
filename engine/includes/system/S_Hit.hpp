#include "System.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_Shield.hpp"

class S_Hit : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->HasComponent(typeid(C_Life<int>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_input,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<sf::Sprite>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::shared_ptr<sf::Event> event_) override {
            int current_shield;
            int current_life;
            std::shared_ptr<C_Shield<int>> shield_comp;
            std::shared_ptr<C_Life<int>> life_comp;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                shield_comp = entity->template GetComponent<C_Shield<int>>();
                if (shield_comp && shield_comp->getValue() > 0) {
                    current_shield = shield_comp->getValue();
                    shield_comp->setValue(current_shield - 1);
                } else {
                    life_comp = entity->template GetComponent<C_Life<int>>();
                    current_life = life_comp->getValue();
                    life_comp->setValue(current_life - 1);
                }
            }
        }
};
