#include "System.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Position.hpp"

class S_Display : public System {
    public:
        std::vector<std::shared_ptr<Entity>> filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->hasComponent(typeid(C_Sprite<std::shared_ptr<sf::Sprite>>)) &&
                    entity->hasComponent(typeid(C_Position<std::pair<double, double>>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void execute(
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) override {
            std::shared_ptr<sf::Sprite> sprite_comp;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
            float x_position;
            float y_position;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                sprite_comp = entity->template getComponent<C_Sprite<std::shared_ptr<sf::Sprite>>>()->getValue();
                position_comp = entity->template getComponent<C_Position<std::pair<double, double>>>();
                x_position = static_cast<float>(position_comp->getValue().first);
                y_position = static_cast<float>(position_comp->getValue().second);
                sprite_comp->setPosition(x_position, y_position);
                arg_window->draw(*sprite_comp);
            }
        }
};
