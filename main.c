#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "main.h"
#include "./mesin/mesinkar.h"
#include "./mesin/mesinkata.h"
#include "./matriks/matriks.h"
#include "./point/point.h"
#include "./jam/jam.h"
#include "./stack/stack.h"
#include "./array/array.h"
#include "./array/array.h"

// gcc -std=c99 -o main main.c ./mesin/mesinkar.o ./mesin/mesinkata.o ./matriks/matriks.o ./point/point.o ./jam/jam.o ./stack/stack.o ./array/array.o

/******* FUNGSI MAIN *******/
int main() {
  /* *********** KAMUS UTAMA ********** */
  /* *********** Map ********** */
  // Map 1 > <  Map 2
  //  V          V
  //  ^          ^
  // Map 4 > < Map 3
  MATRIKS Map1;
  MATRIKS Map2;
  MATRIKS Map3;
  MATRIKS Map4;

  /* *********** JAM ************** */
  JAM JOpen;
  JAM JClose;
  JAM MaxDuration;
  JAM JCurrent;
  JAM Remaining;

  /* *********** Posisi *********** */
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

  /* *********** Stack Aksi *********** */
  Stack S;

  /* *********** Informasi Aksi dan Harga Barang *********** */
  /* NamaAksi[i] durasinya Durasi[i] */
  TabInt NamaAksi;
  TabInt DurasiAksi;

  /* NamaBarang[i] harganya HargaBarang[i] */
  TabInt NamaBarang;
  TabInt HargaBarang;

  /* Nama Pemain dan Saldonya (Money) */
  Kata Nama;
  int money = 1000;
  boolean prep = true;


  /* *********** ALGORITMA UTAMA ********** */
  //Inisialisasi
  initMap(&Map1);
  initJam(&JOpen,&JClose);
  MaxDuration = KurangJAM(JOpen,JClose);
  CreateEmpty(&S,MaxDuration);
  //showMap(Map1);
  initGame(&Nama);
  if (prep) {
    JCurrent = TambahJAM(JClose, CurrentDuration(S));
    Remaining = KurangJAM(JOpen,JCurrent);
    prepDescription(Map1, Nama, money, JCurrent, JOpen, Remaining, S);
  }
  return 0;
}

/******* REALISASI FUNGSI-FUNGSI UTAMA *******/
/*********************************************/
    /**** MAIN MENU ****/
void initGame(Kata * Nama) {
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
        *Nama = concatNama();
    }

     if (CKata.TabKata[0] == 'e' || CKata.TabKata[0] == 'E') {
        printf("// Thanks for playing!!! //");
    }
}

void initMap(MATRIKS *Map) {
  BacaMATRIKSTxt(Map, 10, 20, "./map1.txt");
}

void initPosisi (MATRIKS *MAP, POINT *PPlayer, POINT *POffice, POINT *PAntrian) {
  *PPlayer = getPlayer(*MAP);
  *POffice = getOffice(*MAP);
  *PAntrian = getAntrian(*MAP);
}

void initJam (JAM *JOpen, JAM *JClose) {
  /* ALGORITMA */
  *JOpen = MakeJAM(10, 0, 0);
  *JClose = MakeJAM(22, 0, 0);
}

/* *************** yang lain **************** */

Kata concatNama () {
  Kata K;
  STARTKATA();
  int j=0; int i;
  while (!EndKata) {
    for (i=0; i<CKata.Length; i++) {
      K.TabKata[i+j] = CKata.TabKata[i];
    }
    K.TabKata[i+j] = ' ';
    j+=CKata.Length+1;
    ADVKATA();
  }
  K.Length = j;
  return K;
}

/* *************** MAP **************** */
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

/* *************** DESCRIPTION **************** */
void prepDescription (MATRIKS Map, Kata Nama, int saldo, JAM JCurrent, JAM JOpen, JAM Remaining, Stack S) {
    //KAMUS LOKAL
    //ALGORITMA
    printMap(Map);
    printf("\n");
    printf("Name: ");
    PrintKata(Nama);
    printf("\n");
    printf("Money: %d \n", saldo);
    printf("Current Time: ");
    TulisJAM(JCurrent);
    printf("\n");
    printf("Opening Time: ");
    TulisJAM(JOpen);
    printf("\n");
    printf("Time Remaining: ");
    printf("%d Hour(s) %d Minute(s)", Hour(Remaining), Minute(Remaining));
    printf("\n");
    printf("Total aksi yang dilakukan: %d", JumlahAksi(S));
    printf("\n");
    printf("Total waktu yang dibutuhkan: ");
    printf("%d Hour(s) %d Minute(s)", Hour(CurrentDuration(S)), Minute(CurrentDuration(S)));
    printf("\n");
    printf("Total uang yang dibutuhkan: %d", JumlahBiaya(S));
    printf("\n");
}