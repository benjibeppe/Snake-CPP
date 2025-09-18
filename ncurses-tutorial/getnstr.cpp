#include <ncurses.h>
#include <iostream>
using namespace std;

int main()
{
  initscr(); // Start ncurses mode

  char firstName[50];
  char lastName[50];

  addstr("Enter your first name: ");
  refresh();
  getnstr(firstName, sizeof(firstName) - 1);

  addstr("Enter your last name: ");
  refresh();
  getnstr(lastName, sizeof(lastName) - 1);

  printw("Hello, %s %s!\n", firstName, lastName);

  getch();  // Wait for user input before exiting
  endwin(); // End ncurses mode
  return 0;
}