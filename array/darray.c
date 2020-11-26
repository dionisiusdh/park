#include <stdio.h>
#include "../boolean.h"
#include "array.h"

int main(){
    /* KAMUS */
    TabInt T;
    int X;
    IdxType hasil_search;

    /* ALGORITMA */
    BacaIsi(&T);
    scanf("%d",&X);
    
    TulisIsiTab(T);
    printf("\n");

    hasil_search = Search1(T,X);

    if(hasil_search == IdxUndef){
        printf("%d tidak ada\n",X);
    } else {
        printf("%d\n", hasil_search);
        MaxMin(T, &Max, &Min);
        Sort(&T,true);

        if(X == Max){
            printf("maksimum\n");
        }

        if(X == Min){
            printf("minimum\n");
        }
    }

    return 0;
}