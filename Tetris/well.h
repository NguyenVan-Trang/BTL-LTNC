#ifndef WELL_H_INCLUDED
#define WELL_H_INCLUDED

#pragma once
#include "tetromino.h"
#include <SDL.h>


class Well
{
public:
    Well();
    void draw(SDL_Renderer *);
    enum {Width = 10, Height = 20};
    bool isCollision(const Tetromino &t) const;
    void unite(const Tetromino &);
private:
    bool data[Width][Height];
};

#endif // WELL_H_INCLUDED
