#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#pragma once
#include "well.h"
#include <SDL.h>
#include <SDL_image.h>


const int SCREEN_WIDTH = 300;
const int SCREEN_HEIGHT = 600;

class Game
{
public:
    Game();
    ~Game();
    bool tick();
    void showMenu();

private:
    bool quit;
    Game(const Game&);
    Game &operator = (const Game &);
    SDL_Window *window_;
    SDL_Renderer *renderer_;
    Well well_;
    Tetromino tetromino_;
    uint32_t moveTime_;
    void check(const Tetromino &);
};

#endif // GAME_H_INCLUDED
