#pragma once
#include <ncurses.h>
#include "Drawable.hpp"

class SnakePiece : public Drawable
{
public:
  SnakePiece()
  {
    this->y = 0;
    this->x = 0;
    this->representation = 'o';
    this->color = 4;
  }

  SnakePiece(int y, int x)
  {
    this->y = y;
    this->x = x;
    this->representation = 'o';
    this->color = 4;
  }
};