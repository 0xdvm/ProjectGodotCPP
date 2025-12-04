#pragma once

#include "godot_cpp/classes/ref_counted.hpp"
#include "godot_cpp/classes/wrapped.hpp"
#include "godot_cpp/variant/variant.hpp"
#include "godot_cpp/classes/node3d.hpp"

using namespace godot;

class ExampleClass : public Node3D {
	GDCLASS(ExampleClass, Node3D)

protected:
	static void _bind_methods();
	// double speed;
public:
	ExampleClass() = default;
	~ExampleClass() override = default;

	void print_type(const Variant &p_variant) const;

	void _process(double delta);
};
