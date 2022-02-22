#ifndef DRAW_CIRCLE_HPP
#define DRAW_CIRCLE_HPP

#include "Draw_shape.hpp"
#include "Draw_color.hpp"

#include <optional>

namespace draw
{

class circle : public shape
{
	public:
		explicit circle(const point &p = {0,0}, int r = 1,  float w = 1.0,
			bool aa = true, const std::optional<color> &c = std::nullopt)
			noexcept;
	
		virtual void draw(const window &w,
			const std::optional<color> &c = std::nullopt) const override;
	
	private:
		void draw_aliased(const sdl::renderer &r, 
			const color &c) const;
		void draw_anti_aliased(const sdl::renderer &r,
			const color &c) const;
		point _center;
		int _radius;
};

} // namespace draw