#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "main.h"
#include "./mesin/mesinkar.c"
#include "./mesin/mesinkata.c"
#include "./matriks/matriks.c"
#include "./point/point.c"
#include "./Jam/jam.c"

/******* FUNGSI MAIN *******/
int main() {
  /* *********** VARIABEL UTAMA ********** */
  /* Map */
  // Map 1 > <  Map 2
  //  V          V
  //  ^          ^
  // Map 4 > < Map 3
  MATRIKS Map1;
  MATRIKS Map2;
  MATRIKS Map3;
  MATRIKS Map4;

  /* Posisi */
  POINT PPlayer;
  POINT POffice;
  POINT PAntrian;
  POINT PGerbang_Map1_Kanan;
  POINT PGerbang_Map1_Bawah;
  POINT PGerbang_Map2_Kiri;
  POINT PGerbang_Map2_Bawah;
  POINT PGerbang_Map3_Atas;
  POINT PGerbang_Map3_Kiri;
  POINT PGerbang_Map4_Atas;
  POINT PGerbang_Map4_Kanan;

  /* Algoritma */
  //showMap(Map1);
  initGame();
  initMap(&Map1);

  return 0;
}

/******* REALISASI FUNGSI-FUNGSI UTAMA *******/
void initGame() {
    /**** MAIN MENU ****/
    printf("// Welcome to Willy wangky's fum factory!!//\n// New game / load game / exit? //\n$ ");

    // Baca masukan 
    STARTKATA();
    while (!EndKata) {
        ADVKATA();  
    }

    if (CKata.TabKata[0] == 'n' || CKata.TabKata[0] == 'N') {
        printf("Memulai permainan baru...\n");
        printf("Masukkan nama: \n$ ");
        concatNama();
    }

    if (CKata.TabKata[0] == 'e' || CKata.TabKata[0] == 'E') {
        printf("// Thanks for playing!!! //");
    }
}

void initMap(MATRIKS *Map) {
  BacaMATRIKSTxt(Map, 10, 20, "../map1.txt");
}

void initPosisi (MATRIKS *MAP, POINT *PPlayer, POINT *POffice, POINT *PAntrian) {
  *PPlayer = getPlayer(*MAP);
  *POffice = getOffice(*MAP);
  *PAntrian = getAntrian(*MAP);
}

void initJam (JAM *J) {
  *J = MakeJAM(21,0,0);
}

char kata[50];
void concatNama() {
  STARTKATA();
  int j=0; int i;
  while (!EndKata) {
    for (i=0; i<CKata.Length; i++) {
      kata[i+j] = CKata.TabKata[i];
    }
    kata[i+j] = ' ';
    j+=CKata.Length+1;
    ADVKATA();
  }
  printf("%s",kata);
}

void printMap (MATRIKS M) {
/* Mencetak Map dan Legenda */

    //KAMUS LOKAL
    int i,j;

    //ALGORITMA
    TulisMATRIKS(M);
    printf("Legend:\n");
    printf("A = Antrian\n");
    printf("P = Player\n");
    printf("W = Wahana\n");
    printf("O = Office\n");
}