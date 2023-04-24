int main(){
    int x;
    int y;
    int z;
    int a;
    int b;
    int c;
    x = 0;
    y = 1;
    z = 2;
    a = 3;
    b = 4;
    c = 5;
    // Some complex arithmetic expressions
    x = (((x+y)+(z-b))+((a+c)+(x+a)))*(((x*a)-(x*a))-((x+y)-(a+b+c)));
    y = y * z + x;
    z = z + x * y;
    a = a + b * c;
    b = b * c + a;
    c = c + a * b;
    // Some complex printf statements
    printf("x = %d\n", x);
    printf("y = %d, z = %d\n", y*2, z);
    return 0;
}