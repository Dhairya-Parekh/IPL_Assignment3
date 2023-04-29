int main(){
    int x,y;
    x =100;
    y = x+1;
    x = (x!=100) || (y!=100);

    printf("%d %d\n",x+x*y,y>100);
    return 0;
}