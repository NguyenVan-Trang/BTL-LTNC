#include "game.h"
#include <stdexcept>
#include <iostream>
#include <string>
#include <SDL_image.h>

Game::Game():
    tetromino_{static_cast<Tetromino::Type>(rand() % 7)},
    moveTime_(SDL_GetTicks())
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) throw std::runtime_error("SDL_Init(SDL_INIT_VIDEO)");
    int imgFlags = IMG_INIT_PNG;
    window_ = SDL_CreateWindow("Tetris", 300, 100, 300, 600, SDL_WINDOW_SHOWN);
    renderer_ = SDL_CreateRenderer(window_, 0, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    quit = false;
}

Game::~Game()
{
    SDL_DestroyRenderer(renderer_);
    SDL_DestroyWindow(window_);
    SDL_Quit();
}

void Game::showMenu()
{
    SDL_Surface* menuSurface = IMG_Load("Menu.png");
    SDL_Texture* menuTexture = SDL_CreateTextureFromSurface(renderer_, menuSurface);
    SDL_FreeSurface(menuSurface);
    bool isInMenu = true;
    SDL_Event ev;
    while(!quit && isInMenu)
    {
        while (SDL_PollEvent(&ev) != 0)
        {
            if(ev.type == SDL_QUIT) quit = true;
            else if (ev.type == SDL_KEYDOWN) isInMenu = false; // Exit menu loop on any key press
        }
        //Render menu
        SDL_RenderClear(renderer_);
        SDL_RenderCopy(renderer_, menuTexture, nullptr, nullptr);
        SDL_RenderPresent(renderer_);
    }
    SDL_DestroyTexture(menuTexture);
}

bool Game::tick()
{
    if(quit) return false;
    SDL_Event e;
    if (SDL_WaitEventTimeout(&e, 200))
  {
    switch (e.type)
    {
    case SDL_KEYDOWN:
      {
        switch (e.key.keysym.sym)
        {
        case SDLK_DOWN:
          {
            Tetromino t = tetromino_;
            t.move(0, 1);
            if (!well_.isCollision(t))
              tetromino_ = t;
          }
          break;
        case SDLK_RIGHT:
          {
            Tetromino t = tetromino_;
            t.move(1, 0);
            if (!well_.isCollision(t))
              tetromino_ = t;
          }
          break;
        case SDLK_LEFT:
          {
            Tetromino t = tetromino_;
            t.move(-1, 0);
            if (!well_.isCollision(t))
              tetromino_ = t;
          }
          break;
        case SDLK_UP:
          {
            Tetromino t = tetromino_;
            t.rotate();
            if (!well_.isCollision(t))
              tetromino_ = t;
          }
          break;
        }
      }
      break;
        case SDL_QUIT:
      return false;
        }
    }
    SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 0xff);
    SDL_RenderClear(renderer_);
    well_.draw(renderer_);
    tetromino_.draw(renderer_);
    if (SDL_GetTicks() > moveTime_)
    {
        moveTime_ += 750;
        Tetromino t = tetromino_;
        t.move(0, 1);
        check(t);
    }
    SDL_RenderPresent(renderer_);
    return true;
};


void Game::check(const Tetromino &t)
{
    if(well_.isCollision(t))
    {
        well_.unite(tetromino_);
        tetromino_ = Tetromino{static_cast<Tetromino::Type>(rand() % 7)};
        if (well_.isCollision(tetromino_)) well_ = Well();
    } else tetromino_ = t;
}
