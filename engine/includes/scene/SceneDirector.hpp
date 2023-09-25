#include "SceneBuilder.hpp"

class SceneDirector {
    private:
        SceneBuilder* builder;
    public:
        void set_builder(SceneBuilder* builder){
            this->builder=builder;
        }
};