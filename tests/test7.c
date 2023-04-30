int main()
{
    int i;
    int j;
    i = 0;

    for (i = 0; (i < 3); i = i + 1)
    {
        if (i == 5)
        {
            printf("no i = 5\n");
        }
        else
        {

            if (i == 7)
            {
                printf("lol xd i = 7\n");
            }
            else
            {
                printf("i = %d\n", i);
            }
        }
        for(j = 0; j < 2; j = j + 1){
            printf("i = %d\n", i);
        }
        if(i == 5)
        {
            printf("no i = 5\n");
        }
        else
        {
            printf("i = %d\n", i);
        }
        j = j + 1;
    }
    printf("lol i = %d\n", i);
    return 0;
}