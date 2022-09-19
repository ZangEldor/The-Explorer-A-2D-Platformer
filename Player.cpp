#include "Player.h"
//#include "Collidable.cpp"
//#include "LevelObjects.h"
Player::Player(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
    this->horizontalRight = 1;
    this->speed = 500;
    this->hook = new Hook(rendererArg, "C:\\Users\\eldor\\OneDrive\\Desktop\\hook.png", 50, 50, x + width, y + (height / 2), 1);
}
void Player::draw()
{
    if (horizontalRight)
    {
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, NULL, NULL, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, NULL, NULL, SDL_FLIP_HORIZONTAL);
    }
    this->hook->draw();
}
void Player::update(int action, LevelObjects *data)
{
    switch (action)
    {
    case up:
        this->rect->y -= speed / 5;
        break;
    case left:
        this->horizontalRight = 0;
        this->hook->setHorizontalRight(0);
        this->rect->x -= speed / 30;
        break;
    case right:
        this->horizontalRight = 1;
        this->hook->setHorizontalRight(1);
        this->rect->x += speed / 30;
        break;
    case space:
        this->hook->update(1, data);
        break;
    default:
        break;
    }
    for (auto *block : data->getBlocksList())
    {
        SDL_Rect *currRect = block->getRect();
        if (!SDL_HasIntersection(this->rect, currRect))
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
        this->rect->y = currRect->y - this->rect->h;
    }

    if (this->horizontalRight)
    {
        this->hook->getRect()->x = this->rect->x + this->rect->w;
    }
    else
    {
        this->hook->getRect()->x = this->rect->x - this->hook->getRect()->w;
    }
    this->hook->getRect()->y = this->rect->y + (this->rect->h / 2);
    this->hook->update(0, data);
}
Player::~Player()
{
}
