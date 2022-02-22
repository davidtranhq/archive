#include <SDLpp.hpp>

int main(int argc, char *argv[])
{
	sdl::init(SDL_INIT_VIDEO);
	sdl::window w {"SDL C++", 640, 480};
	sdl::surface res {"hello.bmp"};
	sdl::renderer r {w};
	sdl::texture t {r.get(), res.get()};
	SDL_RenderClear(r);
	SDL_RenderCopy(r, t, NULL, NULL);
	SDL_RenderPresent(r);
	SDL_Delay(3000);
	return 0;
}