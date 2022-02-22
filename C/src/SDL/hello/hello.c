#include <SDL.h>
#include <stdio.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

bool init(void);
/*
    init: starts up SDL and creates window.
*/

bool load_media(void);
/*
    load_media: loads media
*/

void finish(void);
/*
    finish: frees media and shuts down SDL
*/

SDL_Window *window = NULL;
SDL_Surface *surface = NULL;
SDL_Surface *hello_world = NULL;

void handle_error(const char *const s)
{
    fprintf(stderr, "%s %s\n", s, SDL_GetError());
    exit(1);
}

bool init(void)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        return false;
    window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN);
    if (window == NULL)
        return false;
    surface = SDL_GetWindowSurface(window);
    return true;
}

bool load_media(void)
{
    hello_world = SDL_LoadBMP("src.bmp");
    if (hello_world == NULL)
        return false;
    return true;
}

void finish()
{
    SDL_FreeSurface(hello_world);
    surface = NULL;
    SDL_DestroyWindow(window);
    window = NULL;
    SDL_Quit();
}

int main(int argc, char *argv[])
{
    bool quit = false;
    if (!init())
        handle_error("Failed to initialize!");
    if (!load_media())
        handle_error("Failed to load media!");
    SDL_BlitSurface(hello_world, NULL, surface, NULL);
    SDL_UpdateWindowSurface(window);
    while (!quit)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                quit = true;
        }
    }
    finish();
    return 0;
}