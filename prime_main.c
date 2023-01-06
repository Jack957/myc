/* 
2023-01-06 resolve potential uninitialized primeArray error
*/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

extern int isPrime(unsigned long);

int main(int agc, char** argv)
{
	unsigned int n, i = 3, count;
	unsigned int* primeArray;
	clock_t begin, end;
	double mstime_consume;

	printf("Enter the number of prime numbers required\n");
	scanf_s("%u", &n);

	begin = clock();

	if (n >= 1)
	{
		primeArray = (unsigned int*)malloc(sizeof(unsigned int) * n);
		if (primeArray == NULL)
			return 1;
		primeArray[0] = 2;
		//      printf("First %d prime numbers are :\n",n);
		//      printf("2 ");
	}
	else {
		return 1;
	}

	for (count = 2; count <= n;)
	{
		if (isPrime(i))
		{
			primeArray[count - 1] = i;
			count++;
		}
		i++; // i is the number for test
	}
	end = clock();

	printf("first %u prime list:\n", n);
	for (i = 0; i < n; i++)
	{
		printf("%5u ", primeArray[i]);
		if (i % 10 == 9)
			printf("\n");
	}
	if (i % 10 != 9)
		printf("\n");

	mstime_consume = (end - begin) / (CLOCKS_PER_SEC / 1000.0);
	printf("consuming %f millisec.\n", mstime_consume);
	return 0;
}
