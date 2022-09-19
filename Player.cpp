#include "Player.h"
//#include "Collidable.cpp"
//#include "LevelObjects.h"
Player::Player(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
    this->speed = 500;
}
void Player::draw()
{
    SDL_RenderCopy(this->renderer, this->texture, NULL, this->rect);
}
void Player::update(int action,LevelObjects* data)
{
    switch (action)
    {
    case up:
        this->rect->y -= speed/5;
        break;
    case left:
        this->rect->x -= speed / 30;
        break;
    case right:
        this->rect->x += speed / 30;
        break;
    default:
        break;
    }
    for (auto *block : data->getBlocksList())
    {
        SDL_Rect* currRect = block->getRect();
        if (!SDL_HasIntersection(this->rect,currRect))
        {
            continue;
        }
        switch (action)
        {
        case up:
            this->rect->y = currRect->y + currRect->h;
            break;
        case left:
            this->rect->x = currRect->x + currRect->w;
            break;
        case right:
            this->rect->x = currRect->x - this->rect->w;
            break;
        default:
            break;
        }
    }
    this->rect->y += speed / 30;
    for (auto *block : data->getBlocksList())
    {
        SDL_Rect *currRect = block->getRect();
        if (!SDL_HasIntersection(this->rect, currRect))
        {
            continue;
        }
        this->rect->y = currRect->y-this->rect->h;
    }
 
}
Player::~Player()
{
}
