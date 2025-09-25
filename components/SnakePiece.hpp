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
  }

  SnakePiece(int y, int x)
  {
    this->y = y;
    this->x = x;
    this->representation = 'o';
    this->color = 4;
  }

  void setRepresentation(char c) { this->representation = c; }
  void setColor(int c) { this->color = c; }
  void setX(int x) { this->x = x; }
  void setY(int y) { this->y = y; }
};