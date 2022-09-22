#ifndef BACKGROUND_H
#define BACKGROUND_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Background
{
protected:
    SDL_Texture *texture;
    SDL_Rect *rect;
    SDL_Renderer *renderer;

public:
    Background(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
    ~Background();
    SDL_Rect *getRect();
    virtual void draw();
};

#endif