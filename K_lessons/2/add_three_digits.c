int CalculateThreeDigits(int a, int b, int c)
{
  return a + b + c;
}

void ThrowAwayValue(int garbage)
{
  int trashcan = 0;
  garbage *= trashcan;
}

int main(void)
{
  int p = CalculateThreeDigits(1, 2, 5);
  int q = p * 2;
  ThrowAwayValue(q);
}
