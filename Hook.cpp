#include "Collidable.cpp"
#include "Hook.h"
#include <cmath>
#include<math.h>
#define _USE_MATH_DEFINES
Hook::Hook(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y, int horizontalRight) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
    this->angle = 0.0;
    this->isLaunched = 0.0;
    this->verticalUp = 1;
    this->horizontalRight = horizontalRight;
}
void Hook::draw()
{
    if (horizontalRight)
    {
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, this->angle, NULL, SDL_FLIP_NONE);
    }
    else
    {
        SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, this->angle, NULL, SDL_FLIP_HORIZONTAL);
    }
}
void Hook::update(int action, LevelObjects *data)
{
    SDL_Point currLocation;
    currLocation.x = this->rect->x;
    currLocation.y = this->rect->y;

    if (isLaunched == 0 && action == 0)
    {
        if (this->verticalUp != 0)
        {
            this->angle += 1.0;
            if (this->angle > 90)
            {
                this->angle = 90;
                this->verticalUp = 0;
            }
        }
        else
        {
            this->angle -= 1.0;
            if (this->angle < -90)
            {
                this->angle = -90;
                this->verticalUp = 1;
            }
        }
    }
    else if (isLaunched == 0 && action == 1)
    {
        isLaunched = 1;
        launchPoint.x = this->rect->x;
        launchPoint.y = this->rect->y;
    }
    else if(isLaunched == 1){
        double radianAngle = angle * (3.14 / 180);
        double result = 20 * sin(radianAngle);
        this->rect->y += result;
        if(horizontalRight){
            result = 20 * cos(radianAngle);
            this->rect->x += result;
        }else{
            result = 20 * cos(radianAngle);
            this->rect->x -= result;
        }
        for (auto *block : data->getBlocksList())
        {
            SDL_Rect *currRect = block->getRect();
            if (SDL_HasIntersection(this->rect, currRect))
            {
                this->rect->x = currLocation.x;
                this->rect->y = currLocation.y;
                isLaunched=0;
                 break;
            }
            
        }
    }
}
void Hook::setHorizontalRight(int value)
{
    this->horizontalRight = value;
}
Hook::~Hook()
{
}
