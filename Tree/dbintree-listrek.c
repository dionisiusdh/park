#include <stdio.h>
#include <stdlib.h>
#include "./bintree.h"
#include "../boolean.h"
#include "../mesin/mesinkata.h"
#include "../mesin/mesinkar.h"

// gcc -std=c99 -o dtree dtree.c ../mesin/mesinkata.o ../mesin/mesinkar.o bintree.o

int main() {
    BinTree Wahana1, Wahana2, Wahana3;
    BacaWahana(&Wahana1, &Wahana2, &Wahana3);
    printf("%d", AkarHarga(Wahana1));
    int i;
    printf("\n");
    for (i=0; i<5; i++) {
        printf("\nElemen: %d\n", MatUp(Akar(Wahana1),i));
    }
    printf("asdasd");
    PrintNamaWahana(Wahana1, Wahana2, Wahana3);
    return 0;
}