#include "System.hpp"
#include "../components/C_Mana.hpp"

class S_Mana : public System {
    public:
        std::vector<std::shared_ptr<Entity>> filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->hasComponent(typeid(C_Mana<int>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void execute(
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int>arg_input,
                std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) override {
            int current_mana;
            std::shared_ptr<C_Mana<int>> mana_comp;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                mana_comp = entity->template getComponent<C_Mana<int>>();
                current_mana = mana_comp->getValue();
                mana_comp->setValue(current_mana + 1);
            }
        }
};