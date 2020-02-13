int main()
{
   int i; // declare an integer 
   int j = 12; // declare and initialize an integer
   const int k = 345; // declare and initialize a constant integer
   unsigned int l = 6789; // declare and initialize an unsigned integer

   char myletter; // declare a character called "myletter"

   float x = 1.23; // declare and initialize a single-precision floating point number
   double y = 45.6789; // declare and initialize a double-precision floating point number

   // arrays are contiguous in memory and can be
   // accessed like so: myarray[0], myarray[1], ...
   // Note that the first index is always 0 in C!
   int myarray[5] = { 2, 4, 6, 8, 10 }; // declare and initialize a 5-element integer array
   float farray[100]; // declare a 100-element array of single-precision floating point numbers

   return 0;
}