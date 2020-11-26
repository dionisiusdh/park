#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"
#include "./boolean.h"

int main() {
    /* KAMUS */
    List L;
    int N, Q, x;
    int i;
    infotype trash;
    addressList P;

    /* ALGORITMA */
    CreateEmpty(&L);
    scanf("%d", &N);
    
    for (i = 0; i<N; i++){
        InsVLast(&L, i+1);
    }
    
    scanf("%d", &Q);

    for (i = 0; i<Q; i++){
        scanf("%d", &x);

        if (Search(L, x) != Nil) {
            printf("Ada");
            DelP(&L, x);
            InsVFirst(&L, x);
            PrintInfo(L);
            printf("\n");
        } else {
            printf("Tidak ada");
            DelVLast(&L, &trash);
            InsVFirst(&L, x);
            PrintInfo(L);
            printf("\n");
        }
    }
    
    return 0;
}

