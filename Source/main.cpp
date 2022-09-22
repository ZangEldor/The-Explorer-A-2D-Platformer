#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_timer.h>
#include "Player.h"
#include "Block.h"
#include "Hook.h"
#include "Spike.h"
#include "LevelFinish.h"
#include "Background.h"
#include <fstream>
#include <emscripten.h>
typedef struct Args{
    LevelObjects* lvlObj;
    SDL_Renderer* renderer;
} Args ;
void loop(void *args)
{
    LevelObjects *lvlObjs = ((Args *)(args))->lvlObj;
    SDL_Renderer* renderer = ((Args*)(args))->renderer;
    SDL_RenderClear(renderer);
    lvlObjs->getBackground()->draw();
    SDL_Event event;
    // Events management
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
          //  close = 1;
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
    Player* player = lvlObjs->getPlayer();
    player->update(0, lvlObjs);

    for (auto *var : lvlObjs->getEnemiesList())
    {
        var->update(0, lvlObjs);
    }

    for (auto *var : lvlObjs->getEnemiesList())
    {
        var->draw();
    }

    for (auto *var : lvlObjs->getBlocksList())
    {
        var->draw();
    }
    lvlObjs->getFinish()->draw();
    lvlObjs->getPlayer()->draw();
    // triggers the double buffers
    // for multiple rendering
    SDL_RenderPresent(renderer);

    // calculates to 60 fps
   // SDL_Delay(1000 / 60);
}
int main(int argv, char **args)
{
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window *window = SDL_CreateWindow("Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    Uint32 render_flgs = SDL_RENDERER_ACCELERATED;
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    LevelObjects *lvlObjs = new LevelObjects();
    Background *background = new Background(renderer, "Sprites/background.png", 800, 600, 0, 0);
    lvlObjs->setBackground(background);
    int levelActive = 1;
    int* levelActivePtr = &levelActive;
    int i=0,j=0;
    
    //std::ifstream fileStream("level.txt");
    char *playerSprite = (char *)"Sprites/bigplayer.png";
    FILE *file = fopen("Levels/level.txt", "rb");
    if (!file)
    {
        printf("cannot open file\n");
        return 1;
    }
    while (!feof(file))
    {
        char currChar = fgetc(file);
        if (currChar != EOF)
        {
            if (currChar == 'P')
            {
                Player *player = new Player(renderer, "Sprites/bigplayer.png", 40, 60, i * 20, j * 20, levelActivePtr);
                lvlObjs->setPlayer(player);
            }
            else if (currChar == '0')
            {
                Block *block = new Block(renderer, "Sprites/floor.png", 20, 20, i * 20, j * 20);
                lvlObjs->addBlock(block);
            }
            else if (currChar == '1')
            {
                Block *block = new Block(renderer, "Sprites/block.png", 20, 20, i * 20, j * 20);
                lvlObjs->addBlock(block);
            }
            else if (currChar == 'E')
            {
                Enemy *enemy = new Enemy(renderer, "Sprites/enemy.png", 20, 20, i * 20, j * 20);
                lvlObjs->addEnemy(enemy);
            }
            else if (currChar == 'S')
            {
                Enemy *enemy = new Spike(renderer, "Sprites/spike.png", 20, 20, i * 20, j * 20);
                lvlObjs->addEnemy(enemy);
            }
            else if (currChar == 'F')
            {
                LevelFinish *finish = new LevelFinish(renderer, "Sprites/flag.png", 20, 60, i * 20, j * 20);
                lvlObjs->setFinish(finish);
            }
            if (currChar == '\n')
            {
                j++;
                i = 0;
            }
            else
            {
                i++;
            }
        }
    }
    fclose(file);
    
    Args args1;
    
    args1.lvlObj = lvlObjs;
    args1.renderer = renderer;
    emscripten_set_main_loop_arg(loop,(void*)&args1,0,1);
        SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
}