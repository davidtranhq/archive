#include "Draw_polygon.hpp"

#include <stdexcept>

using draw::polygon;
using draw::line;
using draw::rect;

polygon::polygon(std::initializer_list<point> vs, int weight, bool aa)
	: _vertices(vs.size())
	  _weight {weight > 0 ? weight : 1},
	  _anti_aliased {aa}
{
	if (vs.size() < 2)
		throw std::invalid_argument {"Object of type 'Polygon' requires at \
			least 2 vertices!"};
	int i {0};
	for (draw::point p : vs)
		_vertices[i++] = p;
}

void polygon::draw(sdl::renderer &r) const
{
	draw::point p1 {};
	draw::point p2 {};
	for (size_t i = 0; i < _vertices.size(); i++)
	{
		p1 = _vertices[i];
		p2 = _vertices[(i+1) % _vertices.size()]; // wrap around for final point
		SDL_RenderDrawLine(r, p1.x, p1.y, p2.x, p2.y);
	}
}

// delegate to polygon, passing the 2 vertices
line::line(point p1, point p2)
	: polygon({p1, p2})
{
	
}

// calculate the four vertices of the rect and delegate to polygon()
rect::rect(point p, int w, int h)
	: polygon({
			   p,
	          {p.x+w, p.y},
			  {p.x+w, p.y+h},
			  {p.x, p.y+h}
			  })
{
}
