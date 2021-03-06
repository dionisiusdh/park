/* File: pengunjung.h */
/* *** Definisi ABSTRACT DATA TYPE PENGUNJUNG *** */

#ifndef PENGUNJUNG_H
#define PENGUNJUNG_H

#include "../boolean.h"
#include "../mesin/mesinkata.h"
#include "../array/array.h"

#define MaxElmt 5
/* Maksimum wahana yang ingin dikunjungi pengunjung */
#define KesabaranAwal 5
/* Nilai kesabaran awal */
#define PrioritasAwal 0
/* Nilai priorias awal */

typedef struct {
    Kata Mem[MaxElmt+1];    /* Wahana yang ingin dinaiki pengunjung */
    int NeffPengunjung;                 /* Jumlah elemen efektif wahana yang ingin dikunjungi pengunjung */
    // int Prioritas;                      /* Priority */
	int Kesabaran;                      /* Tingkat kesabaran   */
} PENGUNJUNG;

/* *** Selektor *** */
#define NeffPengunjung(P) (P).NeffPengunjung
// #define Prioritas(P) (P).Prioritas
#define Kesabaran(P) (P).Kesabaran
#define ElmtPengunjung(P,i) (P).Mem[(i)]

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membuat PENGUNJUNG *** */
void MakePENGUNJUNG (PENGUNJUNG *P, int random, TabInt Kapasitas);
/* Membuat data dengan tipe PENGUNJUNG dengan wahana yang ingin dinaiki kosong */
/* I.S. Sembarang */
/* F.S. PENGUNJUNG terbentuk */

void GetRandomWahana (PENGUNJUNG *P, int random, TabInt Kapasitas);
/* Menghasilkan wahana random yang ingin dikunjungi pengunjung */

void TulisWahana (PENGUNJUNG P);
/* Menuliskan isi wahana yang ingin dinaiki pengunjung */

boolean SearchPengunjung(PENGUNJUNG P, Kata Wahana);
/* Search Wahana pada pengunjung P */

void DellPengunjung(PENGUNJUNG *P, Kata Wahana);
/* Delete wahana dari list pengunjung */

#endif