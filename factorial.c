/*
  Factorial(階乘) program
  2023-01-06 check if input number > 0
			 maxmize result data type
*/
#include <stdio.h>

unsigned long long factorial(unsigned int);

int main()
{
	unsigned int number;

	printf("Enter a number to calculate it's factorial\n");
	scanf_s("%u", &number);

	if (number > 0)
	{
		printf("%d! = %ull\n", number, factorial(number));
		return 0;
	}
	else
	{
		printf("Input number should great than zero\n");
		return 1;
	}
}

unsigned long long factorial(unsigned int n)
{
	unsigned int c;
	unsigned long long result = 1;

	for (c = 1; c <= n; c++)
		result = result * c;

	return result;
}