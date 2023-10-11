#include "System.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Position.hpp"

class S_Display : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->HasComponent(typeid(C_Sprite<std::shared_ptr<sf::Sprite>>)) &&
                    entity->HasComponent(typeid(C_Position<std::pair<double, double>>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures,
                std::shared_ptr<sf::Event> event_) override {
            std::shared_ptr<sf::Sprite> sprite_comp;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp;
            float x_position;
            float y_position;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                sprite_comp = entity->template GetComponent<C_Sprite<std::shared_ptr<sf::Sprite>>>()->getValue();
                position_comp = entity->template GetComponent<C_Position<std::pair<double, double>>>();
                x_position = static_cast<float>(position_comp->getValue().first);
                y_position = static_cast<float>(position_comp->getValue().second);
                sprite_comp->setPosition(x_position, y_position);
                arg_window->draw(*sprite_comp);
            }
        }
};
