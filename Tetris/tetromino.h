#ifndef TETROMINO_H_INCLUDED
#define TETROMINO_H_INCLUDED

#pragma once
#include <SDL.h>

class Tetromino
{
public:
    enum Type { I = 0, J, L, O, S, T, Z };
    Tetromino(Type);
    void draw(SDL_Renderer *);
    void move(int dx, int dy);
    void rotate();
    bool isBlock(int x, int y) const;
    int x() const;
    int y() const;

private:
    Type type_;
    int x_;
    int y_;
    int angle_; // 0 -0deg, 1 -90deg, 2 -180deg, 3 - 270deg
};

#endif // TETROMINO_H_INCLUDED
