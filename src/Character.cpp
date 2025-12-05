#include "Character.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>


void Character::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_speed", "value"), &Character::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &Character::get_speed);
    ClassDB::add_property(
        "Character",
        PropertyInfo(Variant::FLOAT, "speed"),
        "set_speed",
        "get_speed"
    );

    ClassDB::bind_method(D_METHOD("set_jump_speed", "value"), &Character::set_jump_speed);
    ClassDB::bind_method(D_METHOD("get_jump_speed"), &Character::get_jump_speed);
    ClassDB::add_property(
        "Character",
        PropertyInfo(Variant::FLOAT, "jump_speed"), 
        "set_jump_speed", 
        "get_jump_speed"
    );

    ClassDB::bind_method(D_METHOD("set_fall_speed", "value"), &Character::set_fall_speed);
    ClassDB::bind_method(D_METHOD("get_fall_speed"), &Character::get_fall_speed);
    ClassDB::add_property(
        "Character",
        PropertyInfo(Variant::FLOAT, "fall_speed"),
        "set_fall_speed",
        "get_fall_speed"
    );

}

Character::Character():speed(10), gravity(9.8), jump_speed(2.0), fall_speed(4.5){}

void Character::set_speed(float value)
{
    this->speed = value;
}

void Character::set_jump_speed(float value)
{
    this->jump_speed = value;
}
void Character::set_fall_speed(float value)
{
    this->fall_speed = value;
}

float Character::get_speed()
{
    return (this->speed);
}

float Character::get_jump_speed()
{
    return (this->jump_speed);
}

float Character::get_fall_speed()
{
    return (this->fall_speed);
}

void Character::_physics_process(double delta)
{
    if (Engine::get_singleton()->is_editor_hint()) return;

    Vector3 movement = Vector3(0, 0, 0);
    Input *input = Input::get_singleton();

    if (input->is_action_pressed("ui_up"))
    {
        movement.z += 1;
    }
    if (input->is_action_pressed("ui_down"))
    {
        movement.z -= 1;
    }
    if (input->is_action_pressed("ui_left"))
    {
        movement.x += 1;
    }
    if (input->is_action_pressed("ui_right"))
    {
        movement.x -= 1;
    }
    movement = movement.normalized() * speed;
    
    Vector3 vel = this->get_velocity();
    vel.x = movement.x;
    vel.z = movement.z;

    if (!this->is_on_floor())
    {
        vel.y -= gravity * fall_speed * delta;
        print_line(vformat("Nao esta no chao"));
    }
    this->set_velocity(vel);
    
    this->move_and_slide();
    print_line(vformat("HELLO C++ CHARACTER"));
}

// void Character::_input()
// {

// }