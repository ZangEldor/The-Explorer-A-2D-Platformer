#include "Enemy.h"
#include "Block.h"

Enemy::Enemy(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
    this->horizontalRight = 1;
    this->speed = 200;
}
void Enemy::draw()
{
    if (horizontalRight)
    {
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, NULL, NULL, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, NULL, NULL, SDL_FLIP_HORIZONTAL);
    }
}
void Enemy::update(int action, LevelObjects *data)
{
    if (this->horizontalRight)
    {
        this->rect->x += speed / 30;
    }
    else
    {
        this->rect->x -= speed / 30;
    }
    for (auto *block : data->getBlocksList())
    {
        SDL_Rect *currRect = block->getRect();
        if (!SDL_HasIntersection(this->rect, currRect))
        {
            continue;
        }
        if (this->horizontalRight)
        {
            this->rect->x = currRect->x - this->rect->w;
            this->horizontalRight = 0;
        }
        else
        {
            this->rect->x = currRect->x + currRect->w;
            this->horizontalRight = 1;
        }
    }
    // gravity
    this->rect->y += speed / 30;
    for (auto *block : data->getBlocksList())
    {
        SDL_Rect *currRect = block->getRect();
        if (!SDL_HasIntersection(this->rect, currRect))
        {
            continue;
        }
        this->rect->y = currRect->y - this->rect->h;
    }
}
Enemy::~Enemy()
{
}