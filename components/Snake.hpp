#pragma once
#include <ncurses.h>
#include "SnakePiece.hpp"
#include <queue>
using namespace std;

enum Direction
{
  UP,
  DOWN,
  LEFT,
  RIGHT
};

class Snake
{
  queue<SnakePiece> pieces;
  Direction currentDirection;

public:
  Snake()
  {
    currentDirection = UP;
  }

  void addPiece(SnakePiece piece)
  {
    pieces.push(piece);
  }

  void removeTail()
  {
    if (!pieces.empty())
    {
      pieces.pop();
    }
  }

  SnakePiece tail()
  {
    return pieces.back();
  }

  SnakePiece head()
  {
    return pieces.front();
  }
};