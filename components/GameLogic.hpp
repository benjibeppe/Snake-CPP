#include <ncurses.h>
#include "Drawable.hpp"
#include "Board.hpp"
#include "Apple.hpp"
#include "Empty.hpp"
#include "Snake.hpp"
#include "Pause.hpp"
#include "Score.hpp"
#include "ChangeLevel.hpp"

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
  Score *scoreWin = nullptr;
  time_t lastAppleTime = 0;

  // Applica le impostazioni del livello selezionato
  void applyLevelSettings(ChangeLevel *levelSelector)
  {
    if (levelSelector)
    {
      // Aggiorna le impostazioni del gioco
      int newSpeed = levelSelector->getCurrentSpeed();
      int newTargetScore = levelSelector->getCurrentScoreToWin();
      int newTimeLimit = levelSelector->getCurrentTime();

      // Applica la nuova velocità alla board
      board.setTimeout(newSpeed);

      // Qui potresti aggiornare altre variabili se le avessi
      // targetScore = newTargetScore;
      // timeLimit = newTimeLimit;
    }
  }

public:
  GameLogic(int h, int w)
  {
    board = Board(h, w, 150);
    scoreWin = new Score(h, w, 12, 22);
    createGame();
  }

  ~GameLogic()
  {
    delete scoreWin;
  }

  void createGame()
  {
    gameOver = false;
    scoreWin->setScore(0);
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
    lastAppleTime = time(nullptr);
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
    int oldTimeout = board.getTimeout();

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
      togglePause(oldTimeout);
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

    time_t now = time(nullptr);
    if (now - lastAppleTime >= 1.5)
    {
      generateApple();
      lastAppleTime = now;
    }

    SnakePiece nextHead = snake.nextHeadPosition();

    int nextChar = board.getCharAt(nextHead.getY(), nextHead.getX()) & A_CHARTEXT;

    switch (nextChar)
    {
    case '@':
      moveSnake(nextHead);
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

      if (nextHead.getY() == lastAppleY && nextHead.getX() == lastAppleX)
      {
        updateScore(10);
      }
      break;
      return;
    }
  }

  void render()
  {
    board.refresh();
  }

  void togglePause(int oldTimeout)
  {
    if (!paused)
    {
      paused = true;

      pauseMenu = new Pause(board.getRows(), board.getCols());

      bool stayInPause = true;
      while (stayInPause)
      {
        int choice = pauseMenu->show();

        if (choice == 0) // Continue
        {
          stayInPause = false;
        }
        else if (choice == 1) // Change level
        {
          ChangeLevel levelSelector(board.getRows(), board.getCols());
          int levelChoice = levelSelector.showLevelSelection();

          if (levelChoice != -1) // Se un livello è stato selezionato
          {
            applyLevelSettings(&levelSelector);
            stayInPause = false;
          }
          // Se levelChoice == -1 (ESC), stayInPause rimane true e torna al menu pause
        }
        else if (choice == 2) // Exit
        {
          gameOver = true;
          stayInPause = false;
        }
      }
      delete pauseMenu;
      pauseMenu = nullptr;
      paused = false;
      board.setTimeout(oldTimeout);
      render();
    }
  }

  void updateScore(int points)
  {
    score = score + points;
    scoreWin->setScore(score);
  }

  bool isPaused() const
  {
    return paused;
  }
};