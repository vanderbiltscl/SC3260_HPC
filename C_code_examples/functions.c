#include <stdio.h>


float mySimpleFuncByValue(int iloc,float xloc)
{

   iloc += 101;
   xloc *= 14.6;

   float yloc = (float)iloc * xloc;
   
   return yloc;   

}

float mySimpleFuncByReference(int * iPtr,float * xPtr)
{

   // dereference the pointer and modify the value it points to
   *iPtr += 101;
   *xPtr *= 14.6;

   // make copies to the values that each pointer points to
   int iloc = *iPtr;
   float xloc = *xPtr;

   float yloc = (float)iloc * xloc;
   
   return yloc;   

}

void modifyArray( int * array )
{

   array[0] = 5;
   array[1] = 12;

}


int main()
{

   int i = 22;
   float x = 234.23;

   // i and x are both passed by value,
   // meaning a copy of each of these variables
   // is passed to mySimpleFunc
   float y = mySimpleFuncByValue(i,x);
   printf("i: %d x: %10.5f y: %10.5f\n",i,x,y);
   // Now i and x are both being passed by reference
   // (Notice the & symbol)
   // This means that the actual memory location of 
   // i and x are being passed, so any modifications
   // to the values i and x within the function will
   // propogate to main() 
   y = mySimpleFuncByReference(&i,&x);
   printf("i: %d x: %10.5f y: %10.5f\n",i,x,y);

   int myArray[2] = { 0, 0 };
   printf("Before function call, myArray[0]: %d myArray[1]: %d\n",myArray[0],myArray[1]);
   modifyArray(myArray);
   printf("After function call, myArray[0]: %d myArray[1]: %d\n",myArray[0],myArray[1]);

   return 0;

}