#include "scene/SceneDirector.hpp"

std::shared_ptr<System> SceneDirector::CreateSystemFromConfig(const json& arg_systemConfig)
{
    std::string type = arg_systemConfig["type"];

    std::cout << type << std::endl;
    return SystemRegistry::Instance().CreateSystem(type);
}

std::shared_ptr<System> SceneDirector::CreateSystemFromType(std::string arg_type)
{
    return SystemRegistry::Instance().CreateSystem(arg_type);
}

const json& SceneDirector::FindComponentConfigById(
        const json& arg_componentsConfig,
        int arg_id) {
    static const json empty_json;

    for (const auto& component_config : arg_componentsConfig)
        if (component_config["id"] == arg_id)
            return component_config;
    return empty_json;
}


bool SceneDirector::ProcessComponent(
        const json& arg_entity_component,
        const json& arg_component_config,
        JsonParser& arg_parser,
        EntityBuilder& arg_entity_builder) {
    std::string component_name = arg_component_config["type"];
    std::string value_type = arg_component_config["value_type"];
    json component_value = arg_entity_component["value"];
    std::shared_ptr<ComponentBase> component = ComponentRegistry::Instance().CreateComponent(component_name);
    Variant value = arg_parser.ParseValue(value_type, component_value);

    if (!component)
        return false;
    std::cout << " - " << component_name << std::endl;
    if (value_type == "Sprite") {
        arg_entity_builder.AddComponent(component,  std::get<sf::Sprite>(value));
    } else if (value_type == "Texture") {
        arg_entity_builder.AddComponent(component, std::get<sf::Texture>(value));
    }  else if (value_type == "Int") {
        arg_entity_builder.AddComponent(component, std::get<int>(value));
    } else if (value_type == "PairDouble") {
        arg_entity_builder.AddComponent(component, std::get<std::pair<double, double>>(value));
    } else if (value_type == "PairInt") {
        arg_entity_builder.AddComponent(component, std::get<std::pair<int, int>>(value));
    } else if (value_type == "Bool") {
        arg_entity_builder.AddComponent(component, std::get<bool>(value));
    } else if (value_type == "Double") {
        arg_entity_builder.AddComponent(component, std::get<double>(value));
    } else if (value_type == "Clock") {
        arg_entity_builder.AddComponent(component, std::get<sf::Clock>(value));
    } else if (value_type == "IntRect") {
        arg_entity_builder.AddComponent(component, std::get<sf::IntRect>(value));
    } else if (value_type == "PairPairInt") {
        arg_entity_builder.AddComponent(component, std::get<std::pair<std::pair<int, int>, std::pair<int, int>>>(value));
    } else if (value_type == "VectorEntity") {
        arg_entity_builder.AddComponent(component, std::get<std::vector<std::shared_ptr<Entity>>>(value));
    } else if (value_type == "SinFunc") {
        arg_entity_builder.AddComponent(component, std::get<SinusoidalFunction>(value));
    } else if (value_type == "Sound") {
        arg_entity_builder.AddComponent(component, std::get<sf::Sound>(value));
    } else if (value_type == "SoundBuffer") {
        arg_entity_builder.AddComponent(component, std::get<sf::SoundBuffer>(value));
    } else if (value_type == "String") {
        std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
        scene_builder_.AddMusic(music);
        arg_entity_builder.AddComponent(component, std::get<std::string>(value));
    } else {
        std::cerr << "Unsupported component type: " << value_type << std::endl;
        return false;
    }
    return true;
}
std::shared_ptr<Entity> SceneDirector::CreateEntityFromConfig(
        const json& arg_entity_config,
        const json& arg_components_config) {
    JsonParser parser;
    int component_id;
    int entity_id = arg_entity_config["id"];
    EntityBuilder entity_builder(entity_id);
    const json& entity_components = arg_entity_config["components"];

    std::cout << "Create Entity: " << entity_id << std::endl;
    for (const auto& entity_component : entity_components) {
        component_id = entity_component["component_id"];
        const json& component_config = FindComponentConfigById(arg_components_config, component_id);
        if (component_config.is_null()) {
            return entity_builder.Build();
        }
        if (!ProcessComponent(entity_component, component_config, parser, entity_builder)) {
            return entity_builder.Build();
        }
    }
    return entity_builder.Build();
}

