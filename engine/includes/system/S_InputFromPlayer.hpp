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


class S_InputFromPlayer : public ISystem {
    private:
    public:
        std::vector<std::shared_ptr<IEntity>> Filter(const std::vector<std::shared_ptr<IEntity>>& arg_entities);
        void Execute(
                int arg_is_server,
                Scene * arg_scene);

        void BasicShot(
                const std::shared_ptr<IEntity>& entity,
                std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                Scene * arg_scene);

        void SpecialShot(
                const std::shared_ptr<IEntity>& entity,
                std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                Scene * arg_scene);

        void DeleteFromInventory(
                int base_id,
                const std::shared_ptr<IEntity>& entity,
                std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
                std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
                Scene * arg_scene);

        bool IsInInventory(
            int base_id,
            const std::shared_ptr<IEntity>& entity,
            std::vector<std::shared_ptr<IEntity>>& arg_all_entities,
            std::shared_ptr<C_Position<std::pair<double, double>>> position_comp,
            Scene * arg_scene);
};
