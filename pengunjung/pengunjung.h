/* File: pengunjung.h */
/* *** Definisi ABSTRACT DATA TYPE PENGUNJUNG *** */

#ifndef PENGUNJUNG_H
#define PENGUNJUNG_H

#include "../boolean.h"
#include "../mesin/mesinkata.h"

#define MaxElmt 5
/* Maksimum wahana yang ingin dikunjungi pengunjung */
#define KesabaranAwal 5
/* Nilai kesabaran awal */
#define PrioritasAwal 0
/* Nilai priorias awal */

typedef Kata ElPengunjungType;
typedef struct {
    ElPengunjungType Mem[MaxElmt+1];    /* Wahana yang ingin dinaiki pengunjung */
    int NeffPengunjung;                 /* Jumlah elemen efektif wahana yang ingin dikunjungi pengunjung */
    int Prioritas;                      /* Priority */
	int Kesabaran;                      /* Tingkat kesabaran   */
} PENGUNJUNG;

/* *** Selektor *** */
#define NeffPengunjung(P) (P).NeffPengunjung
#define Prioritas(P) (P).Prioritas
#define Kesabaran(P) (P).Kesabaran
#define ElmtPengunjung(P,i) (P).Mem[(i)]

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membuat PENGUNJUNG *** */
void MakePENGUNJUNG (int Neff, PENGUNJUNG *P);
/* Membuat data dengan tipe PENGUNJUNG dengan wahana yang ingin dinaiki kosong */
/* I.S. JE jumlah elemen efektif, SB kesabaran awal */
/* F.S. PENGUNJUNG terbentuk */

void GetRandomWahana ();
/* Menghasilkan wahana random */

#endif