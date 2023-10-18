#pragma once

#include "../main.hpp"
#include "../entity/EntityBuilder.hpp"
#include "../system/System.hpp"
#include "../components/C_SinClock.hpp"
#include "../components/C_Clock.hpp"
#include "../components/C_Player.hpp"
#include "../components/C_Position.hpp"
#include "../components/C_SpriteRect.hpp"
#include "../components/C_Hitbox.hpp"
#include "../components/C_Sprite.hpp"

class Scene {
    private:
        std::shared_ptr<sf::RenderWindow> window_;
        std::shared_ptr<sf::Event> event_;
        std::vector<std::shared_ptr<Entity>> list_entities_;
        std::vector<std::shared_ptr<Entity>> entities_;
        std::vector<std::shared_ptr<System>> systems_;
        std::vector<sf::Sprite> sprites_;
        std::vector<std::shared_ptr<sf::Texture>> textures_;
        std::vector<std::shared_ptr<sf::Music>> musics_;
        std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> spawn_index_;
        int frames_this_second_;
        int total_ticks_;
        std::unordered_map<sf::Keyboard::Key, int> key_states_;
        std::shared_ptr<sf::Clock> second_clock_;
        std::shared_ptr<sf::Text> tick_;
        std::shared_ptr<sf::Text> entities_nbr_;
        std::shared_ptr<sf::Font> font_;
        std::shared_ptr<sf::Text> current_tick_;

        int time_pressed_;
        bool is_pressed_ = false;
        std::vector<int> inputs_ = {0, 0, 0, 0, 0};

    public:
        bool running = true;
        double targetFrameTime = (1.0 / 60);
        Scene();
        Scene( std::vector<std::shared_ptr<System>> arg_system_list,
                std::vector<std::shared_ptr<Entity>> arg_entity_list,
                std::vector<sf::Sprite> arg_sprite_list,
                std::vector<std::shared_ptr<sf::Texture>> arg_texture_list,
                std::vector<std::shared_ptr<sf::Music>> arg_music_list,
                std::vector<std::pair<int, std::vector<std::pair<int, std::pair<int, int>>>>> arg_spawn_index);

        void ClearWindow();

        std::vector<std::shared_ptr<Entity>> GetEntities();

        std::vector<std::shared_ptr<System>> GetSystems();

        void DisplayCurrentTick();

        void DisplayEntities(int nbr);

        void DisplayTicks();


        void AddNewPlayer(int arg_id);

    void InputFromPlayer(std::pair<int,int> arg_message);

    void Update(int arg_is_server);
};
