#include "LevelFinish.h"
LevelFinish::LevelFinish(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
}
void LevelFinish::draw()
{
    SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, NULL, NULL, SDL_FLIP_NONE);
}

LevelFinish::~LevelFinish()
{
}