#ifndef LEVELOBJECTS_H
#define LEVELOBJECTS_H
//#include "Player.h"
//#include "LevelFinish.h"
#include <vector>
#include <list>

class Player;
class Collidable;
class Enemy;
class Block;
class LevelFinish;
class LevelObjects
{
private:
    std::vector<Enemy *> enemies;
    std::vector<Block *> blocks;
    Player *player;
    std::vector<Block *> invBlocks;
    LevelFinish *finish;

public:
    LevelObjects();
    std::vector<Enemy *> getEnemiesList();
    std::vector<Block *> getBlocksList();
    std::vector<Block *> getInvBlocksList();
    Player *getPlayer();
    LevelFinish *getFinish();
    void addEnemy(Enemy *enemy);
    void setPlayer(Player *player);
    void addBlock(Block *block);
    void addInvBlock(Block *invBlock);
    void setFinish(LevelFinish *finish);
};
#endif