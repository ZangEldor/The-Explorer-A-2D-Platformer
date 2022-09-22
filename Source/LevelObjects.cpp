#include "LevelObjects.h"
#include <stdio.h>
LevelObjects::LevelObjects()
{
    this->player = nullptr;
    this->finish = nullptr;
    this->levelActive = nullptr;
}
std::vector<Enemy *> *LevelObjects::getEnemiesList()
{
    return &this->enemies;
}
std::vector<Block *> *LevelObjects::getBlocksList()
{
    return &this->blocks;
}
std::vector<InvBlock *> *LevelObjects::getInvBlocksList()
{
    return &this->invBlocks;
}
Player *LevelObjects::getPlayer()
{
    return this->player;
}
Background *LevelObjects::getBackground()
{
    return this->background;
}
LevelFinish *LevelObjects::getFinish()
{
    return this->finish;
}
void LevelObjects::addEnemy(Enemy *enemy)
{
    this->enemies.push_back(enemy);
}
void LevelObjects::setPlayer(Player *player)
{
    this->player = player;
}
void LevelObjects::setLevelActive(int *levelActivePtr)
{
    this->levelActive = levelActivePtr;
}
void LevelObjects::setLevelActiveValue(int val)
{
    *this->levelActive = val;
}
int *LevelObjects::getLevelActive()
{
    return this->levelActive;
}
void LevelObjects::addBlock(Block *block)
{
    this->blocks.push_back(block);
}
void LevelObjects::addInvBlock(InvBlock *invBlock)
{
    this->invBlocks.push_back(invBlock);
}
void LevelObjects::setFinish(LevelFinish *finish)
{
    this->finish = finish;
}
void LevelObjects::setBackground(Background *background)
{
    this->background = background;
}
