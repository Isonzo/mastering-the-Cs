#include <stdio.h>

int main()
{
  int a, b, z;

  scanf("%d", &a);
  scanf("%d", &b);

  // Normal way to write it
  if (a > b)
    z = a;
  else
    z = b;
  printf("z is %d", z);
  // Another way to write it
  z = (a > b) ? a : b;  // condition ? if_true : else
  printf("z is %d here too", z);
}
