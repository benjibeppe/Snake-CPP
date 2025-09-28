#pragma once
#include <ncurses.h>
#include "Drawable.hpp"
#include "Time.hpp"
#include <stdlib.h>

class Board
{
public:
  Board(int h, int w, int snakeSpeed)
  {
    defaultConstructor(h, w, snakeSpeed);
  }

  Board()
  {
    defaultConstructor(20, 45, 200); // Default size if not specified
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
    time_t timeLastInput = Time::milliseconds();

    int input = wgetch(boardWin);
    int newInput = ERR;

    setTimeout(0);
    while (timeLastInput + snakeSpeed >= Time::milliseconds())
    {
      newInput = wgetch(boardWin);
    }

    if (newInput != ERR)
    {
      input = newInput;
    }

    setTimeout(snakeSpeed);
    return input;
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

  int getTimeout()
  {
    return snakeSpeed;
  }

  int getRows() { return rows; }
  int getCols() { return cols; }

  int getStartY() { return (rows / 2) - (rows / 2); }
  int getStartX()
  {
    return (cols / 2) - (cols / 2);
  }

private:
  WINDOW *boardWin;
  int rows, cols;
  int snakeSpeed;

  void defaultConstructor(int h, int w, int snakeSpeed)
  {
    createWindow(h, w);
    rows = h;
    cols = w;
    this->snakeSpeed = snakeSpeed;
    setTimeout(snakeSpeed);
    drawBorder();
  }
};