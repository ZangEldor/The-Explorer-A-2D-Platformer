#ifndef COLLIDABLE_H
#define COLLIDABLE_H
#include <stdio.h>
#include <string>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "actions.cpp"
#include <vector>

class Collidable
{
protected:
    SDL_Texture *texture;
    SDL_Rect* rect;
    SDL_Renderer *renderer;

public:
    Collidable(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
    ~Collidable();
    SDL_Rect* getRect();
     virtual void draw() = 0;
};

#endif