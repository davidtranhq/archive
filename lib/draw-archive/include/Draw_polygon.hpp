#ifndef DRAW_POLYGON_HPP
#define DRAW_POLYGON_HPP

#include "draw_shape.hpp"

#include <vector>

namespace draw
{

class polygon : public shape
{
	public:
		explicit polygon(std::initializer_list<point> vs, int weight = 1,
			bool anti_aliased = true);
		virtual void draw() const;
	
	private:
		std::vector<point> _vertices;
};

class rect : public polygon
{
	public:
		rect(point p, int w, int h);
};

}
#endif