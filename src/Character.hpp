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
    public:
        Character();
        ~Character() override = default;;

        void _physics_process(double delta) override;
        void set_speed(float value);

        float get_speed();
};