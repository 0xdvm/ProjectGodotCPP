#pragma once

#include <godot_cpp/classes/character_body3d.hpp>

using namespace godot;

class Character : public CharacterBody3D
{
    GDCLASS(Character, CharacterBody3D)

    protected:
        static void _bind_methods();

    private:
        float speed;
        float gravity;
        float jump_speed;
        float fall_speed;
    public:
        Character();
        ~Character() override = default;

        void _physics_process(double delta) override;
        // void _input() override;
        void set_speed(float value);
        void set_jump_speed(float value);
        void set_fall_speed(float value);

        float get_speed();
        float get_jump_speed();
        float get_fall_speed();

};