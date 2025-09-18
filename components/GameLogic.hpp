#include <ncurses.h>
#include "Drawable.hpp"
#include "Board.hpp"
#include "Apple.hpp"
#include "Empty.hpp"

class GameLogic
{
public:
  GameLogic(int h, int w)
  {
    board = Board(h, w);
    gameOver = false;
    srand(time(0));
    lastAppleY = -1;
    lastAppleX = -1;
  }

  bool isGameOver()
  {
    return gameOver;
  }

  void getInput()
  {
    char input = board.getInput();
  }

  void updateGame()
  {
    int y, x;
    board.getEmptyCoordinates(y, x);
    if (lastAppleY != -1 && lastAppleX != -1)
    {
      board.add(Empty(lastAppleY, lastAppleX));
    }
    board.add(Apple(y, x));
    board.add(Drawable(5, 5, '#'));

    lastAppleY = y;
    lastAppleX = x;
  }

  void render()
  {
    board.refresh();
  }

private:
  Board board;
  bool gameOver;
  int lastAppleY, lastAppleX;
};