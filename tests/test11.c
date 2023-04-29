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

void h(struct A a){
    printf("%d\n", a.x);
    printf("%d\n", a.y);
}

int main(){
    struct A a;
    a.x = 1;
    a.y = 2;
    h(f(a));
    return 0;
}