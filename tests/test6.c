int main()
{
    int x;
    int y;
    int z;
    z = 5;
    x = 0;
    if (x > 3||z > 7)
    {
        x = 1;
        if(x > 3)
        {
            x = 2;
            printf("hello\n");
        }
        else
        {
            x = 3;
            printf("x <= 3\n");
        }
        printf("x > 3\n");
    }
    else
    {
        if (x > 4 && z < 7)
        {
            x = 2;
            printf("x > 4\n");
        }
        else
        {
            x = 3;
            printf("x <= 4\n");
        }
        y = 4;
        printf("y = 4\n");
    }
    printf("x = %d\n", x);
    printf("y = %d\n", y);
    printf("z = %d\n", z);
    while(((x < 10)||(y < 10)||(z < 10))&&(x < 20 && z>7)||(y>=10||z>=10))
    {
        x = x + 1;
        printf("x = %d\n", x);
    }
    return 0;
}