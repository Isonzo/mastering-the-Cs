#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Position
{
  int x;
  int y;
}Position;

typedef struct Player
{
  Position position;

  int health;
}Player;

Player * playerSetUp();

int main()
{
  playerSetUp();
}

Player * playerSetUp()
{
  Player * new_player;
  

}
