#include "Collidable.h"
#include "LevelObjects.h"
#include "Updatable.h"
class Enemy : public Collidable, Updatable
{
    int speed;
    int horizontalRight;

public:
    Enemy(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
    ~Enemy();
    virtual void draw();
    virtual void update(int action, LevelObjects *data);
};