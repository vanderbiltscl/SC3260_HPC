#include <stdio.h> // for printf
#include <stdlib.h> // for atoi and atof

int main(int argc, char **argv)
{

   // argc captures the number of command-line arguments
   // note: The executable command (./command_line) is 
   // always the first argument, and the remaining arguments
   // are separated by spaces      
   printf("argc: %d\n",argc);
   if ( argc != 3 ) {
      printf("Usage: ./pass_command_line_options arg1 arg2\n");
      printf("where arg1 is an integer and arg2 is a floating point number\n");
      exit(0);
   }
   
   // argv captures each argument in an array of characters
   // Here we loop over all arguments and print the value
   int i;
   for (i=0;i<argc;i++) {
      // %d is for integers, %s is for an array of characters
      printf("i: %d argv[i]: %s\n",i,argv[i]); 
   }

   // since command-line arguments are read in as an 
   // array of characters, they must be converted
   // to the appropriate type (e.g. int, float)
   i = 1;
   int myarg_int = 0;
   float myarg_float = 0.0;
   if ( argc > 1 ) myarg_int = atoi(argv[i]);
   ++i; 
   if ( argc > 2 ) myarg_float = atof(argv[i]);

   // %d is for integer
   // %10.5f is for the floating point number, 10 is the width of the number
   // and 5 is the precision after the decimal point. If more precision is 
   // needed, 10.5 can be changed.
   printf("myarg_int: %d myarg_float: %10.5f\n",myarg_int,myarg_float);

   return 0;

}
