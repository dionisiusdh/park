#include <stdio.h>
#include "jam.c"

int main()
{   /* KAMUS */
    JAM J1, J2;
    /* ALGORITMA */
    BacaJAM(&J1);
    printf("Jam sekarang: ");
    TulisJAM(J1); printf("\n");
    printf("Konversi menjadi detik: %d\n",JAMToDetik(J1));
    J2 = DetikToJAM(5000);
    printf("5000 detik sama dengan jam : ");
    TulisJAM(J2);
    printf("/n");
    return 0;
}