#include <iostream>
#include <SDLpp.hpp>

int main(int argc, char *argv[])
{
	sdl::init();
	sdl::window w;
	SDL_Event e;
	SDL_Color text_color {0, 0, 0, 0xFF};
	
	bool quit = false;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}
		}
	}
		
	return 0;
}