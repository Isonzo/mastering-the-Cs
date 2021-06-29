#include <stdio.h>
#include <unistd.h>

int main(){

  int answer;

  printf("Who wants to be a Millionaire?\n\n");
  printf("Alright bud, what is the title of an Ethiopian king?\n");
  printf("1. King\n2. Negus\n3. Pharaoh\n4. Wáng\n");
  scanf("%d", &answer);

  if(answer != 2){
    printf("Ooh, sorry mate, that's incorrect.\n");
    return 0;
  }else{
    printf("Alright! Don't get your hopes up though, there's more to come!\n");
  }

  printf("Alright guy, according to Purdue University, how many licks to reach\n the center of a Tootsie Pop?\n");
  printf("1. 6 bites\n2. 241 licks\n3. 364 licks\n4. More than 450\n");
  scanf("%d", &answer);

  if(answer != 3){
    printf("Ooh, sorry mate, that's incorrect.\n");
    return 0;
  }else{
    printf("Alright, two in a row! Keep that up and you might make it big\n");
  }

    printf("Alright pal, how many litres of blood does a typical human have?\n");
    printf("1. 4-6\n2. 8-9\n3. 2-3\n4. None of the above\n");
    scanf("%d", &answer);

    if(answer != 1){
      printf("Ooh, sorry mate, that's incorrect.\n");
      return 0;
    }else{
      printf("Wow! you're a natural! you might even become one of the \n12 million millionaire households!\n");
  }

  printf("Alright buddy, final question. What number am I thinking of??\n");
  printf("type your answer here: ");
  scanf("%d", &answer);

  if(answer != 5){
    printf("Ooh, sorry mate, that's incorrect. And you were so close!\n");
    return 0;
  }else{
    printf("Huh, you actually won, huh? Of course you can collect you winnings\nI... just need to make a call. I swear I'll be back!\n");
    sleep(5);
    printf("(He might not be coming back)");
    return 0;
  }
}
