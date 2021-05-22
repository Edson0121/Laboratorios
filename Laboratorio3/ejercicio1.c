#include <stdio.h>
/* Code to print the first n triangular numbers */

/* Function to calculate the first n triangular numbers, vois is used because nothing is returned */
void triangular(int number)
{
    /* Result */
    int res = 0;
    /* Count */
    int i;
    /* For loop to sum up all the numbers of the triangle */
    for(i = 0; i <= number; i++){
        res = res + i;
        printf("Valor del numero triangular no. %d: %d\n", i, res);
    }
}

/* Main function to call triangular function, we specify that we want the first 100 triangular numbers. */
int main(void)
{
    int number = 100;
    triangular(number);
    return 0;
}