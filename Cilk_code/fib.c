#include <cilk/cilk.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int fib(int n) {
  if (n < 2) return n;
  int x, y;
  x = cilk_spawn fib(n - 1);
  y = fib(n - 2);
  cilk_sync;
  return x + y;
}

int main(int argc, char *argv[]) {
  int n = atoi(argv[1]);
  struct timeval start, end;
  gettimeofday(&start, NULL);
  int result = fib(n);
  gettimeofday(&end, NULL);
  printf("Fib(%d)=%d in %f seconds\n", n, result, ((double)(end.tv_sec-start.tv_sec)*1e6+(end.tv_usec-start.tv_usec))*1e-6);
  return 0;
}