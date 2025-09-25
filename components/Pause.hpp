#pragma once
#include <ncurses.h>

class Pause
{

public:
  Pause(int boardH, int boardW)
  {
    int pauseH = boardH;
    int pauseW = boardW / 2;
    createWindow(pauseH, pauseW);
  }

  void createWindow(int h, int w)
  {
    getmaxyx(stdscr, rows, cols);
    int starty = (rows / 2) - (h / 2);
    int startx = (cols / 2) - (w / 2) + 5;
    pauseWin = newwin(h, w, starty, startx);
    keypad(pauseWin, TRUE);
  }

  void
  drawBorder()
  {
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
  int rows, cols;
};