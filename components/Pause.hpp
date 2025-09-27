#pragma once
#include <ncurses.h>

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

  void createWindow(int h, int w)
  {
    int boardRows, boardCols;
    getmaxyx(stdscr, boardRows, boardCols);
    int boardStartY = (boardRows / 2) - (h / 2);
    int boardStartX = (boardCols / 2) - (boardW / 2);

    int pauseStartY = boardStartY;
    int pauseStartX = boardStartX + boardW + 1;

    pauseWin = newwin(h, w, pauseStartY, pauseStartX);
    keypad(pauseWin, TRUE);
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
  int rows, cols;
  int boardW;
};