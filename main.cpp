#include <ncurses.h>
#include "components/Board.hpp"
#include "components/GameLogic.hpp"
#include "components/Drawable.hpp"
#include "components/Menu.hpp"

#define BOARD_WIDTH 45
#define BOARD_HEIGHT 20

int main()
{
  initscr();
  refresh();
  noecho();

  if (has_colors())
  {
    start_color();
    use_default_colors();
    init_pair(1, COLOR_BLUE, -1);
    init_pair(2, COLOR_RED, -1);
    init_pair(3, COLOR_MAGENTA, -1);
    init_pair(4, COLOR_GREEN, -1);
    init_pair(5, COLOR_RED, -1);
    init_pair(6, COLOR_BLUE, -1);
    init_pair(7, -1, COLOR_BLACK);
    init_pair(8, -1, COLOR_RED);
  }

  curs_set(0);

  Menu menu;
  int choice = menu.show();

  if (choice == 0)
  {
    GameLogic game(BOARD_HEIGHT, BOARD_WIDTH);
    while (!game.isGameOver())
    {
      game.getInput();
      game.updateGame();
      game.render();
    }
  }
  else if (choice == 1)
  {
    mvprintw(0, 0, "Ranking");
    refresh();
  }

  endwin();
  return 0;
}