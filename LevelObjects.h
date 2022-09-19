#ifndef LEVELOBJECTS_H
#define LEVELOBJECTS_H
//#include "Player.h"
#include <vector>
#include <list>
class Player;
class Collidable;
class LevelObjects
{
private:
    std::vector<Collidable *> enemies;
    std::vector<Collidable *> blocks;
    Player *player;
    std::vector<Collidable *> invBlocks;
    Collidable *finish;

public:
    LevelObjects();
    std::vector<Collidable *> getEnemiesList();
    std::vector<Collidable *> getBlocksList();
    std::vector<Collidable *> getInvBlocksList();
    Player *getPlayer();
    Collidable *getFinish();
    void addEnemy(Collidable *enemy);
    void setPlayer(Player *player);
    void addBlock(Collidable *block);
    void addInvBlock(Collidable *invBlock);
    void setFinish(Collidable *finish);
};
#endif