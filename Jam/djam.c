#include <stdio.h>
#include "jam.c"

int main()
{   /* KAMUS */
    JAM J1, J2;
    
    /* ALGORITMA */
    BacaJAM(&J1);
    printf("Jam sekarang: ");
    TulisJAM(J1);
    printf("\n");
    IncrementNMenit(&J1,2);
    TulisJAM(J1);
    printf("\n");
    DecrementNMenit(&J1,23);
    TulisJAM(J1);
    printf("\n");
    DecrementNDetik(&J1,36);
    TulisJAM(J1);
    printf("\n");
    return 0;
}