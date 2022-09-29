#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Player.h"
#include "Block.h"
#include "InvBlock.h"
#include "Hook.h"
//#include "Spike.h"
//#include "LevelFinish.h"
#include "Background.h"
#include "LevelUtils.cpp"
#include <fstream>
// Emscripten header for online version
/*
#include <emscripten.h>
*/
typedef struct MainLoopArgs
{
    LevelObjects *lvlObj;
    SDL_Renderer *renderer;
    int levelID;
    int run;
} MainLoopArgs;

void loop(void *args)
{
    LevelObjects *lvlObjs = ((MainLoopArgs *)(args))->lvlObj;
    SDL_Renderer *renderer = ((MainLoopArgs *)(args))->renderer;
    int *levelID = &((MainLoopArgs *)args)->levelID;
    SDL_RenderClear(renderer);
    // Case for restarting current level
    if ((*(lvlObjs->getLevelActive()) == 0))
    {
        *(lvlObjs->getLevelActive()) = 1;
        loadLevel(lvlObjs, *levelID, renderer);
        return;
    }
    // Case for advancing to next level
    if ((*(lvlObjs->getLevelActive()) == 2))
    {
        *(lvlObjs->getLevelActive()) = 1;
        *levelID = (*levelID + 1) % 10;
        loadLevel(lvlObjs, *levelID, renderer);
        return;
    }
    lvlObjs->getBackground()->draw();
    if (*levelID == -1)
    {
        handleKeyboardStartScreen(lvlObjs, levelID);
        SDL_RenderPresent(renderer);
        return;
    }
    ((MainLoopArgs *)args)->run = handleKeyboardLevel(lvlObjs,levelID);
    updateLevel(lvlObjs);
    drawLevel(lvlObjs);
    SDL_RenderPresent(renderer);

    // Use only in offline version
     SDL_Delay(1000 / 60);
}
int main(int argv, char **args)
{
    // Initializing SDL
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    // Initializing arguments for main loop
    LevelObjects *lvlObjs = new LevelObjects();
    Background *background = new Background(renderer, "Sprites/background.png", 800, 600, 0, 0);
    lvlObjs->setBackground(background);
    int levelActive = 0;
    lvlObjs->setLevelActive(&levelActive);
    MainLoopArgs loopArgs;
    loopArgs.lvlObj = lvlObjs;
    loopArgs.renderer = renderer;
    loopArgs.run = 1;
    // -1 is starting screen
    loopArgs.levelID = -1;
    loadLevel(lvlObjs, loopArgs.levelID, renderer);
    // Loop for online version:
    /*
    while (true)
    {
        loop((void *)&loopArgs);
    }
    emscripten_set_main_loop_arg(loop, (void *)&loopArgs, 0, 1);
    */
    while (loopArgs.run)
    {
        loop((void *)&loopArgs);
    }
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}