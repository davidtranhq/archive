#ifndef DRAW_SHAPE_HPP
#define DRAW_SHAPE_HPP

#include <optional>
#include <SDLpp.hpp>
#include <Draw_color.hpp>

namespace draw
{
	class window;
	struct point;
	class shape;
	class circle;
	class dot;
	class line;

struct point
{
	int x, y;
};

// abstract base class
class shape
{
	public:
		// draw this to a window with an optional color override
		virtual void draw(const window &w,
			const std::optional<color> &c = std::nullopt) const = 0;
			
		float get_weight() const noexcept;
		bool is_anti_aliased() const noexcept;
	
	protected:
		explicit shape(float w = 1, bool aa = false);
	
	private:
		float _weight;
		bool _anti_aliased;
};



class dot : public shape
{
	public:
		explicit dot(const point &p = {0,0}, 
			const std::optional<color> &c = std::nullopt) noexcept;
		virtual void draw(const window &w;
			const std::optional<color> &c = std::nullopt) const override;
		
	private:
		point _point;
};

class line : public shape
{
	public:
		line(const point &p1, const point &p2, float w = 1.0, bool aa = true,
			const std::optional<color> &c = std::nullopt) noexcept;
		virtual void draw(const window &w,
			const std::optional<color> &c = std::nullopt) const override;
		
	private:
		void draw_aliased(const sdl::renderer &r, int dx, int dy, 
			int sx, int sy, const color &c) const noexcept;
		void draw_anti_aliased(const sdl::renderer &r, int dx, int dy, 
			int sx, int sy, const color &c) const noexcept;
		point _p1, _p2;
};

}

#endif