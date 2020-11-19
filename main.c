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
#include "./aksi/prepaksi.h"
//#include "./Graph/graph.h"

// gcc -std=c99 -o main main.c ./aksi/prepaksi.o ./mesin/mesinkar.o ./mesin/mesinkata.o ./matriks/matriks.o ./point/point.o ./jam/jam.o ./stack/stack.o ./array/array.o

/******* FUNGSI MAIN *******/
int main() {
  /* *********** KAMUS UTAMA ********** */
  /********** GRAPH **********/
  //Graph GMain; MakeGMain(&GMain);
  // PrintGraph(GMain);
  Map MapNameActive = 1;
  Map MapNameAsal = 1;
  Map MapNameTujuan;
  
  /* *********** MATRIKS ********** */
  // Map1 > < Map2
  //  v        v
  //  ^        ^
  // Map4 > < Map3
  MATRIKS Map1; BacaMATRIKSTxt(&Map1, 10, 20, "../map1.txt");
  MATRIKS Map2; BacaMATRIKSTxt(&Map2, 10, 20, "../map2.txt");
  MATRIKS Map3; BacaMATRIKSTxt(&Map3, 10, 20, "../map3.txt");
  MATRIKS Map4; BacaMATRIKSTxt(&Map4, 10, 20, "../map4.txt");
  MATRIKS* MapList[4] = {&Map1, &Map2, &Map3, &Map4};
  MATRIKS MapActive;

  /* *********** JAM ************** */
  JAM JOpen;
  JAM JClose;
  JAM MaxDuration;
  JAM JCurrent;
  JAM Remaining;

  /* *********** POINT *********** */
  POINT PPlayer = getPlayer(MapActive);
  POINT POffice = getOffice(MapActive);
  POINT PAntrian = getAntrian(MapActive);
  /*
  POINT PGerbang_Map1_Kanan = getGerbangRight(Map1);
  POINT PGerbang_Map1_Bawah = getGerbangDown(Map1);
  POINT PGerbang_Map2_Kiri = getGerbangLeft(Map2);
  POINT PGerbang_Map2_Bawah = getGerbangDown(Map2);
  POINT PGerbang_Map3_Atas = getGerbangUp(Map3);
  POINT PGerbang_Map3_Kiri = getGerbangLeft(Map3);
  POINT PGerbang_Map4_Atas = getGerbangUp(Map4);
  POINT PGerbang_Map4_Kanan = getGerbangRight(Map4);
  */

  /* *********** Stack Aksi *********** */
  Stack S;

  /* *********** Inventory *********** */
  TabInt Inventory;

  /* *********** Informasi Aksi dan Harga Barang *********** */
  TabInt ListAksi;
  TabInt ListMaterial;

  /* *********** Trash *********** */
  aksitype AksiTypeTrash;

  /* Nama Pemain dan Saldonya (Money) */
  Kata NamaPlayer;
  Kata CurrentPerintah;

  /* *********** ALGORITMA UTAMA ********** */
  //Inisialisasi
  int Money = 10000;
  boolean prep_status = true;
  boolean main_status = false;
  initMap(&Map1);
  initJam(&JOpen,&JClose);
  MaxDuration = KurangJAM(JOpen,JClose);
  initAllList(&Inventory, &ListMaterial, &ListAksi);
  CreateEmpty(&S,MaxDuration);

  //showMap(Map1);
  initGame(&NamaPlayer);
  while (prep_status & !main_status) {
    JCurrent = TambahJAM(JClose, CurrentDuration(S));
    Remaining = KurangJAM(JOpen, JCurrent);
    prepDescription(Map1, NamaPlayer, Money, JCurrent, JOpen, Remaining, S);
    printf("Masukkan Perintah: \n$ ");
    inputPerintah(&CurrentPerintah);
    cekPerintahPrep(CurrentPerintah, &Map1, &S, &AksiTypeTrash, &Inventory, &ListMaterial, &Money, &main_status, &prep_status, &ListAksi);
  }
  return 0;
}

/******* REALISASI FUNGSI-FUNGSI UTAMA *******/
/*********************************************/
/******* INISIALISASI *******/
void initGame(Kata * NamaPlayer) {
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
      *NamaPlayer = concatNama();
  }

    if (CKata.TabKata[0] == 'e' || CKata.TabKata[0] == 'E') {
      printf("// Thanks for playing!!! //");
  }
}

/******* MENANGANI PERINTAH *******/
void inputPerintah(Kata *Perintah){
  // Baca masukan 
  STARTKATA();
  while (!EndKata) {
      ADVKATA();  
  }
  *Perintah = CKata;
}

void cekPerintahPrep(Kata CurrentPerintah, MATRIKS *Map, Stack *S, aksitype *AksiTypeTrash, TabInt *ListMaterial, TabInt *Inventory, int *Money, boolean *prep_status, boolean *main_status, TabInt *ListAksi) {
    JAM durasi;

    if (IsEQKata(CurrentPerintah,StringToKata("w",1))){
      moveUp(Map);
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("a",1))){
      moveLeft(Map);
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("s",1))){
      moveDown(Map);
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("d",1))){
      moveRight(Map);
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("buy",3))){
      MenuBuy(Inventory, ListMaterial, Money);
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("build",5))){
      //
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("upgrade",7))){
      // 
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("undo",4))){
      Undo(S, AksiTypeTrash);
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("execute",7))){
      //
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("main",4))){
      *prep_status = false;
      *main_status = true;
    }
    else if (IsEQKata(CurrentPerintah,StringToKata("exit",4))){
      *prep_status = false;
      *main_status = false;
    }

    durasi = DetikToJAM((long) GetValue(ListAksi, CurrentPerintah));
    //CurrentDuration(*S) = TambahJAM(CurrentDuration(*S), durasi);
}

/******* INISIALISASI *******/
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
  *JOpen = MakeJAM(10, 00, 00);
  *JClose = MakeJAM(22, 00, 00);
}

void initAllList (TabInt *Inventory, TabInt *ListMaterial, TabInt *ListAksi) {
  /* ALGORITMA */
  MakeEmpty(ListMaterial);
  MakeEmpty(Inventory);

  BacaMaterial(ListMaterial);
  BacaMaterial(Inventory);
  SetAllValueX(Inventory, 10);

  BacaAksi(ListAksi);
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
void prepDescription (MATRIKS Map, Kata Nama, int Money, JAM JCurrent, JAM JOpen, JAM Remaining, Stack S) {
    //KAMUS LOKAL
    //ALGORITMA
    printMap(Map);
    printf("\n");
    printf("Name: ");
    PrintKata(Nama);
    printf("\n");
    printf("Money: %d", Money);
    printf("\n");
    printf("Current Time: ");
    TulisJAM(JCurrent);
    printf("\n");
    printf("Opening Time: ");
    TulisJAM(JOpen);
    printf("\n");
    printf("Time Remaining: ");
    printf("%02d Hour(s) %02d Minute(s)", Hour(Remaining), Minute(Remaining));
    printf("\n");
    printf("Total aksi yang dilakukan: %d", JumlahAksi(S));
    printf("\n");
    printf("Total waktu yang dibutuhkan: ");
    printf("%02d Hour(s) %02d Minute(s)", Hour(CurrentDuration(S)), Minute(CurrentDuration(S)));
    printf("\n");
    printf("Total uang yang dibutuhkan: %d", JumlahBiaya(S));
    printf("\n");
}