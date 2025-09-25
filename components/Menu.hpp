#include <ncurses.h>
#include <string.h>
#include <string>
using namespace std;

class Menu
{
public:
  Menu()
  {
    createWindow();
    drawBorder();
  }

  int show()
  {
    int highlight = 0;
    int choice = -1;
    int c;

    while (choice == -1)
    {
      werase(menu);
      drawBorder();

      const char *title = "SNAKE GAME";
      int title_x = (cols - strlen(title)) / 2;

      wattron(menu, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);
      mvwprintw(menu, 2, title_x, "%s", title);
      wattroff(menu, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);

      for (int i = 0; i < NUM_OPTIONS; i++)
      {
        int y = start_y + i * 2;

        if (i == highlight)
        {
          string text = "> " + string(options[i]) + " <";
          int x = (cols - text.size()) / 2;

          wattron(menu, COLOR_PAIR(1) | A_BOLD);
          mvwprintw(menu, y, x, "%s", text.c_str());
          wattroff(menu, COLOR_PAIR(1) | A_BOLD);
        }
        else
        {
          int x = (cols - strlen(options[i])) / 2;

          wattron(menu, COLOR_PAIR(3));
          mvwprintw(menu, y, x, "%s", options[i]);
          wattroff(menu, COLOR_PAIR(3));
        }
      }

      wrefresh(menu);

      c = wgetch(menu);
      switch (c)
      {
      case KEY_UP:
        highlight = (highlight - 1 + NUM_OPTIONS) % NUM_OPTIONS;
        break;
      case KEY_DOWN:
        highlight = (highlight + 1) % NUM_OPTIONS;
        break;
      case 10:
        choice = highlight;
        break;
      }
    }

    werase(menu);
    wrefresh(menu);
    delwin(menu);
    attrset(A_NORMAL);
    clear();
    refresh();

    return choice;
  }

private:
  WINDOW *menu;
  const int rows = 12;
  const int cols = 22;
  int start_y = 5;

  static const int NUM_OPTIONS = 3;
  const char *options[NUM_OPTIONS] = {"New Game", "Rank", "Exit"};

  void createWindow()
  {
    int max_y, max_x;
    getmaxyx(stdscr, max_y, max_x);
    menu = newwin(rows, cols, (max_y - rows) / 2, (max_x - cols) / 2);
    keypad(menu, TRUE);
  }

  void drawBorder()
  {
    wattron(menu, COLOR_PAIR(4));
    wborder(menu, ACS_VLINE, ACS_VLINE, ACS_HLINE, ACS_HLINE,
            ACS_ULCORNER, ACS_URCORNER, ACS_LLCORNER, ACS_LRCORNER);
    wattroff(menu, COLOR_PAIR(4));
  }
};
