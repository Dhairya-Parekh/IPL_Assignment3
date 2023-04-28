int main(){
    int x;
    int y;
    int z;
    y = 5;
    for(x =0; x < 10; x = x + 1){
        while(x < 5){
            y = y + 2;
            x = x + 1;
        }
        if(x > 5){
            y = y + 2 ;
        }
        else{
            z = 4;
        }
    }
    printf("%d %d %d\n", x, y, z);
    return 0;
}