#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
#include <time.h>
#include <stdlib.h>

class Board
{
public:
  int snakeSpeed = 200;

  Board(int h, int w)
  {
    defaultConstructor(h, w);
  }

  Board()
  {
    defaultConstructor(20, 45); // Default size if not specified
  }

  void createWindow(int h, int w)
  {
    getmaxyx(stdscr, rows, cols);
    boardWin = newwin(h, w, (rows / 2) - (h / 2), (cols / 2) - (w / 2));
    keypad(boardWin, TRUE);
  }

  void clear()
  {
    werase(boardWin);
    box(boardWin, 0, 0);
    wrefresh(boardWin);
  }

  void clearCell(int y, int x)
  {
    wattrset(boardWin, A_NORMAL);
    wcolor_set(boardWin, 0, NULL);
    mvwaddch(boardWin, y, x, ' ' | A_NORMAL);
  }

  void drawBorder()
  {
    wattron(boardWin, COLOR_PAIR(3));
    wborder(boardWin,
            ACS_VLINE, ACS_VLINE,
            ACS_HLINE, ACS_HLINE,
            ACS_ULCORNER, ACS_URCORNER,
            ACS_LLCORNER, ACS_LRCORNER);
    wattroff(boardWin, COLOR_PAIR(3));
    wrefresh(boardWin);
  }

  void redrawBoard()
  {
    werase(boardWin);
    drawBorder();
  }

  int getInput()
  {
    return wgetch(boardWin);
  }

  int getCharAt(int y, int x)
  {
    return mvwinch(boardWin, y, x);
  }

  void getEmptyCoordinates(int &y, int &x)
  {
    do
    {
      y = rand() % rows;
      x = rand() % cols;
    } while (mvwinch(boardWin, y, x) != ' ');
  }

  void addChar(int y, int x, char ch)
  {
    mvwaddch(boardWin, y, x, ch | A_NORMAL);
    wrefresh(boardWin);
  }

  void add(Drawable drawable)
  {
    if (drawable.getColor() != 0)
    {
      wattron(boardWin, COLOR_PAIR(drawable.getColor()));
      mvwaddch(boardWin, drawable.getY(), drawable.getX(), drawable.getRepresentation());
      wattroff(boardWin, COLOR_PAIR(drawable.getColor()));
    }
    else
    {
      mvwaddch(boardWin, drawable.getY(), drawable.getX(), drawable.getRepresentation() | A_NORMAL);
    }
    wrefresh(boardWin);
  }

  void refresh()
  {
    wrefresh(boardWin);
  }

  void setTimeout(int ms)
  {
    wtimeout(boardWin, ms);
  }

private:
  WINDOW *boardWin;
  int rows, cols;

  void defaultConstructor(int h, int w)
  {
    createWindow(h, w);
    this->rows = rows;
    this->cols = cols;
    drawBorder();

    wtimeout(boardWin, snakeSpeed);
  }
};