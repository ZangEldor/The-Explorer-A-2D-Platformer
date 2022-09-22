#include "Enemy.h"
#include "LevelObjects.h"
#include "Updatable.h"
class Spike : public Enemy
{

public:
    Spike(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
    ~Spike();
    virtual void draw();
    virtual void update(int action, LevelObjects *data);
};