#include <stdio.h>
#include "prepaksi.h"
#include "../boolean.h"
#include <stdlib.h>

// gcc -std=c99 -o dprep dprep.c prepaksi.o ../array/array.o ../mesin/mesinkata.o ../mesin/mesinkar.o ../stack/stack.o ../jam/jam.o
// gcc -std=c99 -o dprep dprep.c ./prepaksi.o ../mesin/mesinkata.o ../array/array.o ../mesin/mesinkar.o ../Tree/bintree.o ../stack/
// stack.o ../jam/jam.o ../matriks/matriks.o ../point/point.o ../Graph/graph.o
int main() {
    TabInt Inven;
    aksitype CurrentAksi;
    int CurrentWahana;
    boolean cek;
    MakeEmpty(&L);
    MakeEmpty(&Inven);
    BinTree W1,W2,W3;
    
    BacaWahana(&W1,&W2,&W3);
    int money = 5000;
    printf("Initial Money: %d", money);
    BacaMaterial(&Inven);
    SetAllValueX(&Inven, 100);
    TulisIsiTab(Inven);
    printf("\n");
    printf("Initial Inventory:");
    TulisIsiTab(Inven);
    printf("\n");
    MenuBuild(&Inven, W1, W2, W3, &CurrentWahana, &cek);
    // TulisIsiTab(Inven);
    // printf("\nFinal Money: %d\n", money);
    // printf("Initial Inventory:");
    // TulisIsiTab(Inven);
    printf("\n");
    return 0;
}

// gcc -std=c99 -o dprep dprep.c ./prepaksi.o ../mesin/mesinkata.o ../array/array.o ../mesin/mesinkar.o ../Tree/bintree.o ../stack/stack.o ../jam/jam.o ../matriks/matriks.o ../point/point.o ../Graph/graph.o