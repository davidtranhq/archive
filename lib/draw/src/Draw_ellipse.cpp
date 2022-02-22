#include "Draw_ellipse.hpp"
#include "Draw_color.hpp"
#include "Draw_shape.hpp"
#include "Draw_window.hpp"

#include <optional>

namespace draw
{

void ellipse::draw(const draw::window &w) const
{
	int xm {_center.x}, ym {_center.y};
	int a {_xrad}, b {_yrad};
	long x {-a}, y {0}; // quadrant from bottom left to top right
	long e2 {b}, dx {(1+2*x)*e2*e2}; // error increment
	long dy {x*x}, err {dx+dy}; // error of 1. step */
	
	do
	{
		w.set_pixel(xm-x, ym+y); // I. Quadrant
		w.set_pixel(xm+x, ym+y); // II. Quadrant
		w.set_pixel(xm+x, ym-y); // III. Quadrant
		w.set_pixel(xm-x, ym-y); // IV. Quadrant
		e2 = 2*err;
		// x step
		if (e2 >= dx)
		{
			x++;
			err += dx += 2*(long)b*b;
		}
		// ystep
		if (e2 <= dy)
		{
			y++;
			err += dy += 2*(long)a*a;
		}
	} while (x <= 0);
	
	while (y++ < b)
	{
		// too early stop for flat ellipses with a = 1
		// finish top of ellipses
		w.set_pixel(xm, ym+y);
		w.set_pixel(xm, ym-y);
	}
	
}

} // namespace draw