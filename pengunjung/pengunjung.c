/* File: pengunjung.c */
/* *** REALISASI ABSTRACT DATA TYPE PENGUNJUNG *** */

#include <stdio.h>
#include "pengunjung.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membuat PENGUNJUNG *** */
void MakePENGUNJUNG (int Neff, PENGUNJUNG *P){
/* Membuat data dengan tipe PENGUNJUNG dengan wahana yang ingin dinaiki kosong */
/* I.S. JE jumlah elemen efektif, SB kesabaran awal */
/* F.S. PENGUNJUNG terbentuk */
    NeffPengunjung(*P) = Neff;
    Kesabaran(*P) = 5;
    Prioritas(*P) = 0;
}

// BELUM SELESAI