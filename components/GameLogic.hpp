#include <ncurses.h>
#include "Drawable.hpp"
#include "Board.hpp"
#include "Apple.hpp"
#include "Empty.hpp"
#include "Snake.hpp"

class GameLogic
{

private:
  Board board;
  bool gameOver;
  int lastAppleY, lastAppleX;
  int snakeLength = 23;
  int snakeStartingX = 27;
  int snakeStartingY = 9;
  Snake snake;

public:
  GameLogic(int h, int w)
  {
    board = Board(h, w);
    createGame();
  }

  void createGame()
  {
    gameOver = false;
    srand(time(0));
    lastAppleY = -1;
    lastAppleX = -1;

    for (int i = 0; i < snakeLength; ++i)
    {
      SnakePiece piece(snakeStartingY, snakeStartingX - i);
      board.add(piece);
      snake.addPiece(piece);
    }
  }

  bool isGameOver()
  {
    return gameOver;
  }

  void getInput()
  {
    int input = board.getInput();
    switch (input)
    {
    case KEY_UP:
      snake.setDirection(UP);
      break;
    case KEY_DOWN:
      snake.setDirection(DOWN);
      break;
    case KEY_LEFT:
      snake.setDirection(LEFT);
      break;
    case KEY_RIGHT:
      snake.setDirection(RIGHT);
      break;
    }
  }

  void generateApple()
  {
    int y, x;
    board.getEmptyCoordinates(y, x);
    board.add(Apple(y, x));
    lastAppleY = y;
    lastAppleX = x;
  }

  void updateGame()
  {
    SnakePiece nextHead = snake.nextHeadPosition();

    if (nextHead.getY() != lastAppleY || nextHead.getX() != lastAppleX)
    {
      SnakePiece tail = snake.tail();
      int tailY = tail.getY();
      int tailX = tail.getX();
      board.add(Empty(tailY, tailX));
      snake.removeTail();
      board.add(nextHead);
      snake.addPiece(nextHead);
    }
  }

  void render()
  {
    board.refresh();
  }
};