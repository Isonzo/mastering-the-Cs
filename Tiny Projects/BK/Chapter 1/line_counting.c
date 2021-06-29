#include <stdio.h>

// Count lines as input

int main()
{
  int c, nl, tb, bl;

  nl = 0;
  while((c = getchar()) != EOF)
  {
    if (c == '\n' || c == ' ' || c == '\t')
    {
      ++nl;
    }
  }
  printf("%d, %d, %d\n", nl, tb, bl);
}
