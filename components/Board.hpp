#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
#include <time.h>
#include <stdlib.h>

class Board
{
public:
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
  }

  void clear()
  {
    werase(boardWin);
    box(boardWin, 0, 0);
    wrefresh(boardWin);
  }

  void drawBorder()
  {
    box(boardWin, 0, 0);
    wrefresh(boardWin);
  }

  void redrawBoard()
  {
    clear();
    drawBorder();
  }

  char getInput()
  {
    return wgetch(boardWin);
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
    mvwaddch(boardWin, y, x, ch);
    wrefresh(boardWin);
  }

  void add(Drawable drawable)
  {
    addChar(drawable.getY(), drawable.getX(), drawable.getRepresentation());
  }

  void refresh()
  {
    wrefresh(boardWin);
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
  }
};