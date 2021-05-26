#include <stdio.h>

int fibonacci_finder(num){
  int n1 = 0;
  int n2 = 1;
  int n3;
  int i;

  if(num == 2){
    return 1;
  }else if(num == 1){
    return 0;
  }

  //Offset the initial i due to already having taken care of the first two values
  for(i = 2; i < num; ++i){
    n3 = n1 + n2;
    n1 = n2;
    n2 = n3;
  }
  return n3;
}

int main(){
  int n;
  int answer;

  scanf("%d",&n);

  answer = fibonacci_finder(n);

  printf("The value #%d of the fibonacci sequence is %d", n, answer);


}
