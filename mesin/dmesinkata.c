#include "mesinkata.h"
#include "mesinkar.h"
#include "../boolean.h"
#include "../array/array.h"
#include <stdio.h>

int main() {
    TabInt T, T2;
    MakeEmpty(&T);
    MakeEmpty(&T2);
    int i;
    BacaMaterial(&T);
    BacaAksi(&T2);
    TulisIsiTab(T);
    
    TulisIsiTab(T2);
    printf("\n");
    return 0;
}