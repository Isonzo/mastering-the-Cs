#ifndef ROGUE_H
#define ROGUE_H

#ifdef _LINUX
#include <ncurses.h>
#elif _WIN32
#include <curses.h>
#endif
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int y;
    int x;
} Position;

typedef struct
{
    char ch;
    bool walkable;
} Tile;

typedef struct
{
    Position pos;
    char ch;
}Entity;

// draw.c functions
void drawMap(void);
void drawEntity(Entity* entity);
void drawEverything(void);

// engine.c functions
void cursesSetup(void);
void gameLoop(void);
void closeGame(void);

// map.c functions
Tile** createMapTiles(void);
void freeMap(void);

// player.c functions
Entity* createPlayer(Position start_pos);
void handleInput(int input);

// externs
extern const int MAP_HEIGHT;
extern const int MAP_WIDTH;
extern Entity* player;
extern Tile** map;


#endif