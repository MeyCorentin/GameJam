#pragma once

#include "../main.hpp"
#include "../entity/TEntity.hpp"

class TSystem {

    public:
        virtual ~TSystem() {}

        void compute(std::vector<TEntity>& entities) {
            entities = filter(entities);
            execute(entities);
        }

        virtual std::vector<TEntity> filter(const std::vector<TEntity>& entities) = 0;
        virtual void execute(std::vector<TEntity>& entities) = 0;
};
