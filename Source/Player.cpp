#include "Player.h"
#include "Block.h"
#include "Enemy.h"
//#include "Collidable.cpp"
#include "LevelObjects.h"
#include "LevelFinish.h"
#include <algorithm>
Player::Player(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y, int *levelActivePtr) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
    this->isHookLaunched = 0;
    this->horizontalRight = 1;
    this->speed = 20;
    this->levelActivePtr = levelActivePtr;
    this->hook = new Hook(rendererArg, "Sprites/hook.png", 20, 20, x + 25, y + 4, 1);
}
void Player::draw()
{
    SDL_Point hookCenter;
    hookCenter.x = this->hook->getRect()->x + this->hook->getRect()->w / 2;
    hookCenter.y = this->hook->getRect()->y + this->hook->getRect()->h / 2;
    if (horizontalRight)
    {
        if (this->hook->getIsHooked() || this->hook->getIsLaunched())
        {

            SDL_RenderDrawLine(this->renderer, this->getRect()->x + 26, this->getRect()->y + 22, hookCenter.x, hookCenter.y);
        }
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, NULL, &hookCenter, SDL_FLIP_NONE);
    }
    else
    {
        if (this->hook->getIsHooked() || this->hook->getIsLaunched())
        {
            SDL_RenderDrawLine(this->renderer, this->getRect()->x + 12, this->getRect()->y + 22, hookCenter.x, hookCenter.y);
        }
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, NULL, &hookCenter, SDL_FLIP_HORIZONTAL);
    }
    this->hook->draw();
}
bool Player::checkEnemyCollision(LevelObjects *data)
{
    for (auto *enemy : *data->getEnemiesList())
    {

        if (SDL_HasIntersection(this->rect, enemy->getRect()))
        {
            return true;
        }
    }
    return false;
}
void Player::update(int action, LevelObjects *data)
{
    if (this->hook->getIsLaunched())
    {
    }
    else if (this->hook->getIsHooked())
    {
        SDL_Point hookPoint;
        SDL_Point currPoint;
        hookPoint.x = this->hook->getRect()->x;
        hookPoint.y = this->hook->getRect()->y;
        currPoint.x = this->rect->x;
        currPoint.y = this->rect->y;
        if (std::abs(hookPoint.x - currPoint.x) < speed)
        {
            if (std::abs(this->rect->y - hookPoint.y) > speed)
            {
                this->rect->y -= speed;
            }
            else
            {
                this->hook->setIsHooked(0);
            }
        }
        else
        {
            double slope = (double)(hookPoint.y - currPoint.y) / (hookPoint.x - currPoint.x);
            double yIntersection = (double)(currPoint.y - slope * currPoint.x);
            if (this->horizontalRight)
            {
                this->rect->x += speed;
            }
            else
            {
                this->rect->x -= speed;
            }
            double newY = this->rect->x * slope + yIntersection;
            this->rect->y = newY;
        }
        for (auto *block : *data->getBlocksList())
        {
            SDL_Rect *currRect = block->getRect();
            if (!SDL_HasIntersection(this->rect, currRect))
            {
                continue;
            }
            this->rect->x = currPoint.x;
            this->rect->y = currPoint.y;
            this->hook->setIsHooked(0);
        }
    }
    else
    {

        switch (action)
        {
        case left:
            this->horizontalRight = 0;
            this->hook->setHorizontalRight(0);
            this->rect->x -= speed;
            break;
        case right:
            this->horizontalRight = 1;
            this->hook->setHorizontalRight(1);
            this->rect->x += speed;
            break;
        case space:
            this->isHookLaunched = 1;
            this->hook->update(1, data);
            break;
        default:
            break;
        }

        for (auto *block : *data->getBlocksList())
        {
            SDL_Rect *currRect = block->getRect();

            if (!SDL_HasIntersection(this->rect, currRect))
            {

                continue;
            }

            switch (action)
            {
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

        this->rect->y += speed / 4;
        for (auto *block : *data->getBlocksList())
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
            this->hook->getRect()->x = this->rect->x + 25;
        }
        else
        {
            this->hook->getRect()->x = this->rect->x - 6;
        }
        this->hook->getRect()->y = this->rect->y + 4;
    }

    if (checkEnemyCollision(data))
    {
        *(this->levelActivePtr) = 0;
    }

    if (SDL_HasIntersection(this->rect, data->getFinish()->getRect()))
    {
        *(this->levelActivePtr) = 2;
    }
    this->hook->update(0, data);
}
Player::~Player()
{
}
