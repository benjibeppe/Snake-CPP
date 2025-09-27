#pragma once
#include <ncurses.h>
#include <string>
#include <string.h>
using namespace std;

class Score
{
public:
  Score()
  {
    scoreWin = nullptr;
    score = 0;
  }

  Score(int boardH, int boardW, int pauseH, int pauseW)
  {
    score = 0;
    int scoreH = boardH - pauseH - 1;
    int scoreW = pauseW;

    int termRows, termCols;
    getmaxyx(stdscr, termRows, termCols);
    int boardStartY = (termRows / 2) - (boardH / 2);
    int boardStartX = (termCols / 2) - (boardW / 2);

    int scoreStartY = boardStartY + pauseH + 1;
    int scoreStartX = boardStartX + boardW + 1;

    scoreWin = newwin(scoreH, scoreW, scoreStartY, scoreStartX);
    drawBorder();
    render();
  }

  ~Score()
  {
    if (scoreWin)
    {
      werase(scoreWin);
      wrefresh(scoreWin);
      delwin(scoreWin);
      scoreWin = nullptr;
    }
  }

  void setScore(int value)
  {
    score = value;
    render();
  }

  void render()
  {
    if (!scoreWin)
      return;
    werase(scoreWin);
    drawBorder();

    const char *title = "SCORE";
    int title_x = (getmaxx(scoreWin) - strlen(title)) / 2;
    wattron(scoreWin, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);
    mvwprintw(scoreWin, 2, title_x, "%s", title);
    wattroff(scoreWin, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);

    std::string scoreStr = std::to_string(score);
    int score_x = (getmaxx(scoreWin) - scoreStr.size()) / 2;
    wattron(scoreWin, COLOR_PAIR(1) | A_BOLD);
    mvwprintw(scoreWin, 4, score_x, "%s", scoreStr.c_str());
    wattroff(scoreWin, COLOR_PAIR(1) | A_BOLD);

    wrefresh(scoreWin);
  }

private:
  WINDOW *scoreWin;
  int score;

  void drawBorder()
  {
    if (!scoreWin)
      return;
    wattron(scoreWin, COLOR_PAIR(2));
    wborder(scoreWin,
            ACS_VLINE, ACS_VLINE,
            ACS_HLINE, ACS_HLINE,
            ACS_ULCORNER, ACS_URCORNER,
            ACS_LLCORNER, ACS_LRCORNER);
    wattroff(scoreWin, COLOR_PAIR(2));
    wrefresh(scoreWin);
  }
};