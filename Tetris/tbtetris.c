#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

const int WIDTH = 15;
const int HEIGHT = 23;

char symbol = '@';

char screen[23][15];
void generatescreen()
{
  int i;
  int j;
  for(i = 0; i <= HEIGHT - 1; ++i)
  {
    for(j = 0; j <= WIDTH - 1; ++j)
    {
      if(j == 0 || j == WIDTH - 1)
      {
        screen[i][j] = '#';
      }else if (i == HEIGHT - 1)
      {
        screen[i][j] = '#';
      }else
      {
        screen[i][j] = ' ';
      }
    }
  }
}

void updatescreen()
{
  int i;
  int j;
  for(i = 0; i < HEIGHT; ++i)
  {
    for(j = 0; j < WIDTH; ++j)
    {
      printf("%c", screen[i][j]);
    }
  printf("\n");
  }
}

int randomint()
{
  int randomnumber; // I think this is skewed, something to review
  randomnumber = rand() % 8;
  return randomnumber;
}

void spawnpiece()
{
  //screen[0][WIDTH / 2] = symbol; A single dot, just for testing
  // Randomly choose a piece to spawn

  switch (randomint())
  {
    case 0:
      // Hero
      screen[0][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2] = symbol;
      screen[2][WIDTH / 2] = symbol;
      screen[3][WIDTH / 2] = symbol;
      break;

    case 1:
      // Orange Ricky
      screen[0][WIDTH / 2 - 1] = symbol;
      screen[0][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2] = symbol;
      screen[2][WIDTH / 2] = symbol;
      break;

    case 2:
      // Blue Ricky
      screen[0][WIDTH / 2 + 1] = symbol;
      screen[0][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2] = symbol;
      screen[2][WIDTH / 2] = symbol;
      break;

    case 3:
    // Blue Ricky
      screen[0][WIDTH / 2 + 1] = symbol;
      screen[0][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2] = symbol;
      screen[2][WIDTH / 2] = symbol;
      break;

    case 4:
      // Cleveland Z
      screen[0][WIDTH / 2 - 1] = symbol;
      screen[0][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2 + 1] = symbol;
      break;

    case 5:
      // Rhode Z
      screen[0][WIDTH / 2 + 1] = symbol;
      screen[0][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2 - 1] = symbol;
      break;

    case 6:
      // Teewee
      screen[0][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2 - 1] = symbol;
      screen[1][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2 + 1] = symbol;
      break;

    case 7:
      // Smashboy
      screen[0][WIDTH / 2 + 1] = symbol;
      screen[0][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2] = symbol;
      screen[1][WIDTH / 2 + 1] = symbol;
      break;
  }
}



void physics(char dir)
{
  int i;
  int j;
  int change = 0;
  int physics = 1;
  if (dir == 'd' || dir == 's')
  {
    for(i = HEIGHT - 1; i >=  0; --i)
    {
      for(j = WIDTH - 1; j >= 0; --j)
      { //If space directly below is not a space, don't move that piece
        if (screen[i][j] == symbol && screen[i + 1][j] == ' ' && physics)
        {
          screen[i][j] = ' ';
          if (dir == 'a' && screen[i + 1][j - 1] == ' ')
          {
            screen[i + 1][j - 1] = symbol;
          }else if (dir == 'd' && screen[i + 1][j + 1] == ' ')
          {
            screen[i + 1][j + 1] = symbol;
          }else if (dir == 's' && screen[i + 2][j] == ' ')
          {
            screen[i + 2][j] = symbol;
          }else
          {
            screen[i + 1][j] =symbol;
          }
          // Mark down that physics DID happen
          change += 1;
        }
      }
    }
    if (!change)
    {
      for(i = 0; i <= HEIGHT - 1; ++i)
      {
        for(j = 0; j <= WIDTH - 1; ++j)
        {
          if(screen[i][j] == '@')
          {
            screen[i][j] = '&';
          } 
        }
      }
      spawnpiece();
    }
  }
  if (dir == 'a')
  {
    for(i = HEIGHT - 1; i >=  0; --i)
    {
      for(j = 0; j <= WIDTH - 1; ++j)
      { //If space directly below is not a space, don't move that piece
        if (screen[i][j] == symbol && screen[i + 1][j] == ' ')
        {
          screen[i][j] = ' ';
          if (dir == 'a' && screen[i + 1][j - 1] == ' ')
          {
            screen[i + 1][j - 1] = symbol;
          }else if (dir == 'd' && screen[i + 1][j + 1] == ' ')
          {
            screen[i + 1][j + 1] = symbol;
          }else if (dir == 's' && screen[i + 2][j] == ' ')
          {
            screen[i + 2][j] = symbol;
          }else
          {
            screen[i + 1][j] = symbol;
          }
          // Mark down that physics DID happen
          change += 1;
          {
            //Ensure for @s have moved, else the tetrino has collided
            if(change == 5)
            {

            }
          }
        }
      }
    }
    if (!change)
    {
      spawnpiece();
    }
  }
}

int main()
{
  char dir;
  generatescreen();
  spawnpiece();
  updatescreen();
  while (1)
  {
    scanf("%c", &dir);
    physics(dir);
    updatescreen();
  }
  return 0;
}
