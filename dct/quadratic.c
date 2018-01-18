#include <stdio.h>
#include <math.h>

void quadratic_function()

{
    int         a,b,c;      // variables
    double    result;     // my X in the quadractic function
    double    y,x1,x2;            // the result
    double    quadratic;

    printf("enter values for a,b,c\n");
    scanf("%i\n %i\n %i", &a,&b,&c);
    printf("A=%i  B=%i  C=%i\n", a,b,c); //Displays Variables

    result= pow(b, 2) - 4*(a)*(c); // b^2-4ac
    printf("\nb^2-4ac=%lf\n",result);


    if (result<0) 
        printf("Imaginary Number\n"); // if negative

    else{  // (result>=0);
        //solving for x
    	result = sqrt( result);
    	x1 = (-b + result)/(2*a);
    	x2 = (-b - result)/(2*a);

        printf("\n%lf\t%lf\n",x1,x2);

        quadratic=pow(x1, 2)*a + b*x1 + c;        // if positive
        printf("\nQuadratic equation equal to %lf\n",quadratic); // result

        quadratic=pow(x2, 2)*a + b*x2 + c;        // if positive
        printf("Quadratic equation equal to %lf\n",quadratic); // result
    }

}

int main()
{
quadratic_function();
return 0;

}