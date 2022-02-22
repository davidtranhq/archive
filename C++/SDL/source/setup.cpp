#include <iostream>
#include <SDL.h>

int main(int argc, char *argv[])
{
	SDL_Window *window = NULL;
	SDL_Surface *surface = NULL;
	
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError();
		return 1;
	}
	// SDL_CreateWindow(char *title, int xpos, int ypos, int width, int height
	//  	uint32 flags);
	// https://wiki.libsdl.org/SDL_CreateWindow
	window = SDL_CreateWindow("SDL Tutorial", 100, 100, 640, 480, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError();
		return 1;
	}
	surface = SDL_GetWindowSurface(window);
	SDL_FillRect(surface, NULL, SDL_MapRGB(surface->format, 0xFF, 0xFF, 0xFF));
	SDL_UpdateWindowSurface(window);
	SDL_Delay(2000);
	return 0;
}