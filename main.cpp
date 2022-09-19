#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Player.h"
#include "Player.cpp"
int main(int argv, char **args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
    Uint32 render_flgs = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flgs);
    Player *player = new Player(renderer);
    int close = 0;
    while (!close)
    {
        SDL_RenderClear(renderer);
        SDL_Event event;
        // Events management
        while (SDL_PollEvent(&event))
        {
            switch (event.type)
            {
            case SDL_QUIT:
                close = 1;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.scancode)
                {
                case SDL_SCANCODE_W:
                case SDL_SCANCODE_UP:
                    player->update(up);
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    player->update(left);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    player->update(down);
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    player->update(right);
                    break;
                default:
                    break;
                }
            }
        }
        player->update(0);
        player->draw();
        // triggers the double buffers
        // for multiple rendering
        SDL_RenderPresent(renderer);

        // calculates to 60 fps
        SDL_Delay(1000 / 60);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}