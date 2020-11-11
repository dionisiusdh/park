/* File: pengunjung.h */
/* *** Definisi ABSTRACT DATA TYPE PENGUNJUNG *** */

#ifndef PENGUNJUNG_H
#define PENGUNJUNG_H

#include "../boolean.h"

/* Maksimum wahana yang ingin dikunjungi pengunjung */
#define MaxElmt 25

typedef int ElType;
typedef struct {
    ElType Mem[MaxElmt+1];
    int ElmtEff; /* Jumlah elemen efektif */
	int Sabar; /* Tingkat kesabaran   */
} PENGUNJUNG;

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membuat PENGUNJUNG *** */
void MakePENGUNJUNG (int JE, int SB, PENGUNJUNG *P);
/* Membuat data dengan tipe PENGUNJUNG dengan wahana yang ingin dinaiki kosong */
/* I.S. JE jumlah elemen efektif, SB kesabaran awal */
/* F.S. PENGUNJUNG terbentuk */

/* *** Selektor *** */
#define ElmtEff(P) (P).ElmtEff
#define Sabar(P) (P).Sabar
#define Elmt(P,i) (P).Mem[(i)]

// BELUM SELESAI

#endif