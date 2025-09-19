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
    pieces.pop();
  }

  SnakePiece tail()
  {
    return pieces.front();
  }

  SnakePiece head()
  {
    return pieces.back();
  }

  Direction getDirection()
  {
    return currentDirection;
  }

  void setDirection(Direction newDirection)
  {
    currentDirection = newDirection;
  }

  SnakePiece nextHeadPosition()
  {
    SnakePiece headPiece = head();
    int newY = headPiece.getY();
    int newX = headPiece.getX();

    switch (currentDirection)
    {
    case UP:
      newY -= 1;
      break;
    case DOWN:
      newY += 1;
      break;
    case LEFT:
      newX -= 1;
      break;
    case RIGHT:
      newX += 1;
      break;
    }

    return SnakePiece(newY, newX);
  }
};