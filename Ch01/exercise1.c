#include <stdio.h>
#include <stdlib.h>

int main()
{
    char a;
    char *x;

    int b;
    int *y;

    x = &a;
    y = &b;

    printf("The address for A = %p\n", &a);
    printf("The address for B = %p\n", &b);
    printf("-------------------\n");
    printf("The address in x = %p\n", x);
    printf("The address in y = %p\n", y);

    return(0);
}
