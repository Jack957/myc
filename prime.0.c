#include <stdio.h>
#include <time.h>
 
int main(void)
{
   int n, i = 3, count, c;
 
   printf("Enter the number of prime numbers required\n");
   scanf("%d",&n);
   
   clock_t begin = clock();
   
   if ( n >= 1 )
   {
      printf("First %d prime numbers are :\n",n);
      printf("2 ");
   }
 
   for ( count = 2 ; count <= n ;  )
   {
      for ( c = 2 ; c <= i - 1 ; c++ )
      {
         if ( i%c == 0 )  
            break;		// divide i start from 2
      }
      if ( c == i )
      {
         printf("%d ",i);
	 if(count %10 == 0) printf("\n");
         count++;
      }
      i++; // i is the number for test
   }
   
   if(count % 10 != 9) printf("\n"); 
   
   clock_t end = clock();
   double mstime_consume = (end - begin)/(CLOCKS_PER_SEC/1000.0);
   printf("consuming %f millisec.\n",mstime_consume);
   return 0;
}
