#include "Spike.h"
#include "Block.h"

Spike::Spike(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y) : Enemy(rendererArg, sprite_path, width, height, x, y)
{
}
void Spike::draw()
{
    SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, NULL, NULL, SDL_FLIP_NONE);
}
void Spike::update(int action, LevelObjects *data)
{
}
Spike::~Spike()
{
}