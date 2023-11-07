#include "scene/SceneDirector.hpp"

std::shared_ptr<ISystem> SceneDirector::CreateSystemFromConfig(const json& arg_systemConfig)
{
    std::string type = arg_systemConfig["type"];

    // std::cout << type << std::endl;
    return SystemRegistry::Instance().CreateSystem(type);
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
    std::shared_ptr<IComponent> component = ComponentRegistry::Instance().CreateComponent(component_name);
    Variant value = arg_parser.ParseValue(value_type, component_value);

    if (!component)
        return false;
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
        arg_entity_builder.AddComponent(component, std::get<std::vector<std::shared_ptr<IEntity>>>(value));
    } else if (value_type == "SinFunc") {
        arg_entity_builder.AddComponent(component, std::get<SinusoidalFunction>(value));
    } else if (value_type == "Sound") {
        arg_entity_builder.AddComponent(component, std::get<sf::Sound>(value));
    } else if (value_type == "SoundBuffer") {
        arg_entity_builder.AddComponent(component, std::get<sf::SoundBuffer>(value));
    } else if (value_type == "Text") {
        arg_entity_builder.AddComponent(component, std::get<sf::Text>(value));
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
std::shared_ptr<IEntity> SceneDirector::CreateEntityFromConfig(
        const json& arg_entity_config,
        const json& arg_components_config) {
    JsonParser parser;
    int component_id;
    int entity_id = arg_entity_config["id"];
    EntityBuilder entity_builder(entity_id);
    const json& entity_components = arg_entity_config["components"];

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


SceneDirector::SceneDirector() {}

SceneDirector::SceneDirector(std::string arg_file_path, int value) {
    std::ifstream file(arg_file_path);
    json data;

    file >> data;
    file.close();

    std::string directory = arg_file_path.substr(0, arg_file_path.find_last_of("/\\"));
    std::string timeline_file_path = directory + "/" + data["timeline"][0]["1"].get<std::string>();
    std::ifstream timeline_file(timeline_file_path);
    json timeline_data;
    timeline_file >> timeline_data;
    timeline_file.close();

    std::cout << "------[LOAD SYSTEMS]-------" << std::endl;
    for (const auto& system_config : data["systems"])
        scene_builder_.AddSystem(CreateSystemFromConfig(system_config));
    std::cout << "------[LOAD ENTITIES]-------" << std::endl;
    for (const auto& entity_config : data["entities"]) {
        std::shared_ptr<IEntity> new_entity = CreateEntityFromConfig(entity_config, data["components"]);
        if (new_entity->HasComponent(typeid(C_SpriteRect<sf::IntRect>)) &&
            new_entity->HasComponent(typeid(C_Sprite<sf::Sprite>))) {
            std::shared_ptr<C_SpriteRect<sf::IntRect>> rect = new_entity->template GetComponent<C_SpriteRect<sf::IntRect>>();
            std::shared_ptr<C_Sprite<sf::Sprite>> sprite = new_entity->template GetComponent<C_Sprite<sf::Sprite>>();
            sprite->getValue().setTextureRect(rect->getValue());
        }
        scene_builder_.AddEntity(new_entity);
    }

    scene_builder_.AddSpawnIndex(CreateMap(timeline_data["spawn"]));
    scene_builder_.AddJumpIndex(CreateJump(timeline_data["spawn"]));
}

Scene SceneDirector::ConstructScene(std::string arg_file_path) {
    std::cout << "[CONSTRUCTOR] Scene construct" << std::endl;
    scene_builder_.AddPath(arg_file_path);
    return scene_builder_.Build();
}