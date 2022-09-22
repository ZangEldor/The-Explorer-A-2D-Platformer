#ifndef INVBLOCK_H
#define INVBLOCK_H
#include "Collidable.h"
class InvBlock : public Collidable
{
public:
    InvBlock(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
    ~InvBlock();
    virtual void draw();
};
#endif