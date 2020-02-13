#include <stdio.h>   // for printf
#include <stdlib.h>  // for atoi
#include "fibonacci.h"     // for fib

int main(int argc, char* argv[])
{
    int n = atoi(argv[1]);
    printf("%f\n", fib(n));
}
