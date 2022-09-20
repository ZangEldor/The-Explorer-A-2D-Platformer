#include "Player.h"
//#include "Collidable.cpp"
//#include "LevelObjects.h"
Player::Player(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
    this->isHookLaunched = 0;
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
        /*
        if(currPoint.y == hookPoint.y){
            this->rect->y -= speed / 30;
            return;
        }
        */
        double slope = (double)(hookPoint.y - currPoint.y) / (hookPoint.x - currPoint.x);
        double yIntersection = (double)(currPoint.y - slope * currPoint.x);
        if (this->horizontalRight)
        {
            this->rect->x += speed / 30;
        }
        else
        {
            this->rect->x -= speed / 30;
        }
        double newY = this->rect->x *slope + yIntersection;
        this->rect->y = newY;
        for (auto *block : data->getBlocksList())
        {
            SDL_Rect *currRect = block->getRect();
            if (!SDL_HasIntersection(this->rect, currRect))
            {
                continue;
            }
            this->rect->x = currPoint.x;
            this->rect->y = currPoint.y;
            this->hook->setIsHooked(0);

            /*
            if (this->horizontalRight)
            {
                this->rect->x = currRect->x - this->rect->w;
            }
            else
            {
                this->rect->x = currRect->x + currRect->w;
            }
            while (SDL_HasIntersection(this->rect, currRect)){
                this->rect->y += 1;
            }
                //this->rect->y = currRect->y + currRect->h;
            this->hook->setIsHooked(0);
            break;
            */
        }
    }
    else
    {
        switch (action)
        {
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
            this->isHookLaunched = 1;
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
    }
    this->hook->update(0, data);
}
Player::~Player()
{
}
