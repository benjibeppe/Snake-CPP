#pragma once
#include <ncurses.h>
#include <string.h>
#include <string>
using namespace std;

struct Levels
{
  int level;
  int speed;
  int scoreToWin;
  int time;
  struct Levels *nextLevel;
  struct Levels *prevLevel;
};

class ChangeLevel
{
private:
  Levels *head;
  Levels *current;
  WINDOW *levelWin;
  int boardH, boardW;
  static const int NUM_LEVELS = 5;
  const char *levelNames[NUM_LEVELS] = {"Easy", "Medium", "Hard", "Expert", "Godlike"};

public:
  // Costruttore che posiziona la finestra a sinistra della board
  ChangeLevel(int boardH, int boardW)
  {
    this->boardH = boardH;
    this->boardW = boardW;
    head = nullptr;
    current = nullptr;
    levelWin = nullptr;

    initializeLevels();
    createWindow();
    drawBorder();
  }

  ~ChangeLevel()
  {
    if (levelWin)
    {
      werase(levelWin);
      wrefresh(levelWin);
      delwin(levelWin);
      levelWin = nullptr;
    }
    clearLevels();
  }

  int showLevelSelection()
  {
    int highlight = current ? current->level - 1 : 0;
    int choice = -1;
    int c;

    while (choice == -1)
    {
      werase(levelWin);
      drawBorder();

      // Titolo
      const char *title = "SELECT LEVEL";
      int title_x = (22 - strlen(title)) / 2;
      wattron(levelWin, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);
      mvwprintw(levelWin, 2, title_x, "%s", title);
      wattroff(levelWin, COLOR_PAIR(2) | A_BOLD | A_UNDERLINE);

      // Lista dei livelli
      Levels *temp = head;
      int y = 5;
      for (int i = 0; i < NUM_LEVELS && temp; i++, temp = temp->nextLevel)
      {
        if (i == highlight)
        {
          // Livello selezionato
          wattron(levelWin, COLOR_PAIR(1) | A_BOLD);
          mvwprintw(levelWin, y, 2, "> Level %d <%s", temp->level, "");
          mvwprintw(levelWin, y + 1, 3, "%s", levelNames[i]);
          mvwprintw(levelWin, y + 2, 3, "Speed: %dms", temp->speed);
          mvwprintw(levelWin, y + 3, 3, "Score: %d", temp->scoreToWin);
          wattroff(levelWin, COLOR_PAIR(1) | A_BOLD);
          y += 5;
        }
        else
        {
          // Livello non selezionato
          wattron(levelWin, COLOR_PAIR(3));
          mvwprintw(levelWin, y, 3, "Level %d - %s", temp->level, levelNames[i]);
          wattroff(levelWin, COLOR_PAIR(3));
          y += 2;
        }
      }

      c = wgetch(levelWin);
      switch (c)
      {
      case KEY_UP:
        highlight = (highlight - 1 + NUM_LEVELS) % NUM_LEVELS;
        break;
      case KEY_DOWN:
        highlight = (highlight + 1) % NUM_LEVELS;
        break;
      case 10: // ENTER
        choice = highlight;
        setCurrentLevel(highlight + 1);
        break;
      case 27: // ESC
        choice = -1;
        return -1;
      }
    }

    werase(levelWin);
    wrefresh(levelWin);
    return choice;
  }

  // Imposta il livello corrente (metodo pubblico)
  bool setCurrentLevel(int levelNumber)
  {
    Levels *temp = head;
    while (temp)
    {
      if (temp->level == levelNumber)
      {
        current = temp;
        return true;
      }
      temp = temp->nextLevel;
    }
    return false;
  }

private:
  // Inizializza i 5 livelli predefiniti
  void initializeLevels()
  {
    // Livello 1: Facile
    addLevel(1, 200, 100, 60);
    // Livello 2: Medio
    addLevel(2, 150, 200, 45);
    // Livello 3: Difficile
    addLevel(3, 100, 300, 30);
    // Livello 4: Esperto
    addLevel(4, 75, 500, 20);
    // Livello 5: Estremo
    addLevel(5, 50, 1000, 15);

    current = head; // Inizia dal primo livello
  }

  // Aggiunge un livello alla lista bidirezionale
  void addLevel(int level, int speed, int scoreToWin, int time)
  {
    Levels *newLevel = new Levels;
    newLevel->level = level;
    newLevel->speed = speed;
    newLevel->scoreToWin = scoreToWin;
    newLevel->time = time;
    newLevel->nextLevel = nullptr;
    newLevel->prevLevel = nullptr;

    if (head == nullptr)
    {
      head = newLevel;
    }
    else
    {
      Levels *temp = head;
      while (temp->nextLevel)
        temp = temp->nextLevel;

      temp->nextLevel = newLevel;
      newLevel->prevLevel = temp;
    }
  }

  // Crea la finestra a sinistra della board
  void createWindow()
  {
    int termRows, termCols;
    getmaxyx(stdscr, termRows, termCols);

    int boardStartY = (termRows / 2) - (boardH / 2);
    int boardStartX = (termCols / 2) - (boardW / 2);

    int levelStartY = boardStartY;
    int levelStartX = boardStartX - 23; // Posiziona a sinistra della board

    levelWin = newwin(boardH, 22, levelStartY, levelStartX);
    keypad(levelWin, TRUE);
    wtimeout(levelWin, 10);
  }

  // Disegna il bordo con lo stesso stile di Pause e Score
  void drawBorder()
  {
    if (!levelWin)
      return;

    wattron(levelWin, COLOR_PAIR(2));
    wborder(levelWin,
            ACS_VLINE, ACS_VLINE,
            ACS_HLINE, ACS_HLINE,
            ACS_ULCORNER, ACS_URCORNER,
            ACS_LLCORNER, ACS_LRCORNER);
    wattroff(levelWin, COLOR_PAIR(2));
    wrefresh(levelWin);
  }

  // Pulisce tutti i livelli
  void clearLevels()
  {
    while (head)
    {
      Levels *temp = head;
      head = head->nextLevel;
      delete temp;
    }
    head = current = nullptr;
  }
};