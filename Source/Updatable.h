#ifndef UPDATABLE_H
#define UPDATABLE_H
//#include "LevelObjects.h"
#include <vector>
class LevelObjects;
class Updatable
{
private:


public:
    virtual void update(int action, LevelObjects *data) = 0;
};
#endif