#pragma once

#include "ComponentRegister.hpp"
#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../system/ISystem.hpp"
#include "../components/C_SinClock.hpp"
#include "../components/C_Clock.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_EntityMovementClock.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_ShootCharging.hpp"
#include "../components/C_Inventory.hpp"
#include "../components/C_ChargedShoot.hpp"
#include "../components/C_PositionShot.hpp"
#include "../components/C_Target.hpp"
#include "../components/C_ParallaxClock.hpp"
#include "../parser/jsonParser.hpp"

class Scene {
    private:
    public:
        std::shared_ptr<sf::RenderWindow> window_;
        std::shared_ptr<sf::Event> event_;
        std::vector<std::shared_ptr<IEntity>> list_entities_;
        std::vector<std::shared_ptr<IEntity>> entities_;
        std::vector<std::shared_ptr<ISystem>> systems_;
        std::vector<sf::Sprite> sprites_;
        std::vector<std::pair<int,int>> messages_;
        std::vector<std::shared_ptr<sf::Music>> musics_;
        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> spawn_index_;
        std::vector<std::pair<int,int>> jump_index_;
        std::unordered_map<sf::Keyboard::Key, int> key_states_;
        std::shared_ptr<sf::Clock> second_clock_;
        std::shared_ptr<sf::Text> tick_;
        std::shared_ptr<sf::Text> entities_nbr_;
        std::shared_ptr<sf::Font> font_;
        std::shared_ptr<sf::Text> current_tick_;
        std::string filepath_;
        json data_;

        bool need_switch_;
        std::string next_timeline_;
        int frames_this_second_;
        int total_ticks_;
        int time_pressed_;
        bool is_pressed_ = false;
        std::vector<int> inputs_ = {0, 0, 0, 0, 0, 0, 0};
        int id_store_ = 0;
        bool running = true;
        double targetFrameTime = (1.0 / 60);


        void CheckSwitchTimeline();


        void LoadSettings();

        Scene();
        Scene( std::vector<std::shared_ptr<ISystem>> arg_system_list,
                std::vector<std::shared_ptr<IEntity>> arg_entity_list,
                std::vector<sf::Sprite> arg_sprite_list,
                std::vector<std::shared_ptr<sf::Music>> arg_music_list,
                std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> arg_spawn_index,
                std::vector<std::pair<int,int>> arg_jump_index,
                std::string arg_file_path);

        json FindComponentConfigById(const json& arg_components_config, int arg_id);

        bool ProcessComponent(
                const json& arg_entityComponent,
                const json& arg_componentConfig,
                JsonParser& arg_parser,
                EntityBuilder& arg_entityBuilder);

        std::shared_ptr<IEntity> CreateEntityFromConfig(
                const json& arg_entity_config,
                const json& arg_components_config);

        std::shared_ptr<IEntity> createEntity(
                std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
                int id,
                std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp);

        void ClearWindow();

        std::vector<std::shared_ptr<IEntity>> GetEntities();

        std::vector<std::shared_ptr<ISystem>> GetSystems();

        void DisplayCurrentTick();

        void DisplayEntities(int nbr);

        void DisplayTicks();

        void AddNewPlayer(int arg_id);

        std::vector<EntityPosition> GetPlayerPosition();

        std::vector<EntityPosition> GetEntityPosition();

        void InputFromPlayer(std::pair<int,int> arg_message);

        void SetPlayerPosition(int id, float x, float y);

        void SetClientPlayerId(int arg_id);

        void Update(int arg_is_server);

        void ComputeSystems(int arg_is_server);

        std::vector<std::shared_ptr<IEntity>> SpawnEntities(int arg_is_server);

        void JumpTicks();

        void RemoveOrCreateEntities();

        template <typename T>
        T getRandomInRange(T min, T max);

        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> CreateMap(const json& arg_spawn_config);

        std::vector<std::pair<int,int>> CreateJump(const json& arg_spawn_config);

        void LoadTimeline(
                const std::string& timeline_id);
};
