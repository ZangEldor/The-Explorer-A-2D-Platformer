#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Player.h"
#include "Block.h"
#include "Hook.h"
#include "Spike.h"
#include "LevelFinish.h"
#include <fstream>
int main(int argv, char **args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    Uint32 render_flgs = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, render_flgs);
    LevelObjects *lvlObjs = new LevelObjects();
    int levelActive = 1;
    int* levelActivePtr = &levelActive;
    int i=0,j=0;
    std::ifstream fileStream("C:\\Users\\eldor\\OneDrive\\Desktop\\level.txt");
    if(fileStream.is_open()){
        char currChar;
        while (fileStream.get(currChar))
        {
            if (currChar == 'P'){
                Player *player = new Player(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\bigplayer.png", 40, 60,  i * 20,  j * 20, levelActivePtr);
                lvlObjs->setPlayer(player);
            }else if(currChar == '0'){
                Block *block = new Block(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\floor.png", 20, 20,  i * 20,   j * 20);
                lvlObjs->addBlock(block);
            }
            else if (currChar == '1')
            {
                Block *block = new Block(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\block.png", 20, 20, i * 20, j * 20);
                lvlObjs->addBlock(block);
            }
            else if (currChar == 'E')
            {
                Enemy *enemy = new Enemy(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\enemy.png", 20, 20, i * 20, j * 20);
                lvlObjs->addEnemy(enemy);
            }
            else if (currChar == 'S')
            {
                Enemy *enemy = new Spike(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\spike.png", 20, 20, i * 20, j * 20);
                lvlObjs->addEnemy(enemy);
            }
            else if (currChar == 'F')
            {
                LevelFinish *finish = new LevelFinish(renderer, "C:\\Users\\eldor\\OneDrive\\Desktop\\flag.png", 20, 20, i * 20, j * 20);
                lvlObjs->setFinish(finish);
            }
            if (currChar == '\n'){
                j++;
                i=0;
            }else{
                i++;
            }
        }
    }
    int close = 0;
    while (!close)
    {
        if(!levelActive){
            break;
        }
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
                case SDL_SCANCODE_A:
                case SDL_SCANCODE_LEFT:
                    lvlObjs->getPlayer()->update(left, lvlObjs);
                    break;
                case SDL_SCANCODE_S:
                case SDL_SCANCODE_DOWN:
                    lvlObjs->getPlayer()->update(down, lvlObjs);
                    break;
                case SDL_SCANCODE_D:
                case SDL_SCANCODE_RIGHT:
                    lvlObjs->getPlayer()->update(right, lvlObjs);
                    break;
                case SDL_SCANCODE_SPACE:
                    lvlObjs->getPlayer()->update(space, lvlObjs);
                    break;
                default:
                    break;
                }
            }
        }
        lvlObjs->getPlayer()->update(0, lvlObjs);
        for (auto *var : lvlObjs->getEnemiesList())
        {
            var->update(0,lvlObjs);
        }
        for(auto* var: lvlObjs->getEnemiesList()){
            var->draw();
        }
        for (auto *var : lvlObjs->getBlocksList())
        {
            var->draw();
        }
        lvlObjs->getPlayer()->draw();
        lvlObjs->getFinish()->draw();

        
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