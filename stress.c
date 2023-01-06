#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int main()
{
	double x, y;
	x = 3.1;
	y = 11.17;
	while (1)
	{
		x = x * y;
		if (x > 1000)
			x = sqrt(x);
		printf("x=%f\n", x);
	}
	return 0;
}
