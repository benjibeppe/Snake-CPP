#include <ncurses.h>
#include <iostream>
using namespace std;

int main()
{
  initscr(); // Start ncurses mode

  addstr("Hello how are you doing?\n");
  attron(A_BOLD); // Set text attribute to bold
  addstr("Hello how are you doing?\n");
  attron(A_UNDERLINE); // Set text attribute to underline
  attroff(A_BOLD);     // Turn off bold attribute
  addstr("Hello how are you doing?\n");
  attroff(A_UNDERLINE);         // Turn off underline attribute
  attron(A_BOLD | A_UNDERLINE); // Set both bold and underline attributes
  addstr("Hello how are you doing?\n");
  refresh();

  getch(); // Wait for user input

  endwin(); // End ncurses mode
  return 0;
}