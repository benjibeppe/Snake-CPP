#include <ncurses.h>
#include <iostream>
using namespace std;

// has_colors() checks if the terminal supports color true/false
// start_color() initializes color functionality
// initpair(1, foreground color, bkgd color) is used to define color pairs

int main()
{
  initscr(); // Start ncurses mode

  if (!has_colors())
  {
    endwin();
    cout << "Your terminal does not support color." << endl;
    return 1;
  }

  if (start_color() != OK)
  {
    endwin();
    cout << "Failed to initialize colors." << endl;
    return 1;
  }

  init_pair(1, COLOR_RED, COLOR_BLACK);     // Define color pair 1 (red text on black background)
  init_pair(2, COLOR_BLUE, COLOR_YELLOW);   // Define color pair 2 (green text on black background)
  init_pair(3, COLOR_MAGENTA, COLOR_WHITE); // Define color pair 3 (blue text on yellow background)

  // we need to set the background color first cause it overrider the other colors otherwise
  bkgd(COLOR_PAIR(3)); // Set the background color to the third color pair

  attron(COLOR_PAIR(1) | A_BOLD); // Turn on color pair 1
  addstr("This is a red text!");

  attron(COLOR_PAIR(2) | A_BLINK); // Turn on color pair 2
  addstr("\nThis is a blue text!\n");
  attroff(COLOR_PAIR(2) | A_BLINK | A_BOLD); // Turn off color pair 2

  printw("%d colors are available.\n", COLORS);
  printw("Color pairs available: %d\n", COLOR_PAIRS);

  refresh(); // Refresh the screen to show the text

  getch(); // Wait for user input

  endwin(); // End ncurses mode
  return 0;
}