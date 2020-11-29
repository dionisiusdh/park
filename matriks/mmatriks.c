#include <stdio.h>
#include <stdlib.h>
#include "matriks.h"
#include "../boolean.h"
#include "../point/point.h"

int main() {
    // KAMUS
    MATRIKS M;
    POINT P;

    // ALGORITMA
    BacaMATRIKSTxt(&M, 10, 20, "../map1.txt");
    TulisMATRIKS(M);
    printf("\n");
    TulisMATRIKS(M);

    P = getPlayer(M);
    TulisPOINT(P);
    if (isNearWahana(M, P)) {
        printf("\nPlayer dekat wahana\n");
    }

    return 0;
}