#include "TSystem.hpp"
#include "../components/Sprite.hpp"
#include "../components/Clock.hpp"
#include "../components/SpriteRect.hpp"
#include "../components/Size.hpp"
#include "../components/Animation.hpp"

class AnimationSystem : public TSystem {
    public:
        std::vector<std::shared_ptr<TEntity>> filter(const std::vector<std::shared_ptr<TEntity>>& _entities) override {
            std::vector<std::shared_ptr<TEntity>> filteredEntities;
            for (const std::shared_ptr<TEntity>& entity : _entities) {
                if (entity->hasComponent(typeid(Sprite<std::shared_ptr<sf::Sprite>>)) &&
                    entity->hasComponent(typeid(Clock<std::shared_ptr<sf::Clock>>)) &&
                    entity->hasComponent(typeid(SpriteRect<std::shared_ptr<sf::IntRect>>)) &&
                    entity->hasComponent(typeid(Size<std::pair<int, int>>)) &&
                    entity->hasComponent(typeid(Animation<bool>))) {
                    filteredEntities.push_back(entity);
                }
            }
            return filteredEntities;
        }

        void execute(std::vector<std::shared_ptr<TEntity>>& _entities, std::shared_ptr<sf::RenderWindow> _window, std::vector<int> _inputs, std::vector<std::shared_ptr<TEntity>>& allEntities, std::vector<std::shared_ptr<sf::Sprite>>& sprites, std::vector<std::shared_ptr<sf::Texture>>& textures) override {
            for (const std::shared_ptr<TEntity>& entity : _entities) {
                std::shared_ptr<sf::Sprite> sprite = entity->template getComponent<Sprite<std::shared_ptr<sf::Sprite>>>()->getValue();
                std::shared_ptr<sf::Clock> clock = entity->template getComponent<Clock<std::shared_ptr<sf::Clock>>>()->getValue();
                std::shared_ptr<sf::IntRect> rect = entity->template getComponent<SpriteRect<std::shared_ptr<sf::IntRect>>>()->getValue();
                std::pair<int, int> size = entity->template getComponent<Size<std::pair<int, int>>>()->getValue();
                bool animaion = entity->template getComponent<Animation<bool>>()->getValue();
                if (clock->getElapsedTime().asSeconds() > 0.1f) {
                    if (rect->left >= size.first) {
                        rect->left = 0;
                    } else {
                        rect->left += rect->width;
                    }
                    sprite->setTextureRect(*rect);
                    clock->restart();
                }
            }
        }
};

