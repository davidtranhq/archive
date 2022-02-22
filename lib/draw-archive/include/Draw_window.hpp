#ifndef DRAW_WINDOW_HPP
#define DRAW_WINDOW_HPP

#include "Draw_color.hpp"

#include <SDLpp.hpp>
#include <string>
#include <optional>

namespace draw
{

class shape;
class window
{
	public:
	// constructors may throw runtime_error on failiure
	// constructor from parameters
		// all parameters
		explicit window(const std::string &title = "Draw!", 
						int w = 640, 
						int h = 480, 
						const color &c = black,
						int xpos = SDL_WINDOWPOS_CENTERED, 
						int ypos = SDL_WINDOWPOS_CENTERED);
		// specify only the default color
		explicit window(const color &c);
		// specify dimensions and default color
		window(int w, int h, const color &c = black);
		
	// copy and move can be default because the members have their copy and
	// move methods defined
	
	// destructor can be default for the same reason
	
	// member functions
		// show the changes made to the window after it is drawn to
		void update();
		// draw a shape s to the screen with an optional color override
		void draw(const shape &s, 
			const std::optional<color> &c = std::nullopt);
		// clear the screen with the current default color
		void clear();
		// set the default color of the window
		void set_color(const color &c);
		
	// getter functions
		const sdl::renderer &get_renderer() const noexcept;
		const color &get_color() const noexcept;
		
	private:
		color _color;
		sdl::window _win;
		sdl::renderer _ren;
};

} // namespace draw

#endif