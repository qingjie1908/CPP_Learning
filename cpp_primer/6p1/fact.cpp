int fact(int x)
{
    int fact = 1;
    while (x > 1){
        fact *= x;
        --x;
    }
    return fact;
}