#include "Block.h"
Block::Block(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
}
void Block::draw()
{
    SDL_RenderCopy(this->renderer, this->texture, NULL, this->rect);
}
Block::~Block()
{
}
