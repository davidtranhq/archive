#include <SDL.h>
#include <iostream>

int main(int argc, char *argv[])
{
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
	{
		std::cerr << "Error initializing SDL! Error: " << SDL_GetError();
		return 1;
	}
	SDL_Window *w = SDL_CreateWindow("Geometry", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN);
	if (w == NULL)
	{
		std::cerr << "Could not create window! Error: " << SDL_GetError();
		return 1;
	}
	SDL_Renderer *r = SDL_CreateRenderer(w, -1, 0);
	if (r == NULL)
	{
		std::cerr << "Could not create renderer! Error : " << SDL_GetError();
		return 1;
	}
	
	bool quit = false;
	SDL_Event e;
	while (!quit)
	{
		while (SDL_PollEvent(&e) != 0)
			if (e.type == SDL_QUIT)
				quit = true;
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0xFF, 0xFF);
		SDL_RenderClear(r);
		SDL_Rect fill {20, 20, 20, 20};
		SDL_SetRenderDrawColor(r, 0xFF, 0x00, 0x00, 0xFF);
		SDL_RenderFillRect(r, &fill);
		
		SDL_Rect outline {30, 30, 30, 30};;
		SDL_SetRenderDrawColor(r, 0x00, 0xFF, 0x00, 0xFF);
		SDL_RenderDrawRect(r, &outline);
		
		SDL_SetRenderDrawColor(r, 0x00, 0x00, 0xFF, 0xFF);
		SDL_RenderDrawLine(r, 0, 240, 640, 240);
		
		SDL_SetRenderDrawColor(r, 0xFF, 0xFF, 0x00, 0xFF);
		for (int i = 0; i < 240; i+=4)
		{
			SDL_RenderDrawPoint(r, 320, i); 
		}
		SDL_RenderPresent(r);
	}
	return 0;
}