template <typename T>
T SceneDirector::getRandomInRange(T min, T max)
{
    if (max <= min)
        return min;

    std::mt19937_64 gen(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<long long> distribution(min, max);

    T nbr = (T)distribution(gen);

    return nbr;
}

std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> SceneDirector::CreateMap(const json& arg_spawn_config)
{
    std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> map;
    for (const auto& spawn_entry : arg_spawn_config)
    {
        int tick = spawn_entry.at("tick").get<int>();
        std::vector<std::pair<int, std::pair<int, int>> > entities;

        if (spawn_entry.find("mob_id") == spawn_entry.end())
            continue;
        for (const auto& entity : spawn_entry.at("mob_id"))
        {
            int id_value = entity.at("entity_id").get<int>();
            int x;
            int y;
            if (entity.find("position") != entity.end())
            {
                x = entity.at("position").at("x").get<int>();
                y = entity.at("position").at("y").get<int>();
            } else {
                x = 384;
                y = getRandomInRange(0,180);
            }
            entities.push_back(std::make_pair(id_value, std::make_pair(x, y)));
        }

        map.push_back(std::make_pair(tick, entities));
    }
    return map;
}


std::vector<std::pair<int,int>> SceneDirector::CreateJump(const json& arg_spawn_config)
{
    std::vector<std::pair<int, int>> jump;
    for (const auto& spawn_entry : arg_spawn_config)
    {


        if (spawn_entry.find("jump") == spawn_entry.end())
            continue;
        int tick = spawn_entry.at("tick").get<int>();
        int jump_value = spawn_entry.at("jump").get<int>();

        jump.push_back(std::make_pair(tick, jump_value));
    }
    return jump;
}


bool checkRequiredFilesExist(const std::string& arg_folder_path) {
    std::filesystem::path folder_path(arg_folder_path);

    // Check if the required folders and files exist
    if (!std::filesystem::exists(folder_path / "scenes/scene_start" / "timeline.json")) {
        std::cout << "Missing file: scenes/scene_start/timeline.json" << std::endl;
        return false;
    }
    if (!std::filesystem::exists(folder_path / "scenes/scene_start" / "systems.json")) {
        std::cout << "Missing file: scenes/scene_start/systems.json" << std::endl;
        return false;
    }
    if (!std::filesystem::exists(folder_path / "entities" / "entities.json")) {
        std::cout << "Missing file: entities/entities.json" << std::endl;
        return false;
    }
    if (!std::filesystem::exists(folder_path / "systems" / "systems.json")) {
        std::cout << "Missing file: systems/systems.json" << std::endl;
        return false;
    }
    if (!std::filesystem::exists(folder_path / "components" / "components.json")) {
        std::cout << "Missing file: components/components.json" << std::endl;
        return false;
    }

    return true;
}

SceneDirector::SceneDirector() {}

SceneDirector::SceneDirector(std::string arg_file_path, int value) {
    if (checkRequiredFilesExist(arg_file_path))
    {

        std::cout << "------[LOAD SYSTEMS]-------" << std::endl;
        std::string systemsFilePath = arg_file_path + "/scenes/scene_start/systems.json";
        std::ifstream file(systemsFilePath);
        json systems_needed;
        file >> systems_needed;
        file.close();
        for (const auto& systemId : systems_needed["systems"]) {
            std::string systemsJsonPath = arg_file_path + "/systems/systems.json";
            std::ifstream systemsJsonFile(systemsJsonPath);
            if (systemsJsonFile.is_open()) {
                json systemsJsonData;
                systemsJsonFile >> systemsJsonData;
                systemsJsonFile.close();
                for (const auto& system : systemsJsonData["systems"]) {
                    if (system["id"] == systemId) {
                        std::string systemPath = system["path"];
                        json type;
                        std::string systemsFinalJsonPath = arg_file_path + "/systems/" + systemPath;
                        std::ifstream systemsFinalJsonFile(systemsFinalJsonPath);
                        if (systemsFinalJsonFile.is_open())
                        {
                            systemsFinalJsonFile >> type;
                            systemsFinalJsonFile.close();
                            std::cout << "ID: " << systemId << ", Path: " << systemPath << ", Type: " << type["type"]  << std::endl;
                            scene_builder_.AddSystem(CreateSystemFromType(type["type"]));
                        }
                        break;
                    }
                }
            }
        }

        std::cout << "------[LOAD ENTITIES]-------" << std::endl;

        std::string systemsFilePath = arg_file_path + "/scenes/scene_start/systems.json";
        std::ifstream file(systemsFilePath);
        json systems_needed;
        file >> systems_needed;
        file.close();

        std::string timelineFilePath = arg_file_path + "/scenes/scene_start/timeline.json";
        std::ifstream file_timeline(timelineFilePath);
        json timelineData;
        file_timeline >> timelineData;
        file_timeline.close();

        // Extraction des entity_id uniques
        std::set<int> uniqueEntityIds;
        for (const auto& spawnObject : timelineData["spawn"]) {
            std::cout << "test" << std::endl;
            // if (spawnObject.is_object() && spawnObject.contains("mob_id") && spawnObject["mob_id"].is_array()) {
            //     const auto& mobIdArray = spawnObject["mob_id"];
            //     for (const auto& entityObject : mobIdArray) {
            //         if (entityObject.is_object() && entityObject.contains("entity_id") && entityObject["entity_id"].is_number()) {
            //             uniqueEntityIds.insert(entityObject["entity_id"].get<int>());
            //         }
            //     }
            // }
        }

        // Affichage des entity_id uniques
        std::cout << "Unique Entity IDs:" << std::endl;
        for (const auto& entityId : uniqueEntityIds) {
            std::cout << entityId << std::endl;
        }


        // std::cout << "------[LOAD ENTITIES]-------" << std::endl;
        // for (const auto& entity_config : data["entities"]) {
        //     std::shared_ptr<Entity> new_entity = CreateEntityFromConfig(entity_config, data["components"]);
        //     if (new_entity->HasComponent(typeid(C_SpriteRect<sf::IntRect>)) &&
        //         new_entity->HasComponent(typeid(C_Sprite<sf::Sprite>))) {
        //         std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
        //         std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
        //         sprite->getValue().setTextureRect(rect->getValue());
        //     }
        //     scene_builder_.AddEntity(new_entity);
        // }

        // scene_builder_.AddSpawnIndex(CreateMap(data["spawn"]));
        // scene_builder_.AddJumpIndex(CreateJump(data["spawn"]));
    }
}

Scene SceneDirector::ConstructScene() {
    std::cout << "[CONSTRUCTOR] Scene construct" << std::endl;
    return scene_builder_.Build();
}