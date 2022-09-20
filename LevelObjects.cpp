#include "LevelObjects.h"
LevelObjects::LevelObjects(){
    this->player = nullptr;
    this->finish = nullptr;
}
std::vector<Enemy *> LevelObjects::getEnemiesList()
{
    return this->enemies;
}
std::vector<Block *> LevelObjects::getBlocksList()
{
    return this->blocks;
}
std::vector<Block *> LevelObjects::getInvBlocksList()
{
    return this->invBlocks;
}
Player *LevelObjects::getPlayer(){
    return this->player;
}
Collidable *LevelObjects::getFinish()
{
    return this->finish;
}
void LevelObjects::addEnemy(Enemy *enemy)
{
    this->enemies.push_back(enemy);
}
void LevelObjects::setPlayer(Player *player){
    this->player = player;
}
void LevelObjects::addBlock(Block *block)
{
    this->blocks.push_back(block);
}
void LevelObjects::addInvBlock(Block *invBlock)
{
    this->invBlocks.push_back(invBlock);
}
void LevelObjects::setFinish(Collidable *finish){
    this->finish = finish;
}