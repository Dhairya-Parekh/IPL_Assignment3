struct A
{
    int x;
    int y;
    int z;
};

int f(int a, int b){
    struct A d;
    a = b;
    b = a;
    // return d;
    return 34;
}
int main(){
    int x;
    struct A y;
    x = 12;
    x = f(12, 56);
    return 0;
}