#pragma once

#include "ISystem.hpp"
#include "../scene/Scene.hpp"
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
#include "../components/C_EntityMovementClock.hpp"
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
#include "../components/C_PlayerMovementClock.hpp"
#include "../components/C_Music.hpp"
#include "../components/C_Follow.hpp"
#include "../components/C_TimeAutoMove.hpp"
#include "../components/C_ClockAutoMove.hpp"
#include "../components/C_IsAutoMove.hpp"
#include "../parser/jsonParser.hpp"
#include "../scene/SystemRegister.hpp"
#include "../scene/ComponentRegister.hpp"
#include "../scene/SceneBuilder.hpp"
#include "../components/C_Grounded.hpp"
#include "../components/C_PlayerAmmo.hpp"

class S_BasicInput : public ISystem {
    private:
    public:
        std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities) override;



        void DrawEntityID(
            std::shared_ptr<sf::RenderWindow> arg_window,
            const std::shared_ptr<IEntity>& entity,
            sf::Font arg_font,
            sf::Text arg_entity_id);


        void DrawEntityHitbox(
            std::shared_ptr<sf::RenderWindow> arg_window,
            const std::shared_ptr<IEntity>& entity,
            sf::Color outlineColor);

        void Execute(
                int arg_is_server,
                Scene * arg_scene) override;

        void Move(
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                Scene * arg_scene,
                const std::shared_ptr<IEntity>& entity,
                std::vector<std::shared_ptr<IEntity>>& entity_list,
                sf::Font arg_font,
                sf::Text arg_entity_id,
                sf::Time elapsed);

        void ChangeAdminMode(
                const std::shared_ptr<IEntity>& entity,
                std::shared_ptr<sf::Event> event_);

        void CheckTouchReleased(
            const std::shared_ptr<IEntity>& entity,
            std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
            std::shared_ptr<sf::Event> event_,
            Scene * arg_scene);

        void CheckTouchPressed(
                const std::shared_ptr<IEntity>& entity,
                std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                std::shared_ptr<sf::Event> event_,
                Scene * arg_scene);

        void BasicShot(
                const std::shared_ptr<IEntity>& entity,
                std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                Scene * arg_scene);

};