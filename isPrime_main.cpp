/*
Summary: Check whether a number is prime or not
*/

#include <stdio.h>
#include <time.h>
int isPrime(unsigned long);

int main()
{
  unsigned long n;
  int flag = 0;
  clock_t begin, end;
  double time_spent;

  printf("Enter a positive integer: ");
  scanf("%ld", &n);

  begin = clock(); /* here, do your time-consuming job */
  flag = isPrime(n);
  end = clock();
  time_spent = (double)(end - begin) / (CLOCKS_PER_SEC / 1000.0);
  printf("cosuming %f milliseconds.\n", time_spent);

  if (flag == 1)
    printf("%lu is a prime number.\n", n);
  else
    printf("%lu is not a prime number.\n", n);

  return 0;
}

/*
Input: Enter a positive integer: 29
*/
