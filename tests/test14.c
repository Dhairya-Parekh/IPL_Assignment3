struct A{
    int x;
    int y;
};
struct B{
  struct A a;
  int b;
};

struct A f(struct A a){
    a.x = 3;
    printf("%d\n", a.x);
    printf("%d\n", a.y);
    return a;
}

void g(struct B b){
    f(b.a);
    printf("%d\n", b.a.x);
    printf("%d\n", b.a.y);
}
int main(){
    struct A a;
    struct B b;
    a.x = 10;
    a.y = 20;
    b.a = a;
    b.a = f(f(a));
    printf("%d\n", b.a.x);
    printf("%d\n", b.a.y);
    g(b);
    return 0;
}