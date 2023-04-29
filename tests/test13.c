struct A{
    int x;
    int y;
};
struct B
{
    int x;
    struct A a;
};
struct A f(struct A a)
{
    a.x = 3;
    printf("%d\n", a.x);
    printf("%d\n", a.y);
    return a;
}

