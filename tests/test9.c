struct A
{
    int x;
    int y;
    int z;
};

struct A f(struct A a){
    struct A d;
    return d;
}
int main(){
    struct A y;
    y = f(y);
    return 0;
}