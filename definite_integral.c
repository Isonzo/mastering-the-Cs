#include <stdio.h>
#include <math.h>

int main(){
  float x, y;
  float rect_width = 0.001;
  float area = 0;
  int upper_limit, lower_limit;

  printf("Enter lower limit and upper limit\n");
  scanf("%d  %d", &lower_limit, &upper_limit);

  for(x=lower_limit; x<=upper_limit; x=x+rect_width){

      y = pow(x, 2) + 1;

      area = area + y*rect_width;
  }

  printf("Area under this curve is: %f\n", area);

  return 0;
}
