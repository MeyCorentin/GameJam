#include "TSystem.hpp"
#include "../component/Life.hpp"

class HitSystem : public TSystem {
public:
    std::vector<TEntity> filter(const std::vector<TEntity>& entities) override {
        std::vector<TEntity> filteredEntities;
        for (const TEntity& entity : entities)
            if (entity.hasComponent(typeid(Life<int>)))
                filteredEntities.push_back(entity);
        return filteredEntities;
    }

    void execute(std::vector<TEntity>& entities) override {
        for (TEntity& entity : entities) {
            auto lifeComponent = entity.template getComponent<Life<int>>();
            int currentLife = lifeComponent->getValue();
            lifeComponent->setValue(currentLife - 1);
            std::cout << entity.getId() << ": get hit hp restant : " << lifeComponent->getValue() << std::endl;
        }
    }
};