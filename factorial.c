/*
  Factorial(階乘) program
*/
#include <stdio.h>

unsigned long factorial(unsigned int);

int main()
{
  unsigned int number;
  long fact = 1;

  printf("Enter a number to calculate it's factorial\n");
  scanf("%u", &number);

  printf("%d! = %u\n", number, factorial(number));

  return 0;
}

unsigned long factorial(unsigned int n)
{
  unsigned int c;
  unsigned long result = 1;

  for (c = 1; c <= n; c++)
    result = result * c;

  return result;
}