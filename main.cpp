#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Player.h"
#include "Block.h"
#include "Hook.h"
int main(int argv, char **args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 500, 500, 0);
    Uint32 render_flgs = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flgs);
    Player *player = new Player(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\Untitled.png",100,100,200,200);
    Collidable *block1 = new Block(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\brick.png", 500, 50, 0, 450);
    Collidable *block2 = new Block(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\brick.png", 52, 500, 0, 0);
    Collidable *block3 = new Block(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\brick.png", 500, 50, 0, 0);
    Collidable *block4 = new Block(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\brick.png", 57, 500, 450, 0);
   // Hook* hook = new Hook(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\hook.png", 50, 50, 250, 250);
        LevelObjects *lvlObjs = new LevelObjects();
    lvlObjs->addBlock(block1);
    lvlObjs->addBlock(block2);
    lvlObjs->addBlock(block3);
    lvlObjs->addBlock(block4);

    lvlObjs->setPlayer(player);
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
                    player->update(up, lvlObjs);
                    break;
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    player->update(left, lvlObjs);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    player->update(down, lvlObjs);
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    player->update(right, lvlObjs);
                    break;
                case SDL_SCANCODE_SPACE:
                    player->update(space, lvlObjs);
                    break;
                default:
                    break;
                }
            }
        }
        player->update(0, lvlObjs);
       // hook->update(0, lvlObjs);
            block1->draw();
        block2->draw();
        block3->draw();
        block4->draw();
        player->draw();
      //  hook->draw();
        
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