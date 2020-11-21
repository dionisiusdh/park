#include <stdio.h>
#include "prepaksi.h"
#include "../boolean.h"
#include <stdlib.h>

// gcc -std=c99 -o dprep dprep.c prepaksi.o ../array/array.o ../mesin/mesinkata.o ../mesin/mesinkar.o ../stack/stack.o ../jam/jam.o

int main() {
    TabInt L;
    TabInt Inven;
    MakeEmpty(&L);
    MakeEmpty(&Inven);
    

    int money = 5000;
    printf("Initial Money: %d", money);
    BacaMaterial(&L);
    BacaMaterial(&Inven);
    SetAllValueZero(&Inven);
    printf("\n");
    printf("Initial Inventory:");
    TulisIsiTab(Inven);
    printf("\n");
    MenuBuy(&Inven, &L, &money);
    TulisIsiTab(Inven);
    printf("\nFinal Money: %d\n", money);
    printf("Initial Inventory:");
    TulisIsiTab(Inven);
    printf("\n");
    return 0;
}