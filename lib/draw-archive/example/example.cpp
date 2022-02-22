#include <Draw.hpp>

#include <iostream>

int main(int argc, char *argv[])
{
	draw::init();
	draw::window w;
	w.draw(draw::circle {{0,0}, 
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT)
				quit = true;
		}
	}
	return 0;
}