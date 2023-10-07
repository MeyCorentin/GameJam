#include "System.hpp"
#include "../components/C_Target.hpp"
#include "../components/C_Follow.hpp"
#include "../components/C_Position.hpp"

class S_Target : public System {
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override {
            std::vector<std::shared_ptr<Entity>> filtered_entities;

            for (const std::shared_ptr<Entity>& entity : arg_entities) {
                if (entity->HasComponent(typeid(C_Target<int>))) {
                    filtered_entities.push_back(entity);
                }
            }
            return filtered_entities;
        }

        void Execute(
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int>arg_input,
                std::vector<std::shared_ptr<Entity>>& arg_all_Entities,
                std::vector<std::shared_ptr<sf::Sprite>>& arg_sprites,
                std::vector<std::shared_ptr<sf::Texture>>& arg_textures) override {
            int current_mana;
            std::shared_ptr<C_Target<int>> target;
            std::shared_ptr<C_Follow<bool>> follow;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_1;
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp_2;

            for (const std::shared_ptr<Entity>& entity1 : arg_entities) {
                for (const std::shared_ptr<Entity>& entity2 : arg_all_Entities) {
                    target = entity1->template GetComponent<C_Target<int>>();
                    follow = entity1->template GetComponent<C_Follow<bool>>();
                    position_comp_1 = entity1->template GetComponent<C_Position<std::pair<double, double>>>();
                    position_comp_2 = entity2->template GetComponent<C_Position<std::pair<double, double>>>();

                    if (entity1 == entity2)
                        continue;
                    if (follow && position_comp_1 && position_comp_2 && target->getValue() == entity2->GetId())
                    {
                        std::cout << "OKKK" << std::endl;
                        position_comp_1->getValue().first = position_comp_2->getValue().first;
                        position_comp_1->getValue().second = position_comp_2->getValue().second;
                    }
                }
            }
        }
};