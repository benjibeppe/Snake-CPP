#include <ncurses.h>
#include <iostream>
#include <cstring>
using namespace std;

// getyx(win, row, col) --> current cursor position
// move(row, col) --> move the cursor to desired position
// getmaxyx(win, row, col) --> terminal screen size

void printCursorPosition()
{
  int row, col;
  getyx(stdscr, row, col); // Get current cursor position
  printw("Current cursor position: (%d, %d)\n", row, col);
  refresh(); // Refresh the screen to show changes
}

int main()
{
  initscr(); // Start ncurses mode

  int row, col;
  printCursorPosition(); // Print initial cursor position
  printCursorPosition(); // Print again to show it hasn't changed
  refresh();             // Refresh the screen to show changes

  move(5, 10);           // Move cursor to row 5, column 10
  printCursorPosition(); // Print new cursor position
  refresh();             // Refresh the screen to show changes

  char text[] = "Hello, World!";
  int len = strlen(text);
  getmaxyx(stdscr, row, col);                         // Get terminal size
  int cursor_middle_position = (col) / 2 - (len / 2); // orizzontal center
  move((row / 2) - 1, cursor_middle_position);        // Move cursor to the middle of row 10
  printw("%s", text);                                 // Print text at the new cursor position
  refresh();                                          // Refresh the screen to show changes

  getch(); // Wait for user input

  endwin(); // End ncurses mode
  return 0;
}