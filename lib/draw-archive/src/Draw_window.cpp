#include "Draw_window.hpp"

#include <string>
#include <stdexcept>
#include <Draw_shape.hpp>
#include <Draw_color.hpp>

namespace draw
{
	
window::window(const std::string &title, int w, int h, const color &c, 
	int xpos, int ypos)
	: _color {c},
	  _win(title, xpos, ypos, w, h),
	  _ren(_win) // create SDL rendering context from the window
{
}

window::window(int w, int h, const color &c)
	: window("Draw!", w, h, c)
{
}

window::window(const color &c)
	: window("Draw!", 640, 480, c)
{
}

void window::update()
{
	SDL_RenderPresent(_ren);
}

void window::draw(const shape &s,
	const std::optional<color> &c)
{
	// the user supplied draw::color takes priority over the default drawing
	// color of the window
	color col {c.value_or(_color)};
	s.draw(_ren, col);
}

void window::clear()
{
	int res = SDL_RenderClear(_ren);
	if (res != 0)
	{
		std::string e {"Could not clear window! Error: "};
		throw std::runtime_error {e + SDL_GetError()};
	}
}

void window::set_color(const draw::color &c)
{
	_color = c;
	int res = SDL_SetRenderDrawColor(_ren, c.r, c.g, c.b, c.a);
	if (res != 0)
	{
		std::string e {"Could not change draw::color! Error: "};
		throw std::runtime_error {e + SDL_GetError()};
	}
}

const sdl::renderer &window::get_renderer() const noexcept
{
	return _ren;
}

const color &window::get_color() const noexcept
{
	return _color;
}

} // namespace draw