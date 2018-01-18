
#include <stdio.h>
#include <math.h>

/* -- Macro Definitions */

#ifdef _DEBUG
#define DEBUG_PRINT(x)    printf x
#else
#define DEBUG_PRINT(x)
#endif /* DEBUG */


// #ifdef DDEBUG
// #define DEBUG_PRINT(fmt, args...)    fprintf(stderr, fmt, ## args)
// #else
// #define DEBUG_PRINT(fmt, args...)    /* Don't do anything in release builds */
// #endif

int isPrime (unsigned long p)
{
    if(p%2 ==0)return 0;  // 測試是否為偶數
    unsigned long x_sqrt = (unsigned long)sqrt((double)p);
    for(unsigned long i=3;i<=x_sqrt;i+=2){
      if( p%i == 0 )return 0; // 可以整除，非質數
    }
    DEBUG_PRINT ( ("%lu is a prime number.\n",p) );
    return 1;
}

