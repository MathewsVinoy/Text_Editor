#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <iostream>
#include <window.h>

void window()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        printf("error initializing SDL: %s\n", SDL_GetError());
    }
    SDL_Window *win = SDL_CreateWindow("Text Editor",
                                       SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED,
                                       1000, 1000, 0);
    Uint32 render_flags = SDL_RENDERER_ACCELERATED;
    int close = 0;
    while (!close)
    {
        SDL_Event event;
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close = 1;
                break;
            case SDL_KEYDOWN:
                std::cout << SDL_GetKeyName(event.key.keysym.sym);
                break;

            default:
                break;
            }
        }
    }
}