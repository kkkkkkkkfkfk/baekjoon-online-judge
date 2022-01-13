#include <stdio.h>
int Ezreal[1516];

int main(void)
{
  int N;
  scanf("%d", &N);

  for(int i = 2; i <= N; i++)
  {
    if(i % 2 == 0)
    {
      Ezreal[i] = Ezreal[i - 1] * 2 + 1;
      Ezreal[i] %= 1000000007;
    }
    else
    {
      Ezreal[i] = Ezreal[i - 1] * 2 - 1;
      Ezreal[i] %= 1000000007;
    }
  }

  printf("%d\n", Ezreal[N]);

  return 0;
}