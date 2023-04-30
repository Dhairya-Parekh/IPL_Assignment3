struct A
{
    int x;
    int y;
};

int f(struct A a)
{
    printf("%d\n", a.x);
    a.x = 3;
    printf("%d\n", a.x);
    printf("%d\n", a.y);
    a.y = 4;
    return 2;
}

int main()
{
    struct A a, c;
    int b;
    a.x = 1;
    b = f(a);
    a.y = 6;
    c = a;
    printf("%d\n", a.x);
    printf("%d\n", a.y);
    printf("%d\n", b);
    printf("%d\n", c.x);
    printf("%d\n", c.y);
    c.y = b;
    printf("%d\n", a.y);
    printf("%d\n", c.y);
    return 0;
}