int main(){
    int x;
    int y;
    x = 0;
    y = 0;
    y = x < y;
    if((x<y) < (x>y)){
        printf("x%d\n",x);
    }
    else{
        if(x+y||x-y){
            printf("x-%d\n",x);
        }
        else{
            printf("y-%d\n",y);
        }
        printf("y%d\n",y);
    }
    return 0;
}