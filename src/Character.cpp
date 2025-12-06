#include "Character.hpp"
#include <godot_cpp/core/class_db.hpp>
#include <godot_cpp/variant/variant.hpp>
#include <godot_cpp/classes/engine.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse_motion.hpp>


Character::Character():
    _camera(nullptr),
    speed(10), 
    gravity(9.8), 
    jump_speed(2.0), 
    fall_speed(4.5)
{}

void Character::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_speed", "value"), &Character::set_speed);
    ClassDB::bind_method(D_METHOD("get_speed"), &Character::get_speed);
    ClassDB::bind_method(D_METHOD("set_jump_speed", "value"), &Character::set_jump_speed);
    ClassDB::bind_method(D_METHOD("get_jump_speed"), &Character::get_jump_speed);
    ClassDB::bind_method(D_METHOD("set_fall_speed", "value"), &Character::set_fall_speed);
    ClassDB::bind_method(D_METHOD("get_fall_speed"), &Character::get_fall_speed);
    ClassDB::bind_method(D_METHOD("set_camera", "camera"), &Character::set_camera);
    ClassDB::bind_method(D_METHOD("get_camera"), &Character::get_camera);

    ClassDB::add_property_group("Character", "Properties", "");
    ClassDB::add_property(
        "Character",
        PropertyInfo(Variant::FLOAT, "speed"),
        "set_speed",
        "get_speed"
    );

    ClassDB::add_property(
        "Character",
        PropertyInfo(Variant::FLOAT, "jump_speed"), 
        "set_jump_speed", 
        "get_jump_speed"
    );

    ClassDB::add_property(
        "Character",
        PropertyInfo(Variant::FLOAT, "fall_speed"),
        "set_fall_speed",
        "get_fall_speed"
    );

    ClassDB::add_property_group("Character", "Camera Option", "");
    ClassDB::add_property(
        "Character",
        PropertyInfo(Variant::OBJECT, "Camera", PROPERTY_HINT_NODE_TYPE, "CameraPivot"),
        "set_camera",
        "get_camera"
    );

}


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
void Character::set_camera(CameraPivot *camera)
{
    this->_camera = camera;
}

CameraPivot* Character::get_camera()
{
    return (this->_camera);
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
    Transform3D direction = this->_camera->get_global_transform();

    Vector3 forward = direction.basis.xform(Vector3(0, 0, -1));
    Vector3 right = direction.basis.xform(Vector3(1, 0, 0));

    forward.y = 0;
    right.y = 0;

    forward = forward.normalized();
    right = right.normalized();

    if (input->is_action_pressed("move_forward"))
    {
        movement -= forward;
    }
    if (input->is_action_pressed("move_backward"))
    {
        movement += forward;
    }
    if (input->is_action_pressed("move_left"))
    {
        movement += right;
    }
    if (input->is_action_pressed("move_right"))
    {
        movement -= right;
    }

    if (movement.length() > 0.1f) {
        movement = movement.normalized() * speed;
    }
    // movement = movement.normalized() * speed;
    
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
void Character::jump()
{

    if (this->is_on_floor())
    {

        Vector3 start_jump = Vector3(0,0,0);
        
        start_jump.y += jump_speed;
        
        this->set_velocity(start_jump);
        this->move_and_slide();
    }
}
void Character::_input(const Ref<InputEvent> &event)
{
    if (event->is_action_pressed("jump")) 
        this->jump();
}