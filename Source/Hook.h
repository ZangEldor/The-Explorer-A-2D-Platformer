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
    int verticalUp;
    int horizontalRight;
    int isLaunched;
    int isHooked;
    SDL_Point launchPoint;

public:
    Hook(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y, int horizontalRight);
    ~Hook();
    int getIsHooked();
    int getIsLaunched();
    double getAngle();
    void setHorizontalRight(int value);
    void setIsLaunced(int value);
    void setIsHooked(int value);

    virtual void draw();
    virtual void update(int action, LevelObjects *data);
};
#endif