#include <stdio.h>
int main(){
  int num;
  printf("Enter amount of shekels: ");
  scanf("%d", &num);

  if(num > 0){
    printf("You have too many shekels! The state shall be seizing that...");
    num = 0;
  }else{
    printf("Alright, you can keep what you've got... for now.");
  }

  printf("\nHere's what's left of your wealth: %d", num);
  return 0;
}
