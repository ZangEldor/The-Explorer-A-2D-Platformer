#include "Collidable.cpp"
#include "Hook.h"
Hook::Hook(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y) : Collidable(rendererArg, sprite_path, width, height, x, y)
{
    this->angle = 0.0;
    this->direction = 1;
}
void Hook::draw()
{
    SDL_RenderCopyEx(this->renderer, this->texture, NULL, this->rect, this->angle, NULL, SDL_FLIP_NONE);
}
void Hook::update(int action, LevelObjects *data)
{
    if(this->direction != 0){
   this->angle += 1.0;
   if (this->angle > 90)
   {
       this->angle = 90;
       this->direction = 0;
   }
    }else{
        this->angle -= 1.0;
        if (this->angle < -90)
        {
            this->angle = -90;
            this->direction = 1;
        }
    }
}
Hook::~Hook()
{
}
