#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include "gcd.h"

int main(int argc, char* argv[])
{
    clock_t start, end;     
	start = clock();
	int n = atoi(argv[1]);
	int cnt = 0;
    for (int i=1; i<n; i++)
        for (int j=1; j<n; j++)
            if (find_gcd(i, j)==1)
                cnt += 1;

	end = clock();
    printf("Execution time %f s to find %d coprime numbers\n",
		   ((double) (end - start)) / CLOCKS_PER_SEC, cnt);
}
