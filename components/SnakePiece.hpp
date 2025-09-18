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
    this->representation = 'O';
  }

  SnakePiece(int y, int x)
  {
    this->y = y;
    this->x = x;
    this->representation = 'O';
  }
};