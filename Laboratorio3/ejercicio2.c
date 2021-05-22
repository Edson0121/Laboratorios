#include <stdio.h>

/* Calculate the factorial of a number */ 
int factorial (int n)
{
    int i = 1;
    /* Loop to mutiply the given n number by the n-1 number  */
    while (n > 1){
        i = i * n;
        /* int n = n - 1; */
        n = n - 1;
    }
    return i;
}

/* Main function, here we ask the user for the input*/
int main (int argc, char *argv[])
{
    int f, res;
    printf("Enter a number: ");
    /* Check if the input is a number */
    if(scanf("%d", &f) == 1){
        res = factorial(f);
        printf("%d! = %d\n", f, res);
    }
    else{
        printf("Dato no valido ingresado\n");
    }
    /* int fac4 = factorial(4);
    int fac5 = factorial(5);
    printf("4! = %d, 5! = %d\n", fac4, fac5); */
    return 0;
}