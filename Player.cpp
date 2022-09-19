#include "Player.h"
Player::Player(SDL_Renderer *rendererArg)
{
    this->speed = 300;
    this->renderer = rendererArg;
    SDL_Surface *surface = IMG_Load("C:\\Users\\eldor\\OneDrive\\Desktop\\Untitled.png");
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    SDL_QueryTexture(this->texture, NULL, NULL, &this->rect.w, &this->rect.h);
    this->rect.w /= 6;
    this->rect.h /= 6;
    this->rect.x = (500 - this->rect.w) / 2;
    this->rect.y = (500 - this->rect.h) / 2;
}
void Player::draw()
{
    SDL_RenderCopy(this->renderer, this->texture, NULL, &this->rect);
}
void Player::update(int action)
{
    switch (action)
    {
    case up:
        this->rect.y -= speed / 30;
        break;
    case left:
        this->rect.x -= speed / 30;
        break;
    case right:
        this->rect.x += speed / 30;
        break;
    default:
        this->rect.y += speed / 30;
        break;
    }
    // right boundary
    if (this->rect.x + this->rect.w > 500)
        this->rect.x = 500 - this->rect.w;

    // left boundary
    if (this->rect.x < 0)
        this->rect.x = 0;

    // bottom boundary
    if (this->rect.y + this->rect.h > 500)
        this->rect.y = 500 - this->rect.h;
    // upper boundary
    if (this->rect.y < 0)
        this->rect.y = 0;
}
Player::~Player()
{
    SDL_DestroyTexture(this->texture);
}
