#ifndef DRAW_CIRCLE_HPP
#define DRAW_CIRCLE_HPP

#include "Draw_elipse.hpp"
#include "Draw_color.hpp"

#include <optional>

namespace draw
{

class window;

class circle : public elipse
{
	public:
		circle(point c, unsigned int r, unsigned int w, bool aa) noexcept;
		circle(int x, int y, unsigned int r, unsigned int w, 
			bool aa) noexcept;
	
	private:
		point _center;
		unsigned int _radius;
};

} // namespace draw