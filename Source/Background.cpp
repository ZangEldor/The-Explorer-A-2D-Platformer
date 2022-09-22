#include "Background.h"
Background::Background(SDL_Renderer *rendererArg, char *sprite_path, int width, int height, int x, int y)
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
Background::~Background()
{
    SDL_DestroyTexture(this->texture);
}
SDL_Rect *Background::getRect()
{
    return this->rect;
}
void Background::draw()
{
    SDL_RenderCopy(this->renderer, this->texture, NULL, this->rect);
}
