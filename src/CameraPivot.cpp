#include "CameraPivot.hpp"
#include <godot_cpp/classes/input_event_mouse_motion.hpp>
#include <godot_cpp/classes/input.hpp>
CameraPivot::CameraPivot():speed_mouse(0.3f)
{}

void CameraPivot::_bind_methods()
{
    ClassDB::bind_method(D_METHOD("set_speed_mouse", "value"), &CameraPivot::set_speed_mouse);
    ClassDB::bind_method(D_METHOD("get_speed_mouse"), &CameraPivot::get_speed_mouse);

    ClassDB::add_property_group("CameraPivot", "Camera", "");

    ClassDB::add_property_group("CameraPivot", "Camera", "");
    ClassDB::add_property(
        "CameraPivot",
        PropertyInfo(Variant::FLOAT, "mouse_speed"),
        "set_speed_mouse",
        "get_speed_mouse"
    );
}

void CameraPivot::_ready()
{
    Input::get_singleton()->set_mouse_mode(Input::MOUSE_MODE_CAPTURED);
}
void CameraPivot::_process(double delta)
{
    Vector3 rotation = this->get_rotation_degrees();

    rotation.y -= this->relative.x * this->speed_mouse;

    rotation.x += this->relative.y * this->speed_mouse;
    rotation.x = Math::clamp(rotation.x, -11.3f, 90.0f);

    this->set_rotation_degrees(rotation);
    this->relative = Vector2(0,0);
}
void CameraPivot::_input(const Ref<InputEvent> &event)
{
    if (event->is_class("InputEventMouseMotion"))
    {
        Ref<InputEventMouseMotion> motion_event = event;
        this->relative = motion_event->get_relative();
    }
}


void CameraPivot::set_speed_mouse(float speed)
{
    this->speed_mouse = speed;
}

float CameraPivot::get_speed_mouse()
{
    return (this->speed_mouse);
}