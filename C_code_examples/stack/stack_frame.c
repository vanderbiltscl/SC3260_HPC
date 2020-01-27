# include<stdio.h>
int total;

int square(int x){
   return x*x;
}

int squareOfSums(int x, int y){
   int z = square(x+y);
   return z;
}

int main(){
   int a = 4, b = 8;
   total = squareOfSums(a, b);
   printf("output = %d\n", total);
}
