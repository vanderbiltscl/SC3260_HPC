double fib(int n) 
{
    double a = 0, b = 1;
    for (int i=0; i<n; i++) 
    {
        double tmp = b;
        b = a;
        a += tmp;
     }
    return a;
}
