
#include "../includes/main.hpp"
#include "../includes/system/System.hpp"
#include "../includes/system/S_Position.hpp"
#include "../includes/system/S_Hit.hpp"
#include "../includes/system/S_Display.hpp"
#include "../includes/system/S_Input.hpp"
#include "../includes/system/S_Mana.hpp"
#include "../includes/system/S_Collision.hpp"
#include "../includes/system/S_Mouvement.hpp"
#include "../includes/system/S_Animation.hpp"
#include "../includes/system/S_Target.hpp"
#include "../includes/system/S_KillEntity.hpp"
#include "../includes/system/S_Parallax.hpp"
#include "../includes/system/S_SinMoov.hpp"
#include "../includes/system/S_MakeBaby.hpp"
#include "../includes/system/S_PlaySound.hpp"
#include "../includes/system/S_PlayMusic.hpp"

#include "../includes/components/C_Life.hpp"
#include "../includes/components/C_Player.hpp"
#include "../includes/components/C_Sprite.hpp"
#include "../includes/components/C_Position.hpp"
#include "../includes/components/C_Direction.hpp"
#include "../includes/components/C_Speed.hpp"
#include "../includes/components/C_Mana.hpp"
#include "../includes/components/C_Shoot.hpp"
#include "../includes/components/C_Target.hpp"
#include "../includes/components/C_Follow.hpp"
#include "../includes/components/C_Background.hpp"
#include "../includes/components/C_Animation.hpp"
#include "../includes/components/C_Server.hpp"
#include "../includes/components/C_Client.hpp"
#include "../includes/components/C_Size.hpp"
#include "../includes/components/C_SinMoov.hpp"
#include "../includes/components/C_SpriteRect.hpp"
#include "../includes/components/C_Clock.hpp"
#include "../includes/components/C_FireRate.hpp"
#include "../includes/components/C_Parallax.hpp"
#include "../includes/components/C_ParallaxClock.hpp"
#include "../includes/components/C_Range.hpp"
#include "../includes/components/C_FireRateSpeed.hpp"
#include "../includes/components/C_ChargedShoot.hpp"
#include "../includes/components/C_ShootCharging.hpp"
#include "../includes/components/C_PlayerAmmo.hpp"
#include "../includes/components/C_SinClock.hpp"
#include "../includes/components/C_IsMoving.hpp"
#include "../includes/components/C_Child.hpp"
#include "../includes/components/C_Ammo.hpp"
#include "../includes/components/C_Admin.hpp"
#include "../includes/components/C_Inventory.hpp"
#include "../includes/components/C_UniqueAnimation.hpp"
#include "../includes/components/C_PositionEnd.hpp"
#include "../includes/components/C_PositionStart.hpp"
#include "../includes/components/C_Texture.hpp"
#include "../includes/components/C_Bonus.hpp"
#include "../includes/components/C_BonusPower.hpp"
#include "../includes/components/C_PositionFollow.hpp"
#include "../includes/components/C_Weapon.hpp"
#include "../includes/components/C_PositionShot.hpp"
#include "../includes/components/C_Sound.hpp"
#include "../includes/components/C_SoundBuffer.hpp"
#include "../includes/components/C_SoundIsActive.hpp"
#include "../includes/components/C_Music.hpp"
#include "../includes/components/C_MusicIsActive.hpp"
#include "../includes/components/C_PlayerMovementClock.hpp"
#include "../includes/components/ComponentBase.hpp"

#include "../includes/scene/SystemRegister.hpp"
#include "../includes/scene/ComponentRegister.hpp"
#include "../includes/scene/SceneBuilder.hpp"
#include "../includes/scene/SceneDirector.hpp"

class Ecs
{
    public:
        Scene scene_;

        Ecs(int ac, char **av);

        Ecs();

        void Update(int arg_is_server);

        void Create(int arg_is_server);
};