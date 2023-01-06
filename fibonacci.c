#include <stdio.h>
#include <time.h> /* clock() */
/*
      using recursion to generate a list of Fibonacci Series numbers
*/

unsigned long Fibonacci(unsigned long);

int main(int argc, char *argv[])
{
   int n, i = 0, c;
   clock_t begin, end;
   double mstime_consume;

   if (argc > 1)
   {
      n = atoi(argv[1]);
   }
   else
   {
      printf("How many Fibonacci series numbers would you like to generate?\n");
      scanf("%d", &n);
   }

   if (n > 0)
      printf("to generate %d Fibonacci series numbers.\n", n);
   else
      return -1;

   // printf("Fibonacci series\n");
   printf("%5c ", ' ');
   for (c = 1; c <= 5; c++)
      printf("%11u", c);
   printf("\n");

   begin = clock();
   for (c = 1; c <= n; c++)
   {
      if (c % 5 == 1)
         printf("%5d:", c);
      printf("%11u", Fibonacci(c));
      if (c % 5 == 0)
         printf("\n");
      i++;
   }
   end = clock();
   printf("\n");

   mstime_consume = (end - begin) / (CLOCKS_PER_SEC / 1000.0);
   printf("consuming %f millisec.\n", mstime_consume);

   return 0;
}

unsigned long Fibonacci(unsigned long n)
{
   if (n == 0)
      return 0;
   else if (n == 1)
      return 1;
   else
      return (Fibonacci(n - 1) + Fibonacci(n - 2));
}
