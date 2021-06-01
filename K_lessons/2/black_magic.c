int main(void){
  float myFloat = 2.0f;
  float* myFloatPtr = &myFloat; //& operator takes the address of what you pass it, think of it as the opposite of *
  int* myIntPtr = (int*)myFloatPtr; //I think this is undefined behavior by the way, but it's fun
  printf("%d", *myIntPtr);
}
