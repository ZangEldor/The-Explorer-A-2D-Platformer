#include "LevelObjects.h"
LevelObjects::LevelObjects(){
    this->player = nullptr;
    this->finish = nullptr;
}
std::vector<Collidable *>
LevelObjects::getEnemiesList()
{
    return this->enemies;
}
std::vector<Collidable *> LevelObjects::getBlocksList(){
    return this->blocks;
}
std::vector<Collidable *> LevelObjects::getInvBlocksList(){
    return this->invBlocks;
}
Player *LevelObjects::getPlayer(){
    return this->player;
}
Collidable *LevelObjects::getFinish()
{
    return this->finish;
}
void LevelObjects::addEnemy(Collidable *enemy){
    this->enemies.push_back(enemy);
}
void LevelObjects::setPlayer(Player *player){
    this->player = player;
}
void LevelObjects::addBlock(Collidable *block)
{
    this->blocks.push_back(block);
}
void LevelObjects::addInvBlock(Collidable *invBlock)
{
    this->invBlocks.push_back(invBlock);
}
void LevelObjects::setFinish(Collidable *finish){
    this->finish = finish;
}