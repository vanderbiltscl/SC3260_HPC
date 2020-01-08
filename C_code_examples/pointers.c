#include <stdio.h>

int main()
{

  // a normal integer is declared like so
  // This assigns a piece of memory for i,
  // and stores the value 1 in this memory
  int i = 1; 

  // Pointers were introduced as a way to 
  // access a memory location directly, rather
  // than the value stored in that memory location
  //
  // Declare a pointer with the * character
  int * iPtr;
  // Now reference a variable's memory using the & symbol.
  // The following statement will store the memory location
  // of i in iPtr. So the "type" for a pointer is memory
  // address.
  iPtr = &i;
  printf("memory address of i: %p\n",&i);
  printf("memory address iPtr is pointing to: %p\n",iPtr);
  printf("memory address of iPtr: %p\n",&iPtr);
  // You can also access the value in memory that a 
  // pointer is pointing to using the * symbol. This
  // is called dereferencing.
  printf("i: %d, *iPtr: %d\n",i,*iPtr);

  // There are several benefits from using points, one
  // is passing function arguments by reference, which
  // is illustrated in the functions.c example. 
  //
  // With pointers you have the ability to alter the value
  // stored in a memory location directly. E.g.:
  *iPtr = 2;
  printf("After using \"*iPtr = 2;\", i: %d\n",i);

  return 0;

}
