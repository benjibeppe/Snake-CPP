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

  char headChar(Direction d)
  {
    switch (d)
    {
    case UP:
      return '^';
    case DOWN:
      return 'v';
    case LEFT:
      return '<';
    case RIGHT:
      return '>';
    }
    return 'o';
  }

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

    SnakePiece h = snake.head();
    SnakePiece head(h.getY(), h.getX());
    head.setRepresentation('@');
    board.add(head);

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
    SnakePiece currHead = snake.head();

    SnakePiece body(currHead.getY(), currHead.getX());
    body.setRepresentation('o');
    board.add(body);

    SnakePiece tail = snake.tail();
    board.add(Empty(tail.getY(), tail.getX()));
    snake.removeTail();

    nextHead.setRepresentation('@');
    addSnakePiece(nextHead);
  }

  void updateGame()
  {
    SnakePiece nextHead = snake.nextHeadPosition();

    int nextChar = board.getCharAt(nextHead.getY(), nextHead.getX()) & A_CHARTEXT;

    switch (nextChar)
    {
    case '@':
      moveSnake(nextHead);
      generateApple();
      break;
    case ' ':
      moveSnake(nextHead);
      break;
    default:
      gameOver = true;
      return;
    }
  }

  void render()
  {
    board.refresh();
  }
};