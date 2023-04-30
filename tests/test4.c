int main(){
    int a;
    int x;
    int y;
    int z;
    int b;
    int c;
    x = 3;
    y = 1;
    z = 2;
    b = 4;
    c = 5;
    a = 6;
    // Some complex arithmetic expressions
    // x = ((((x-b)+(y+(5+7)))+((z*b)-(b*y)))+(((a+b)+(a+c))+(x-a)))*(((x*a)-(x*a))-((x+y)-(a+b+c)));
    // x = ((x/b+((z/b)-(b*y)))+(((a/b)+(a+c))+(x/a)))/(((x*a)-(x*a))-((x+y)-(a+b+c)));
    x = (x/b+((z/b)-(b/y)));
    // x = (z/b)-(b/y);
    // y = y * z + x;
    // z = z + x * y;
    // a = a + b * c;
    // b = b * c + a;
    // c = c + a * b;
    // Some complex printf statements
    printf("x = %d\n", x);
    printf("y = %d, z = %d\n", y*2, z);
    return 0;
}