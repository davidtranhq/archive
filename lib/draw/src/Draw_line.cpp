#include "Draw_shape.hpp"

#include <optional>
#include <cmath>

using namespace draw;

line::line(const point &p1, const point &p2, float w, bool aa,
	const std::optional<color> &c) noexcept
	: shape(w, aa, c),
	  _p1 {p1},
	  _p2 {p2}
{
}

void line::draw(const sdl::renderer &r,
	const std::optional<color> &c, const color &fallback) const
{
	// bresenham algorithm
	// http://members.chello.at/~easyfilter/bresenham.html
	color col {c.value_or(get_color().value_or(fallback))};
	int dx {std::abs(_p1.x - _p2.x)}, dy {std::abs(_p1.y - _p2.y)};
	int sx {_p1.x < _p2.x ? 1 : -1}, sy {_p1.y < _p2.y ? 1 :  -1};
	
	if (is_anti_aliased())
		draw_anti_aliased(r, dx, dy, sx, sy, col);
	else
		draw_aliased(r, dx, dy, sx, sy, col);
}

void line::draw_anti_aliased(const sdl::renderer &r, int dx, int dy, 
	int sx, int sy, const color &c) const noexcept
{
	int x0 {_p1.x}, y0 {_p1.y};
	int x1 {_p2.x}, y1 {_p2.y};
	float weight {get_weight()};
	int err {dx-dy}, e2, x2, y2;
	double ed {dx+dy == 0 ? 1.0 : std::sqrt(dx*dx+dy*dy)};

	for (weight = (weight+1)/2; ;)
	{
		// for aliasing, we need to fade the color (alpha blend)
		color fade(c.r, c.g, c.b,
			std::max(uint8_t {0}, 
			uint8_t {c.a*(std::abs(err-dx+dy)/ed-weight+1)}));
		dot d(point {x0, y0}, fade);
		d.draw(r);
		e2 = err;
		x2 = x0;
		if (2*e2 >= -dx)
		{
			for (e2 += dy, y2 = y0; 
				 ((e2 < ed*weight) && (y1 != y2)) || dx > dy; 
				 e2 += dx)
			{
				// alpha blend on one side
				color fade2(c.r, c.g, c.b,
					std::max(double {0}, c.a*(std::abs(e2)/ed-weight+1)));
				dot d2(point {x0, y2 += sy}, fade2);
				d2.draw(r);
			}
			if (x0 == x1)
				break;
			e2 = err;
			err -= dy;
			x0 += sx;
		}
		if (2*e2 <= dy)
		{
			for (e2 = dx-e2; 
				 e2 < ed*weight && (x1 != x2 || dx < dy); 
				 e2 += dy)
			{
				// alpha blend on the other
				color fade3(c.r, c.g, c.b,
					std::max(double {0}, c.a*(std::abs(e2)/ed-weight+1)));
				dot d3(point {x2 += sx, y0}, fade3);
				d3.draw(r);
			}
			if (y0 == y1) 
				break;
			err += dx; 
			y0 += sy; 
		}
	}
}

void line::draw_aliased(const sdl::renderer &r, int dx, int dy, 
	int sx, int sy, const color &c) const noexcept
{
	int x0 {_p1.x}, y0 {_p1.y};
	int x1 {_p2.x}, y1 {_p2.y};
	int err {dx+dy}, e2;
	for (;;)
	{
		dot d(point {x0, y0});
		d.draw(r, c);
		if (x0 == x1 && y0 == y1)
			break;
		e2 = 2*err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}