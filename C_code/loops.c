#include <stdio.h>

int main()
{
   
   int n = 10;

   int i; // we'll use i as an index within a for loop
   int x[n];
   for ( i=0; i<n ; i++ ) {
      x[i] = i * 10;
      printf("i: %d x[i]: %d\n",i,x[i]);
   }

   // while loops are useful in certain situations as well
   int y = 0;
   while ( y < 100 ) {
      y += 12;
      printf("y: %d\n",y);
   }

   // and do-while loops, use these instead of while loops
   // if you want the code block executed before evaluation
   // of a condition (rather than vice versa, as is done with
   // a normal while loop)
   y = 0;
   do {
      y += 12;
      printf("y: %d\n",y);
   }
   while ( y < 100 );

   return 0;

}
