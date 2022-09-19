#ifndef PLAYER_H
#define PLAYER_H
#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "actions.cpp"
class Player{
    private:
    SDL_Texture* texture;
    SDL_Rect rect;
    SDL_Renderer* renderer;
    int speed;
    public:
    Player(SDL_Renderer* rendererArg);
    ~Player();
    void draw();
    void update(int action);
};
#endif