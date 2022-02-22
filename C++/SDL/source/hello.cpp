#include <iostream>
#include <SDL.h>
#include <string>

#include "res_path.hpp"

inline void log_SDL_error(const std::string &e)
{
	std::cerr << e << " SDL_Error: " << SDL_GetError();
}

int main(int argc, char *argv[])
{
	// initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		log_SDL_error("SDL could not initialize!");
		return 1;
	}
	SDL_Window *window = SDL_CreateWindow("SDL Tutorial", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		log_SDL_error("Window could not be created!");
		return 1;
	}
	SDL_Surface *surface = SDL_GetWindowSurface(window);
	
	// load media
	std::string img = get_res_path("lesson02") + "hello.bmp";
	if (img.empty())
		return 1;
	SDL_Surface *hello = SDL_LoadBMP(img.c_str());
	if (hello == NULL)
	{
		log_SDL_error("Unable to load image!");
		return 1;
	}
	
	// display the image
	SDL_BlitSurface(hello, NULL, surface, NULL);
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	
	// close SDL
	SDL_FreeSurface(hello);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}