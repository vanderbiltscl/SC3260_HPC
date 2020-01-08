#include <stdio.h>  // printf is defined in this header file

// This defines a function called "main"
// The return type is an int (integer)
// And it takes no arguments
//
// The main function is required for all 
// C programs. It's where execution of the
// code begins. The return type must be an
// int. 
int main()
{
   // I tend to use spaces to make blocks
   // of code more readable, you can also
   // use tabs.
   //
   // This line calls a function called printf,
   // and passes a "Hello World!" string, along
   // with a special end of line character (\n)
   //
   // A semi-colon is required at the end of 
   // each line
   printf("Hello world!\n");

   // Recall that the return type for the main
   // function is an int. Here, we return the 
   // integer zero, which is the convention 
   // for signifying that the program exited
   // normally. You actually don't need to
   // include this line at all. You might get
   // a warning from the compiler but the program
   // will compile and run normally.
   return 0;

}