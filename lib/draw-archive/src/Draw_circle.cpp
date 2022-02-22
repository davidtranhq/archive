#include "Draw_shape.hpp"

#include <algorithm>
#include <cmath>

using namespace draw;

circle::circle(const point &p, int r, float w, bool aa,
	const std::optional<color> &c) noexcept
	: shape(w, aa, c),
	  _center {p},
	  _radius {r}
{
}

void circle::draw(const window &w,
	const std::optional<color> &c = std::nullopt) const
{
	// color override c takes precedence over the shape color which takes
	// precedence over the fallback color
	color col {c.value_or(get_color().value_or(fallback))};
	if (is_anti_aliased())
		draw_anti_aliased(r, col);
	else
		draw_aliased(r, col);
}

void draw_quadrants(int x, int y, int offx, int offy, const sdl::renderer &r,
	const color &c)
{
	std::array<dot, 4> pts
	{{
		dot({x-offx, y+offy}),
		dot({x-offy, y-offx}),
		dot({x+offx, y-offy}),
		dot({x+offy, y+offx})
	}};
	for (dot d : pts)
		d.draw(r, c);
}

void circle::draw_aliased(const sdl::renderer &r, const color &c) const
{
	int rad = _radius;
	int x = -rad, y = 0;
	int err = 2-2*rad;
	do
	{
		draw_quadrants(_center.x, _center.y, x, y, r, c);
		rad = err;
		if (rad <= y)
			err += ++y*2+1;
		if (rad > x || err > y)
			err += ++x*2+1;
	} while (x < 0);
}

void circle::draw_anti_aliased(const sdl::renderer &r, const color &c) const
{
	int xm {_center.x}, ym {_center.y};
	int rad {_radius};
	int x {-rad}, y {0};           /* II. quadrant from bottom left to top right */
	int x2, e2, err {2-2*rad};                             /* error of 1.step */
	color blend;
	rad = 1-err;
	do 
	{
		blend = {c.r, c.g, c.b,
			c.a*std::abs(err-2*(x+y)-2)/rad};               /* get blend value of pixel */
		draw_quadrants(xm, ym, x, y, r, blend);
		e2 = err; x2 = x;                                    /* remember values */
		if (err+y > 0) 
		{                                              /* x step */
			blend = {c.r, c.g, c.b, c.a*(err-2*x-1)/rad};          /* outward pixel */
			if (blend.a < 256) 
			{
				dot({xm-x, ym+y+1}, blend).draw(r);
				dot({xm-y-1, ym-x}, blend).draw(r);
				dot({xm+x, ym-y-1}, blend).draw(r);
				dot({xm+y+1, ym+x}, blend).draw(r);
			}
			err += ++x*2+1;
		}
		if (e2+x2 <= 0) 
		{                                             /* y step */
			blend = {c.r, c.g, c.b, c.a*255*(2*y+3-e2)/rad};               /* inward pixel */
			if (blend.a < 256) 
			{
				dot({xm-x2-1, ym+y}, blend).draw(r);
				dot({xm-y, ym-x2-1}, blend).draw(r);
				dot({xm+x2+1, ym-y}, blend).draw(r);
				dot({xm+y, ym+x2+1}, blend).draw(r);
			}
			err += ++y*2+1;
		}
	} while (x < 0);
}