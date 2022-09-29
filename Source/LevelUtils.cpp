#include "LevelObjects.h"
#include "Background.h"
#include "Player.h"
#include "Block.h"
#include "InvBlock.h"
#include "Spike.h"
#include "LevelFinish.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <fstream>
void deleteLevel(LevelObjects *lvlObjs)
{
    // Deleting level's blocks
    std::vector<Block *> *blocksList = (lvlObjs->getBlocksList());
    while (!blocksList->empty())
    {
        Block *var = blocksList->back();
        blocksList->pop_back();
        delete var;
    }
    // Deleting level's enemies
    std::vector<Enemy *> *EnemiesList = (lvlObjs->getEnemiesList());
    while (!EnemiesList->empty())
    {
        Enemy *var = EnemiesList->back();
        EnemiesList->pop_back();
        delete var;
    }
    // Deleting level's invinsible blocks
    std::vector<InvBlock *> *invBlocksList = (lvlObjs->getInvBlocksList());
    while (!invBlocksList->empty())
    {
        InvBlock *var = invBlocksList->back();
        invBlocksList->pop_back();
        delete var;
    }
    // Deleting finish and player
    delete lvlObjs->getFinish();
    delete lvlObjs->getPlayer();
}
void loadLevel(LevelObjects *lvlObjs, int levelID, SDL_Renderer *renderer)
{
    // Applying background
    // Case for start screen
    if (levelID == -1)
    {
        Background *background = new Background(renderer, "Sprites/startbackground.png", 800, 600, 0, 0);
        lvlObjs->setBackground(background);
        return;
    }
    // Case for end screen
    else if (levelID == 0)
    {
        Background *background = new Background(renderer, "Sprites/finishbackground.png", 800, 600, 0, 0);
        delete lvlObjs->getBackground();
        lvlObjs->setBackground(background);
    }
    // Else case for all regular levels
    else
    {
        Background *background = new Background(renderer, "Sprites/background.png", 800, 600, 0, 0);
        delete lvlObjs->getBackground();
        lvlObjs->setBackground(background);
    }
    // Creating level's file path (for example: level 2 path is Levels/level_2)
    std::string filePath = "Levels/level_";
    char levelIDChar = '0' + levelID;
    filePath.push_back(levelIDChar);
    filePath = filePath + ".txt";
    deleteLevel(lvlObjs);
    /*
    Each level file is a 30x40 grid resembling the game window, smaller example:
    11111111111111111
    11             11
    11P           F11
    11             11
    11     SSSS    11
    11000000000000011
    11111111111111111
    */
    int i = 0, j = 0;
    FILE *file = fopen(filePath.c_str(), "rb");
    if (!file)
    {
        printf("cannot open file\n");
        printf("%s\n", filePath.c_str());
    }
    while (!feof(file))
    {
        char currChar = fgetc(file);
        if (currChar != EOF)
        {
            if (currChar == 'P')
            {
                Player *player = new Player(renderer, "Sprites/player.png", 40, 60, i * 20, j * 20, lvlObjs->getLevelActive());

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
            else if (currChar == 'I')
            {
                InvBlock *invBlock = new InvBlock(renderer, "Sprites/enemy.png", 20, 20, i * 20, j * 20);
                lvlObjs->addInvBlock(invBlock);
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
}
void handleKeyboardStartScreen(LevelObjects *lvlObj, int *levelID)
{
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_KEYDOWN:
            *levelID = 1;
            *(lvlObj->getLevelActive()) = 0;
            break;
        default:
            break;
        }
    }
}
int handleKeyboardLevel(LevelObjects *lvlObjs, int *levelID){
    SDL_Event event;
    // Events management
    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return 0;
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
            case SDL_SCANCODE_R:
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_1:
            case SDL_SCANCODE_KP_1:
                *levelID = 1;
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_2:
            case SDL_SCANCODE_KP_2:
                *levelID = 2;
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_3:
            case SDL_SCANCODE_KP_3:
                *levelID = 3;
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_4:
            case SDL_SCANCODE_KP_4:
                *levelID = 4;
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_5:
            case SDL_SCANCODE_KP_5:
                *levelID = 5;
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_6:
            case SDL_SCANCODE_KP_6:
                *levelID = 6;
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_7:
            case SDL_SCANCODE_KP_7:
                *levelID = 7;
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_8:
            case SDL_SCANCODE_KP_8:
                *levelID = 8;
                lvlObjs->setLevelActiveValue(0);
                break;
            case SDL_SCANCODE_9:
            case SDL_SCANCODE_KP_9:
                *levelID = 9;
                lvlObjs->setLevelActiveValue(0);
                break;
            default:
                break;
            }
        }
    }
    return 1;
}
void updateLevel(LevelObjects *lvlObjs){
    Player *player = lvlObjs->getPlayer();
    player->update(0, lvlObjs);
    for (auto *var : *lvlObjs->getEnemiesList())
    {
        var->update(0, lvlObjs);
    }
}
void drawLevel(LevelObjects* lvlObjs){
    for (auto *var : *lvlObjs->getEnemiesList())
    {
        var->draw();
    }
    for (auto *var : *lvlObjs->getBlocksList())
    {
        var->draw();
    }
    lvlObjs->getFinish()->draw();
    lvlObjs->getPlayer()->draw();
}