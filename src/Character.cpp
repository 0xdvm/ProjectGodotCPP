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

}

Character::Character():speed(10){}

void Character::set_speed(float value)
{
    this->speed = value;
}

float Character::get_speed()
{
    return (this->speed);
}

void Character::_physics_process(double delta)
{
    if (Engine::get_singleton()->is_editor_hint()) return;

    Vector3 movement = Vector3(0, 0, 0);
    Input *input = Input::get_singleton();

    if (input->is_action_pressed("ui_up"))
    {
        movement.z -= 1;
    }
    if (input->is_action_pressed("ui_down"))
    {
        movement.z += 1;
    }
    if (input->is_action_pressed("ui_left"))
    {
        movement.x -= 1;
    }
    if (input->is_action_pressed("ui_right"))
    {
        movement.x += 1;
    }
    movement = movement.normalized() * speed * delta;
    
    Vector3 vel = this->get_velocity();
    vel.x = movement.x;
    vel.z = movement.z;
    if (!this->is_on_floor())
    {
        vel.y -= 9.8 * delta;
        print_line(vformat("Nao esta no chao"));
    }
    this->set_velocity(vel);
    
    this->move_and_slide();
    print_line(vformat("HELLO C++ CHARACTER"));
}