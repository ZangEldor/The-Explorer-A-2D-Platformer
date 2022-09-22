#include "Collidable.h"
Collidable::Collidable(SDL_Renderer *rendererArg, char *sprite_path,int width, int height, int x,int y)
{
    this->rect = new SDL_Rect();
     this->renderer = rendererArg;
    SDL_Surface *surface = IMG_Load(sprite_path);
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(this->texture, NULL, NULL, &this->rect->w, &this->rect->h);

    this->rect->w = width;
    this->rect->h = height;
    this->rect->x = x;
    this->rect->y = y;
}
Collidable::~Collidable()
{
    SDL_DestroyTexture(this->texture);
}
SDL_Rect* Collidable::getRect(){
    return this->rect;
}
