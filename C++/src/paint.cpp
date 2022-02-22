#include <iostream>
#include <SDLpp.hpp>

int main(int argc, char *argv[])
{
	sdl::init();
	sdl::window w;
	bool quit {false};
	SDL_Event e;
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