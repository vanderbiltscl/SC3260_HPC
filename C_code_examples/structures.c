#include <stdio.h>

typedef struct {
   char * name;
   int age; // in years
   float height; // in inches
   float grades[10]; // grade on 10 assignments
} student;

void printStruct( student oneStudent )
{
   int i;

   printf("=====================\n");
   printf("Student name: %s\n",oneStudent.name);
   printf("        age: %d\n",oneStudent.age);
   printf("        height: %6.3f\n",oneStudent.height);
   printf("        grades: ");
   for (i=0; i<10; i++) printf("%4.1f ",oneStudent.grades[i]);
   printf("\n");
   printf("=====================\n");

   // note that we're just changing the age of the local
   // copy here, so this will not affect the age of the 
   // original struct created in main()
   oneStudent.age = 45;

}

void modifyStruct( student * oneStudent )
{

   // pointers to structs have special -> symbols
   // for deferencing the pointer and accessing a 
   // data member.   
   oneStudent->grades[0] = 72.0; // equivalent to: (*oneStudent).grades[0] = 72.0;
   oneStudent->grades[4] = 81.0;
   oneStudent->grades[6] = 85.0;

}

int main()
{

   student Nikki;
   Nikki.name = "Nikki";
   Nikki.age = 19;
   Nikki.height = 64.75;
   int i;
   for (i=0; i<10 ; i++) {
      Nikki.grades[i] = 98.0; // overachiever
   }

   printStruct(Nikki);

   // It's advantageous to pass arrays and structures by reference, 
   // because it's more efficient (don't need to make a copy of all data)
   // and allows you to modify the contents of the array or struct
   modifyStruct(&Nikki);

   printStruct(Nikki);

   return 0;
}
