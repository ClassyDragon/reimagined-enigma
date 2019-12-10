#pragma once

#include "Sprite.h"
#include "../precomp.h"

namespace Sprite {
    class Animation {
        public:
            Animation(int start_index, int num_frames, bool Reversing);
            ~Animation();

            // Set Functions:
            void set_start_index(int index);
            void set_num_frames(int num_frames);
            void set_reversing(bool Reversing);
            void set_current_frame(int frame);
            void set_speed_ms(int speed_ms);
            void set_begin_delay(int delay_ms);
            void set_end_delay(int delay_ms);

            // Get Functions:
            int get_start_index();
            int get_num_frames();
            bool is_reversing();
            int get_current_frame();
            int get_speed_ms();
            bool beginning_delay();
            bool ending_delay();
            int get_begin_delay();
            int get_end_delay();

            // Advance to next frame:
            void advance();
        private:
            // Parameters:
            int start_index; // Index in sprite-sheet
            int num_frames;  // Number of frames the animation lasts for
            bool Reversing;  // Whether the animation is Reversing or not
            bool direction;  // False = Forward. True = Backward.
            bool wait_begin;
            bool wait_end;
            int speed_ms;
            int begin_delay;
            int end_delay;

            // Direction Enum:
            enum direction{Forward, Backward};

            // Advancement:
            int current_frame;
    };
    class anim_sprite;
    class background;
};
