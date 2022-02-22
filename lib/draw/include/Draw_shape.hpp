#ifndef DRAW_SHAPE_HPP
#define DRAW_SHAPE_HPP

namespace draw
{
	
class window; // forward declaration for shape::draw
	
struct point
{
	int x, y;
};
	
class shape
{
	public:
		virtual void draw(const window &w) const = 0;
		
	protected:
		shape(unsigned int w, bool aa) noexcept;
	
	private:
		unsigned int _weight;
		bool _anti_aliased;
};

class closed_shape : public shape
{
	public:
		virtual void draw_fill(const window &w) const = 0;
};
	
} // namespace draw

#endif