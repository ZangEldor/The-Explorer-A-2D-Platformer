#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "Collidable.h"
#include "Updatable.h"
#include "LevelObjects.h"
#include "Hook.h"
class LevelObjects;

class Player : public Collidable, public Updatable
{
private:
    int speed;
    int isHookLaunched;
    Hook* hook;
    int horizontalRight;
    public:
        Player(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
        ~Player();
        virtual void draw();
        virtual void update(int action, LevelObjects* data);
};
#endif