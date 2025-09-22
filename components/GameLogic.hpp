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
      addSnakePiece(piece);
    }

    generateApple();
  }

  void addSnakePiece(SnakePiece piece)
  {
    snake.addPiece(piece);
    board.add(piece);
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
    case 'w':
    case 'W':
      snake.setDirection(UP);
      break;

    case KEY_DOWN:
    case 's':
    case 'S':
      snake.setDirection(DOWN);
      break;

    case KEY_LEFT:
    case 'a':
    case 'A':
      snake.setDirection(LEFT);
      break;

    case KEY_RIGHT:
    case 'd':
    case 'D':
      snake.setDirection(RIGHT);
      break;

    case 27:
      board.setTimeout(-1);
      while (board.getInput() != 27) // ASCII per ESC
        ;
      board.setTimeout(board.snakeSpeed);
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

  void moveSnake(SnakePiece nextHead)
  {
    SnakePiece tail = snake.tail();
    int tailY = tail.getY();
    int tailX = tail.getX();
    board.add(Empty(tailY, tailX));
    snake.removeTail();

    addSnakePiece(nextHead);
  }

  void updateGame()
  {
    SnakePiece nextHead = snake.nextHeadPosition();

    moveSnake(nextHead);

    if (nextHead.getY() == lastAppleY && nextHead.getX() == lastAppleX)
    {
      generateApple();
    }
  }

  void render()
  {
    board.refresh();
  }
};