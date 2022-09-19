#ifndef HOOK_H
#define HOOK_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Collidable.h"
#include "Updatable.h"
#include "LevelObjects.h"
class Hook : public Collidable, public Updatable
{
private:
    double angle;
    int direction;

public:
    Hook(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
    ~Hook();
    virtual void draw();
    virtual void update(int action, LevelObjects *data);
};
#endif