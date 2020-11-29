/* File: pengunjung.c */
/* *** REALISASI ABSTRACT DATA TYPE PENGUNJUNG *** */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pengunjung.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membuat PENGUNJUNG *** */
void MakePENGUNJUNG (PENGUNJUNG *P, int random, TabInt Kapasitas){
/* Membuat data dengan tipe PENGUNJUNG dengan wahana yang ingin dinaiki kosong */
/* I.S. Sembarang */
/* F.S. PENGUNJUNG terbentuk */
    Kesabaran(*P) = 5;
    //Prioritas(*P) = 0;
    NeffPengunjung(*P) = 0;
    GetRandomWahana(P, random, Kapasitas);
}

void GetRandomWahana (PENGUNJUNG *P, int random, TabInt Kapasitas) { // Butuh input list wahana juga
/* Menghasilkan wahana random yang ingin dikunjungi pengunjung */
/* I.S. P terdefinisi tapi belum ada wahana yang ingin dikunjungi*/
/* F.S. P terdefinisi dengan wahana random */
    /* KAMUS */
    int randomNumber, randomNumber2;
    int i, jumlahWahana;

    /* ALGORITMA */
    srand(random);

    // Ambil wahana yang tersedia
    jumlahWahana = NbElmtArray(Kapasitas);
    randomNumber = rand() % jumlahWahana;
    NeffPengunjung(*P) = randomNumber+1;

    // Generate wahana yang ingin dinaiki pengunjung berdasarkan wahana yang tersedia
    for (i=0; i<NeffPengunjung(*P); i++) {
        ElmtPengunjung(*P, i) = Nama(ElmtArray(Kapasitas, i));
    }
}

void TulisWahana (PENGUNJUNG P) 
/* Menuliskan isi wahana yang ingin dinaiki pengunjung */
{
    int i;

    printf("(");
    if (NeffPengunjung(P) != 1382480432 && NeffPengunjung(P) != 0) {
        PrintKata(ElmtPengunjung(P, 0));
        for (i=1; i<NeffPengunjung(P); i++) {
            printf(", ");
            PrintKata(ElmtPengunjung(P, i));
        }
    }
    printf(")");
}

boolean SearchPengunjung(PENGUNJUNG P, Kata Wahana)
/* Search Wahana pada pengunjung P */
{
    int i=0;
    boolean found = false;
    while (i<NeffPengunjung(P) && !found){
        if (IsEQKata(ElmtPengunjung(P,i), Wahana)){
            found = true;
        }
        i++;
    }
    return found;
}

void DellPengunjung(PENGUNJUNG *P, Kata Wahana)
/* Delete wahana dari list pengunjung */
{
    int i=0;
    boolean found = false;
    while (i<NeffPengunjung(*P) && !found){
        if (IsEQKata(ElmtPengunjung(*P,i),Wahana)){
            found = true;
        }
        i++;
    }
    while (i<NeffPengunjung(*P) && NeffPengunjung(*P) != 1){
        ElmtPengunjung(*P,i-1) = ElmtPengunjung(*P,i);
        i++; 
    }
    NeffPengunjung(*P) -= 1; 
}