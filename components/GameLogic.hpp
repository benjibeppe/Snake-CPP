#include <ncurses.h>
#include "Drawable.hpp"
#include "Board.hpp"
#include "Apple.hpp"
#include "Empty.hpp"
#include "Snake.hpp"
#include "Pause.hpp"

class GameLogic
{

private:
  Board board;
  bool gameOver;
  int lastAppleY, lastAppleX;
  int snakeLength = 23;
  int snakeStartingX = 27;
  int snakeStartingY = 9;
  bool paused = false;
  int score = 0;
  Snake snake;
  Pause *pauseMenu = nullptr;

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
      togglePause();
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
    board.clearCell(tail.getY(), tail.getX());
    snake.removeTail();

    nextHead.setRepresentation('@');
    addSnakePiece(nextHead);
  }

  void updateGame()
  {
    if (paused)
      return;

    SnakePiece nextHead = snake.nextHeadPosition();

    int nextChar = board.getCharAt(nextHead.getY(), nextHead.getX()) & A_CHARTEXT;

    switch (nextChar)
    {
    case '@':
      moveSnake(nextHead);
      generateApple();
      updateScore(10);
      break;
    case ' ':
      moveSnake(nextHead);
      break;
    case 'o':
      gameOver = true;
      return;
    default:
      int maxY = board.getRows() - 2;
      int maxX = board.getCols() - 2;

      if (nextHead.getY() <= 0) // sopra
        nextHead.setY(maxY);
      else if (nextHead.getY() >= maxY + 1) // sotto
        nextHead.setY(1);

      if (nextHead.getX() <= 0) // sinistra
        nextHead.setX(maxX);
      else if (nextHead.getX() >= maxX + 1) // destra
        nextHead.setX(1);

      moveSnake(nextHead);
      break;
      return;
    }
  }

  void render()
  {
    board.refresh();
  }

  void togglePause()
  {
    if (!paused)
    {
      paused = true;
      pauseMenu = new Pause(board.getRows(), board.getCols());
      pauseMenu->drawBorder();
    }
    else
    {
      paused = false;
      delete pauseMenu;
      pauseMenu = nullptr;
      board.redrawBoard();
    }
  }

  void updateScore(int points)
  {
    score += points;
  }

  bool isPaused() const
  {
    return paused;
  }
};