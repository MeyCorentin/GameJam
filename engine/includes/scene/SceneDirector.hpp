#include "SceneBuilder.hpp"

class SceneDirector {
    private:
        SceneBuilder sceneBuilder;
        std::vector<std::shared_ptr<TSystem>> systems;
        std::vector<std::shared_ptr<TEntity>> entities;

    void createSystemFromConfig(const json& systemConfig)
    {
        std::cout << "Create System" << std::endl;
    }

    void createComponentFromConfig(const json& componentConfig)
    {
        std::cout << "Create Component" << std::endl;

    }

    void createEntityFromConfig(const json& entityConfig)
    {
        std::cout << "Create Entity" << std::endl;

    }
    public:
        SceneDirector(std::string file_path) { 
                std::ifstream file(file_path);
                json data;
                file >> data;
                file.close();
                for (const auto& systemConfig : data["systems"]) {
                    createSystemFromConfig(systemConfig);
                }
                for (const auto& componentConfig : data["components"]) {
                    createComponentFromConfig(componentConfig);
                }

                for (const auto& entityConfig : data["entities"]) {
                    createEntityFromConfig(entityConfig);
                }
        }

        TScene constructScene() {
            return sceneBuilder.build();
        }
};