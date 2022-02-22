#include <iostream>
#include <SDLpp.hpp>

int main(int argc, char *argv[])
{
	sdl::init();
	sdl::window win("Physics!");
	sdl::renderer ren(win);
	SDL_RenderDrawLine(ren, 10, 10, 400, 400);
	SDL_RenderPresent(ren);
	SDL_Delay(3000);
	return 0;
}