#ifndef BLOCK_H
#define BLOCK_H
#include "Collidable.h"
class Block : public Collidable {
public:
    Block(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y);
    ~Block();
    virtual void draw();
};
#endif