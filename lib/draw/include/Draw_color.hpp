#ifndef DRAW_COLOR_HPP
#define DRAW_COLOR_HPP

#include <cstdint>

namespace draw
{

struct color
{
	uint8_t r, g, b, a {255}; // alpha defaults to 255
};

static const color
	white {255, 255, 255, 255},
	red {255, 0, 0},
	green {0, 255, 0},
	blue {0, 0, 255},
	orange {255, 69, 0},
	yellow {255, 255, 0},
	purple {255, 0, 255},
	black {0, 0, 0, 0};

} // namespace draw

#endif