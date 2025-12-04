#include "example_class.h"

void ExampleClass::_bind_methods() {
	godot::ClassDB::bind_method(D_METHOD("print_type", "variant"), &ExampleClass::print_type);
	// godot::ClassDB::add_property("speed", PropertyInfo(, &ClassDB::speed), "set_speed", "get_speed");
}

void ExampleClass::print_type(const Variant &p_variant) const {
	print_line(vformat("Type: %d", p_variant.get_type()));
}

void ExampleClass::_process(double dela)
{
	print_line(vformat("HELLO OF GODOT C++ EXTENSION"));
}