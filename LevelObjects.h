#ifndef LEVELOBJECTS_H
#define LEVELOBJECTS_H
//#include "Player.h"
#include <vector>
#include <list>

class Player;
class Collidable;
class Enemy;
class Block;
class LevelObjects
{
private:
    std::vector<Enemy *> enemies;
    std::vector<Block *> blocks;
    Player *player;
    std::vector<Block *> invBlocks;
    Collidable *finish;

public:
    LevelObjects();
    std::vector<Enemy *> getEnemiesList();
    std::vector<Block *> getBlocksList();
    std::vector<Block *> getInvBlocksList();
    Player *getPlayer();
    Collidable *getFinish();
    void addEnemy(Enemy *enemy);
    void setPlayer(Player *player);
    void addBlock(Block *block);
    void addInvBlock(Block *invBlock);
    void setFinish(Collidable *finish);
};
#endif