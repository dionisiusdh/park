/* File: pengunjung.c */
/* *** REALISASI ABSTRACT DATA TYPE PENGUNJUNG *** */

#include <stdio.h>
#include "pengunjung.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membuat PENGUNJUNG *** */
void MakePENGUNJUNG (PENGUNJUNG *P){
/* Membuat data dengan tipe PENGUNJUNG dengan wahana yang ingin dinaiki kosong */
/* I.S. Sembarang */
/* F.S. PENGUNJUNG terbentuk */
    Kesabaran(*P) = 5;
    Prioritas(*P) = 0;
    GetRandomWahana(P);
}

void GetRandomWahana (PENGUNJUNG *P) { // Butuh input list wahana juga
/* Menghasilkan wahana random yang ingin dikunjungi pengunjung */
/* I.S. P terdefinisi tapi belum ada wahana yang ingin dikunjungi*/
/* F.S. P terdefinisi dengan wahana random */
    /* KAMUS */
    int randomNumber;
    int i;

    /* ALGORITMA */
    randomNumber = rand(5);
    NeffPengunjung(*P) = randomNumber;

    for (i = 0; i < NeffPengunjung(*P); i++) {
        randomNumber = rand(3);
        // Do something buat generate wahana dari angka random
        // ElmtPengunjung(*P, i) = Wahana;
    }
}

// BELUM SELESAI