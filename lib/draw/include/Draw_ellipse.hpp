#ifndef DRAW_ELLIPSE_HPP
#define DRAW_ELLIPSE_HPP

#include "Draw_shape.hpp"
#include "Draw_color.hpp"

namespace draw
{

class window;

class ellipse : public closed_shape
{
	public:
		ellipse(point c, unsigned int xrad, unsigned int yrad) noexcept;
		ellipse(int x, int y, unsigned int xrad, unsigned int yrad) noexcept;
	
		void draw(const draw::window &w) const override;
		void draw_fill(const draw::window &w) const override;
		
	private:
		point _center;
		unsigned int _xrad, _yrad;
};

} // namespace draw

#endif