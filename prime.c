#include <stdio.h>
#include <stdlib.h>
#include "debug.h"

int isPrime (unsigned long n)
{
      unsigned long c = 2;
      for ( ; c <= n - 1 ; c++ )
      {
         if ( n%c == 0 )
            return 0;		// test n start from 2
      }
      DEBUG_PRINT (("%u is a prime.\n",n));
      return 1;
}


