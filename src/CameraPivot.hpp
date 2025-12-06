#pragma once

#include <godot_cpp/classes/node3d.hpp>
#include <godot_cpp/godot.hpp>
#include <godot_cpp/classes/input_event.hpp>

using namespace godot;

class CameraPivot: public Node3D
{
    GDCLASS(CameraPivot, Node3D);
    protected:
        static void _bind_methods();

    private:
        Vector2 relative;
        float speed_mouse;
    public:
        CameraPivot();
        ~CameraPivot() = default;
        
        void _ready();
        void _input(const Ref<InputEvent> &event) override;
        void _process(double delta) override;

        void set_speed_mouse(float speed);

        float get_speed_mouse();
};