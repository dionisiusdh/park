/* File: pengunjung.c */
/* *** REALISASI ABSTRACT DATA TYPE PENGUNJUNG *** */

#include <stdio.h>
#include "pengunjung.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membuat PENGUNJUNG *** */
void MakePENGUNJUNG (int JE, int SB, PENGUNJUNG *P){
/* Membuat data dengan tipe PENGUNJUNG dengan wahana yang ingin dinaiki kosong */
/* I.S. JE jumlah elemen efektif, SB kesabaran awal */
/* F.S. PENGUNJUNG terbentuk */
    ElmtEff(*P) = JE;
    SB = 5;
}

// BELUM SELESAI