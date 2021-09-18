#ifndef ROGUE_H
#define ROGUE_H

#ifdef _LINUX
#include <ncurses.h>
#elif _WIN32
#include <curses.h>
#endif
#include <stdlib.h>

typedef struct
{
    int y;
    int x;
} Position;

typedef struct
{
    Position pos;
    char ch;
}Entity;

//engine.c functions
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);


// player.c functions
Entity* createPlayer(Position start_pos);
void handleInput(int input);

// externs
extern Entity* player;


#endif