#pragma once
#include <ncurses.h>
#include <string.h>
#include <string>
using namespace std;

class Pause
{
public:
  Pause(int boardH, int boardW)
  {
    this->boardW = boardW;
    int pauseH = boardH;
    int pauseW = boardW / 2;
    pauseWin = nullptr;
    createWindow(pauseH, pauseW);
    drawBorder();
  }

  ~Pause()
  {
    if (pauseWin)
    {
      werase(pauseWin);
      wrefresh(pauseWin);
      delwin(pauseWin);
      pauseWin = nullptr;
    }
  }

  int show()
  {
    int highlight = 0;
    int choice = -1;
    int c;

    while (choice == -1)
    {
      werase(pauseWin);
      drawBorder();

      const char *title = "PAUSE";
      int title_x = (cols - strlen(title)) / 2;

      wattron(pauseWin, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);
      mvwprintw(pauseWin, 2, title_x, "%s", title);
      wattroff(pauseWin, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);

      for (int i = 0; i < NUM_OPTIONS; i++)
      {
        int y = start_y + i * 2;

        if (i == highlight)
        {
          string text = "> " + string(options[i]) + " <";
          int x = (cols - text.size()) / 2;

          wattron(pauseWin, COLOR_PAIR(1) | A_BOLD);
          mvwprintw(pauseWin, y, x, "%s", text.c_str());
          wattroff(pauseWin, COLOR_PAIR(1) | A_BOLD);
        }
        else
        {
          int x = (cols - strlen(options[i])) / 2;

          wattron(pauseWin, COLOR_PAIR(3));
          mvwprintw(pauseWin, y, x, "%s", options[i]);
          wattroff(pauseWin, COLOR_PAIR(3));
        }
      }

      wrefresh(pauseWin);

      c = wgetch(pauseWin);
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
      case 27: // ESC per riprendere
        choice = 0;
        break;
      }
    }

    werase(pauseWin);
    wrefresh(pauseWin);

    return choice;
  }

  void drawBorder()
  {
    if (!pauseWin)
      return;
    wattron(pauseWin, COLOR_PAIR(2));
    wborder(pauseWin,
            ACS_VLINE, ACS_VLINE,
            ACS_HLINE, ACS_HLINE,
            ACS_ULCORNER, ACS_URCORNER,
            ACS_LLCORNER, ACS_LRCORNER);
    wattroff(pauseWin, COLOR_PAIR(2));
    wrefresh(pauseWin);
  }

private:
  WINDOW *pauseWin;
  int boardW;
  const int rows = 12;
  const int cols = 22;
  int start_y = 5;

  static const int NUM_OPTIONS = 3;
  const char *options[NUM_OPTIONS] = {"Continue", "Change level", "Exit"};

  void createWindow(int h, int w)
  {
    int boardRows, boardCols;
    getmaxyx(stdscr, boardRows, boardCols);
    int boardStartY = (boardRows / 2) - (h / 2);
    int boardStartX = (boardCols / 2) - (boardW / 2);

    int pauseStartY = boardStartY;
    int pauseStartX = boardStartX + boardW + 1;

    pauseWin = newwin(rows, cols, pauseStartY, pauseStartX);
    keypad(pauseWin, TRUE);
    wtimeout(pauseWin, 10);
  }
};