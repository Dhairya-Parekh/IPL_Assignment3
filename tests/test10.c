// struct A{
//     int x;
//     int y;
//     int z;
// };
// struct A f(int a, int b){
//     struct A d;
//     return d;
// }
int f(int a, int b){
    printf("%d\n", a);
    return a + b;
}
int main(){
    // struct A y[10];
    int x;
    int y;
    x = 1;
    y = f(1, 2);
    printf("%d\n", y);

    printf("%d\n", 1 + f(3,4) + 34 + f(3*f(f(f(x,y+2),f(f(f(x+4,y-8)*6,f(x,y)),f(3,6))),6),f(3,4)));
    return 0;
}