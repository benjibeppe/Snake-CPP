#include <ncurses.h>
#include "components/Board.hpp"
#include "components/GameLogic.hpp"
#include "components/Drawable.hpp"

#define BOARD_WIDTH 45
#define BOARD_HEIGHT 20

int main()
{
  initscr();
  refresh();

  noecho();

  GameLogic game(BOARD_HEIGHT, BOARD_WIDTH);

  while (game.isGameOver() == false)
  {
    game.getInput();
    game.updateGame();
    game.render();
  }

  getch();
  endwin();

  return 0;
}