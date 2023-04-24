int main(){
    int x;
    int y;
    x = -1;
    y = x+++x++;
    printf("%d\n", x);
    printf("%d\n", y++);
    printf("%d\n", y);
    x = -y+++x++;
    printf("%d\n", x);
    printf("%d\n", -y++);
    return 0;
}