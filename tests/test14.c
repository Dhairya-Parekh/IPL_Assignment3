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
    g(b);
    return 0;
}