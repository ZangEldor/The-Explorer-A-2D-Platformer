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
class Background;
class InvBlock;
class LevelObjects
{
private:
    std::vector<Enemy *> enemies;
    std::vector<Block *> blocks;
    Player *player;
    std::vector<InvBlock *> invBlocks;
    LevelFinish *finish;
    Background *background;
    int *levelActive;

public:
    LevelObjects();
    std::vector<Enemy *> *getEnemiesList();
    std::vector<Block *> *getBlocksList();
    std::vector<InvBlock *> *getInvBlocksList();
    Player *getPlayer();
    Background *getBackground();
    LevelFinish *getFinish();
    void addEnemy(Enemy *enemy);
    void setPlayer(Player *player);
    void setLevelActive(int *levelActivePtr);
    void setLevelActiveValue(int val);
    int *getLevelActive();
    void setBackground(Background *background);
    void addBlock(Block *block);
    void addInvBlock(InvBlock *invBlock);
    void setFinish(LevelFinish *finish);
};
#endif