#include "Collidable.h"
#include "LevelObjects.h"
#include "Updatable.h"
class LevelFinish : public Collidable
{

public:
    LevelFinish(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
    ~LevelFinish();
    virtual void draw();
};