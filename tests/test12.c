struct A
{
    int x;
    int y;
};

int f(struct A a)
{
    a.x = 3;
    a.y = 4;
    return 2;
}

int main()
{
    struct A a;
    int b;
    b = f(a);
    return 0;
}