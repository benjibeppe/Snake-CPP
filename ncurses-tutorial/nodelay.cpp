#include <ncurses.h>
#include <iostream>
#include <cstring>
using namespace std;

/*
echo() --> keypresses are displayed in the terminal. Default
noecho() --> keypresses are NOT displayed in the terminal.
nodelay(win, TRUE) --> execution doesn't wait for user to provide an input if user input function called such as getch(), getnstr()
nodelay(win, FALSE) --> default behavior.
clear() --> clears the window.
*/

int main()
{
  initscr(); // Start ncurses mode
  char ch;

  noecho();
  while ((ch = getch()) != '\n')
  {
    printw("You've pressed %c\n", ch);
    refresh();
  }

  echo();
  while ((ch = getch()) != '\n')
  {
    printw("You've pressed %c\n", ch);
    refresh();
  }

  endwin(); // End ncurses mode
  return 0;
}