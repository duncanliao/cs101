#include <stdio.h>

void printsp(int i, int n){
    for(int j = 0; j < n - i; j++){
        printf(" ");
    }
}

void printnum(int i){
    for(int j = 0; j < i; j++){
        printf("%d", i);
        if(j < i - 1){
            printf(" ");  
        }
    }
}

int main(){
    int rows = 6;

    for(int i = 1; i <= rows; i++){
        printsp(i, rows);   
        printnum(i);        
        printf("\n");      
    }

    return 0;
}
