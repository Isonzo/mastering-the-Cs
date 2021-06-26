#include <ncurses.h>
#include <stdlib.h>
#include <time.h>


typedef struct Position
{
  int x;
  int y;
}Position;

typedef struct Room
{
  // Top left corner of room
  Position position;

  int height;
  int width;

  Position doors[4];
  //Monster ** monsters;
  //Item ** items;
}Room;

typedef struct Player
{
  Position position;

  int health;
}Player;

void screenSetUp();
Room ** mapSetUp();
Room * createRoom(int y, int x, int height, int width);
void drawRoom(Room * room);
Player * playerSetUp();
void handleInput(char input, Player * user);
void playerMove();
void checkPosition();


Player * playerSetUp();

int main()
{
  Player * user;
  Room ** rooms;
  char ch;
  screenSetUp();
  rooms = mapSetUp();
  user = playerSetUp();


  while((ch = getch()) != 'q')
  {
    handleInput(ch, user);
  }
  free(user);
  free(rooms);

  endwin();
  return 0;
}

void screenSetUp()
{
  initscr();
  printw("Curses looking good!");
  noecho();
  refresh();

}

Room ** mapSetUp()
{
  Room ** rooms;
  rooms = malloc(sizeof(Room) * 6);
  rooms[0] = createRoom(13, 13, 6, 8);
  rooms[1] = createRoom(5, 23, 7, 5);

  drawRoom(rooms[0]);
  drawRoom(rooms[1]);

  return rooms;
}

Room * createRoom(int y, int x, int height, int width)
{
  Room * new_room;
  new_room = malloc(sizeof(new_room));

  new_room->position.y = y;
  new_room->position.x = x;
  new_room->height = height;
  new_room->width = width;

  srand(time(NULL));


  // Top Door
  new_room->doors[0].x = rand() % width + new_room->position.x;
  new_room->doors[0].y = new_room->position.y;

  // Bottom
  new_room->doors[1].x = rand() % width + new_room->position.x;
  new_room->doors[1].y = new_room->position.y + height;

  // Left
  new_room->doors[2].x = rand() % height + new_room->position.y;
  new_room->doors[2].y = new_room->position.x;

  // Right
  new_room->doors[3].x = rand() % height + new_room->position.y;
  new_room->doors[3].y = new_room->position.x + width;
}

void drawRoom(Room * room)
{
  int x;
  int y;

  // Draw top and bottom
  for (x = room->position.x; x < room->position.x + room->width; x++)
  {
    mvprintw(room->position.y, x, "-");
    mvprintw(room->position.y + room->height - 1, x, "-");
  }

  // Floor and sides
  for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
  {
    // Sides
    mvprintw(y, room->position.x, "|");
    mvprintw(y, room->position.x + room->width - 1, "|");

    // Floors
    for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
    {
      mvprintw(y, x, ".");
    }
  }
  // Doors
  mvprintw(room->doors[0].y, room->doors[0].x, "+");
  mvprintw(room->doors[1].y, room->doors[1].x, "+");
  mvprintw(room->doors[2].y, room->doors[2].x, "+");
  mvprintw(room->doors[3].y, room->doors[3].x, "+");
}

Player * playerSetUp()
{
  Player * newPlayer;
  newPlayer = malloc(sizeof(Player));

  newPlayer->position.x = 14;
  newPlayer->position.y = 14;
  newPlayer->health = 5;

  playerMove(14, 14, newPlayer);
  return newPlayer;
}

void handleInput(char input, Player * user)
{
  int new_y;
  int new_x;

  switch (input)
  {
    case 'w':
    case 'W':
      new_y = user->position.y - 1;
      new_x = user->position.x;
      break;

    case 's':
    case 'S':
      new_y = user->position.y + 1;
      new_x = user->position.x;
      break;

    case 'a':
    case 'A':
      new_y = user->position.y;
      new_x = user->position.x - 1;
      break;

    case 'd':
    case 'D':
      new_y = user->position.y;
      new_x = user->position.x + 1;
      break;

    default:
      break;
  }

  checkPosition(new_y, new_x, user);
}

// Checks what the the player is moving into
void checkPosition(int new_y, int new_x, Player * user)
{
  int space;
  switch(mvinch(new_y, new_x)) // mvinch checks char in specific position
  {
    case '.':
      playerMove(new_y, new_x, user);
      break;

    default:
      move(user->position.y, user->position.x); // Making sure cursor stays on player
      break;
  }
}

void playerMove(int y, int x, Player * user)
{
  mvprintw(user->position.y, user->position.x, ".");

  user->position.y = y;
  user->position.x = x;

  mvprintw(user->position.y, user->position.x, "@");
  move(user->position.y, user->position.x);
}
