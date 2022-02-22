#include "Draw_shape.hpp"

#include <optional>

using namespace draw;

shape::shape(float w, bool aa, const std::optional<color> &c)
	: _weight {w},
	  _anti_aliased {aa},
	  _color {c}
{
}

float shape::get_weight() const noexcept
{
	return _weight;
}

bool shape::is_anti_aliased() const noexcept
{
	return _anti_aliased;
}

const std::optional<color> &shape::get_color() const noexcept
{
	return _color;
}