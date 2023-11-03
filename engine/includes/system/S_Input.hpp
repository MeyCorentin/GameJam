#pragma once

#include "System.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_ChargedShoot.hpp"
#include "../components/C_ShootCharging.hpp"
#include "../components/C_IsMoving.hpp"
#include "../components/C_Size.hpp"
#include "../components/C_Admin.hpp"
#include "../components/C_Bonus.hpp"
#include "../components/C_PlayerAmmo.hpp"
#include "../components/C_Sprite.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../components/C_Inventory.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../components/C_Life.hpp"
#include "../components/C_Weapon.hpp"
#include "../components/C_PositionShot.hpp"
#include "../components/C_Sound.hpp"
#include "../components/C_SoundBuffer.hpp"
#include "../components/C_Music.hpp"
#include "../parser/jsonParser.hpp"
#include "../scene/SystemRegister.hpp"
#include "../scene/ComponentRegister.hpp"
#include "../scene/SceneBuilder.hpp"

class S_Input : public System {
    private:
        std::vector<int> inputs_ = {0, 0, 0, 0, 0, 0};
    public:
        std::vector<std::shared_ptr<Entity>> Filter(const std::vector<std::shared_ptr<Entity>>& arg_entities) override;

        json FindComponentConfigById(const json& arg_components_config, int arg_id);

        bool ProcessComponent(
                const json& arg_entityComponent,
                const json& arg_componentConfig,
                JsonParser& arg_parser,
                EntityBuilder& arg_entityBuilder);

        std::shared_ptr<Entity> CreateEntityFromConfig(
                const json& arg_entity_config,
                const json& arg_components_config);

        std::shared_ptr<Entity> createEntity(
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                int id,
                std::shared_ptr<C_Position<std::pair<double, double>>> arg_position_comp);

        void Execute(
                int arg_is_server,
                std::vector<std::shared_ptr<Entity>>& arg_entities,
                std::shared_ptr<sf::RenderWindow> arg_window,
                std::vector<int> arg_inputs,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::vector<std::shared_ptr<sf::Music>>& arg_music_list,
                std::shared_ptr<sf::Event> event_) override;

        void Move(
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                std::shared_ptr<sf::RenderWindow> arg_window,
                const std::shared_ptr<Entity>& entity,
                std::vector<std::shared_ptr<Entity>>& entity_list);

        void ChangeAdminMode(
                const std::shared_ptr<Entity>& entity,
                std::shared_ptr<sf::Event> event_);

        void CheckTouchPressed(
                const std::shared_ptr<Entity>& entity,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                std::shared_ptr<sf::Event> event_);

        void CheckTouchReleased(
                const std::shared_ptr<Entity>& entity,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                std::shared_ptr<sf::Event> event_);

        void BasicShot(
                const std::shared_ptr<Entity>& entity,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp);

        void SpecialShot(
                const std::shared_ptr<Entity>& entity,
                std::vector<std::shared_ptr<Entity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp);

};