#pragma once

#include <iostream>
#include <SFML/Graphics.hpp>
#include "Animation.h"
#include "../precomp.h"

namespace Sprite {
    class Animation;
    class sprite {
        public:
            sprite();
            sprite(std::string filename);
            ~sprite();
            virtual void drawto(sf::RenderWindow* window);
            void setPosition(sf::Vector2f pos);
            void setScale(sf::Vector2f scale);
            void move(sf::Vector2f offset);
        protected:
            sf::RectangleShape image;
            sf::Texture* texture;
    };
    class anim_sprite : public sprite {
        public:
            anim_sprite();
            anim_sprite(std::string filename, int sprite_width, int sprite_height, std::map<std::string, Sprite::Animation> animations);
            ~anim_sprite();
            
            // Set Functions:
            void set_speed_ms(int speed_ms);
            void set_begin_delay_ms(int delay_ms);
            void set_end_delay_ms(int delay_ms);

            // Update Functions:
            void update();
            void update_frame();

            // Advance Frame:
            void advance_frame();

            // Add a new animation:
            void add_animation(std::string name, Sprite::Animation animation);
        private:
            int sprite_width;
            int sprite_height;
            int sheet_width;
            int sheet_height;
            int speed_ms;
            int begin_delay;
            int end_delay;
            std::map<std::string, Sprite::Animation> animations;
            sf::Clock clock;
            std::string current_animation;
    };
    class background {
        public:
            background(std::string filename);
            ~background();
            void drawto(sf::RenderWindow* window);
        private:
            sf::RectangleShape image;
            sf::Texture* texture;
    };
};
