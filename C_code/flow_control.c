#include <stdio.h>

int main()
{

  int i = 1;

  // native boolean variables don't exist in C
  // Integers are typically used instead, with a 
  // value of 0 evaluated as false and a non-zero
  // value evaluated as true
  if ( i ) printf("i is true with value of: %d\n",i);
  i = 123;
  if ( i ) printf("i is true with value of: %d\n",i);
  i = -321;
  if ( i ) printf("i is true with value of: %d\n",i);

  i = 0;
  if ( i ) {
     printf("i is true with value of: %d\n",i);
  }
  else {
     printf("i is false with value of: %d\n",i);
  }

  int y = 26;

  // Note that in a large if-else block like the one
  // below, program flow jumps out of the block after
  // the first condition is met, and its contents are 
  // executed. This is why "condition 5 is met!" is not
  // printed.
  if ( i > 0 && y == 26 ) {
     printf("condition 1 met!\n");
  }
  else if ( i > 0 || y == 25 ) {
     printf("condition 2 met!\n");
  }
  else if ( i != 0 ) {
     printf("condition 3 met!\n");
  }
  else if ( !i && y >= 20 ) {
     printf("condition 4 met!\n");
  }
  else if ( i == 0 ) {
     printf("condition 5 met!\n");
  }
  else {
     printf("no condition met!\n");
  }

  // nested if-else blocks are also allowed
  if ( y == 26 ) {
     if ( i != 0 ) {
        printf("i is not zero!\n");
     }
     else {
        printf("i is zero\n");
     }
  }

  return 0;

}
