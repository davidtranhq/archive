#include "Draw_shape.hpp"

#include <optional>

using namespace draw;

dot::dot(const point &p, const std::optional<color> &c) noexcept
	: shape(1.0, false, c),
	  _point {p}
{
}

void dot::draw(const sdl::renderer &r, 	const std::optional<color> &c
	const color &fallback) const
{
	// choose which color to use based on the hierachy below
	// explicit draw parameter color > shape color > window color > black
	color col {c.value_or(_color.value_or(fallback))};
	SDL_SetRenderDrawColor(r, col.r, col.g, col.b, col.a);
	SDL_RenderDrawPoint(r, _point.x, _point.y);
}