#include "Player.h"
#include "Block.h"
#include "Enemy.h"
//#include "Collidable.cpp"
#include "LevelObjects.h"
#include "LevelFinish.h"
#include <algorithm>
Player::Player(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y, int* levelActivePtr) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
    this->isHookLaunched = 0;
    this->horizontalRight = 1;
    this->speed = 20;
    this->levelActivePtr = levelActivePtr;
    this->hook = new Hook(rendererArg, "Newfolder/hook.png", 20, 20, x + width, y + (height / 2), 1);
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
bool Player::checkEnemyCollision(LevelObjects *data){
    for (auto *enemy : data->getEnemiesList())
    {

        if (SDL_HasIntersection(this->rect,enemy->getRect()))
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
        /*
        if(currPoint.y == hookPoint.y){
            this->rect->y -= speed / 30;
            return;
        }
        */
        if (hookPoint.x == currPoint.x){
            if (std::abs(this->rect->y - hookPoint.y) > speed){
                this->rect->y -= speed;
            }else{
                this->hook->setIsHooked(0);
            }
        }else{
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
        double newY =this->rect->x * slope + yIntersection;
        /*
        if (std::abs(newY - this->rect->y)>=20){
             newY = this->rect->y - 19;
        }
        */
        this->rect->y = newY;
        }
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
        this->rect->y += speed;
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
        this->hook->getRect()->y = this->rect->y + (this->rect->h / 2) - (this->hook->getRect()->h / 2);
    }
    if(checkEnemyCollision(data)){
        *(this->levelActivePtr) = 0;
    }
    if(SDL_HasIntersection(this->rect,data->getFinish()->getRect())){
        *(this->levelActivePtr) = 0;
    }
    this->hook->update(0, data);
}
Player::~Player()
{
}
