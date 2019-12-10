#include "Animation.h"

// Constructor:
Sprite::Animation::Animation(int start_index, int num_frames, bool Reversing) {
    this->start_index = start_index;
    this->num_frames = num_frames;
    this->Reversing = Reversing;
    this->speed_ms = 50;

    this->current_frame = 1;
    this->direction = false; // Forward
    this->wait_begin = false;
    this->wait_end = false;
}

// Deconstructor:
Sprite::Animation::~Animation() {
}

// Set Functions:
void Sprite::Animation::set_start_index(int index) {
    start_index = index;
}

void Sprite::Animation::set_num_frames(int num_frames) {
    this->num_frames = num_frames;
}

void Sprite::Animation::set_reversing(bool Reversing) {
    this->Reversing = Reversing;
}

void Sprite::Animation::set_current_frame(int frame) {
    this->current_frame = frame;
}

void Sprite::Animation::set_speed_ms(int speed_ms) {
    this->speed_ms = speed_ms;
}

void Sprite::Animation::set_begin_delay(int delay_ms) {
    this->begin_delay = delay_ms;
}

void Sprite::Animation::set_end_delay(int delay_ms) {
    this->end_delay = delay_ms;
}

// Get Functions:
int Sprite::Animation::get_start_index() {
    return this->start_index;
}

int Sprite::Animation::get_num_frames() {
    return this->num_frames;
}

bool Sprite::Animation::is_reversing() {
    return this->Reversing;
}

int Sprite::Animation::get_current_frame() {
    return this->current_frame;
}

int Sprite::Animation::get_speed_ms() {
    return this->speed_ms;
}

bool Sprite::Animation::beginning_delay() {
    return this->wait_begin;
}

bool Sprite::Animation::ending_delay() {
    return this->wait_end;
}

int Sprite::Animation::get_begin_delay() {
    return this->begin_delay;
}

int Sprite::Animation::get_end_delay() {
    return this->end_delay;
}

// Advance to the next frame:
void Sprite::Animation::advance() {
    if (this->is_reversing()) {
        if (direction == Sprite::Animation::direction::Forward && !wait_end) {
            current_frame++;
            if (current_frame == num_frames) {
                wait_end = true;
                return;
            }
        }
        else if (direction == Sprite::Animation::direction::Backward && !wait_begin) {
            current_frame--;
            if (current_frame == 1) {
                wait_begin = true;
                return;
            }
        }

        wait_end = false;
        wait_begin = false;

        if (!wait_end && !wait_begin) {
            if (current_frame == num_frames && direction == Sprite::Animation::direction::Forward) {
                direction = Sprite::Animation::direction::Backward;
                wait_end = false;
            }
            else if (current_frame == 1 && direction == Sprite::Animation::direction::Backward) {
                direction = Sprite::Animation::direction::Forward;
                wait_begin = false;
            }
        }
    }
    else if (!this->is_reversing()) {
        if (current_frame + 1 > this->num_frames)
            current_frame = 1;
        else
            current_frame++;
    }
}
