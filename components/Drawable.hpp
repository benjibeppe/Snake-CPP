#pragma once

class Drawable
{
public:
  Drawable()
  {
    y = 0;
    x = 0;
    representation = ' ';
  }

  Drawable(int y, int x, char rep)
  {
    this->y = y;
    this->x = x;
    this->representation = rep;
  }

  int getX() { return x; }
  int getY() { return y; }
  char getRepresentation() { return representation; }

protected:
  int y, x;
  char representation;
};