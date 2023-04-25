int main()
{
    int x;
    int y;
    x = 0;
    if (x > 3)
    {
        x = 1;
        printf("x > 3\n");
    }
    else
    {
        if (x > 4)
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
    return 0;
}