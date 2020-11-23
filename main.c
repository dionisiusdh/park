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
#include "./Tree/bintree.h"

// gcc -std=c99 -o main main.c ./aksi/prepaksi.o ./mesin/mesinkar.o ./mesin/mesinkata.o ./matriks/matriks.o ./point/point.o ./jam/jam.o ./stack/stack.o ./array/array.o

/******* FUNGSI MAIN *******/
int main() {
  /* *********** KAMUS UTAMA ********** */
  /********** GRAPH **********/
  Graph GMain; MakeGMain(&GMain);
  // PrintGraph(GMain);
  Map MapNameActive = 1;
  Map MapNameAsal = 1;
  Map MapNameTujuan;
  
  /* *********** MATRIKS ********** */
  // Map1 > < Map2
  //  v        v
  //  ^        ^
  // Map4 > < Map3
  MATRIKS Map1; BacaMATRIKSTxt(&Map1, 10, 20, "./map1.txt");
  MATRIKS Map2; BacaMATRIKSTxt(&Map2, 10, 20, "./map2.txt");
  MATRIKS Map3; BacaMATRIKSTxt(&Map3, 10, 20, "./map3.txt");
  MATRIKS Map4; BacaMATRIKSTxt(&Map4, 10, 20, "./map4.txt");
  MATRIKS* MapList[4] = {&Map1, &Map2, &Map3, &Map4};
  MATRIKS MapActive;
  CopyMATRIKS(Map1, &MapActive);

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
  
  POINT PGerbang_Map1_Kanan = getGerbangRight(Map1);
  POINT PGerbang_Map1_Bawah = getGerbangDown(Map1);
  POINT PGerbang_Map2_Kiri = getGerbangLeft(Map2);
  POINT PGerbang_Map2_Bawah = getGerbangDown(Map2);
  POINT PGerbang_Map3_Atas = getGerbangUp(Map3);
  POINT PGerbang_Map3_Kiri = getGerbangLeft(Map3);
  POINT PGerbang_Map4_Atas = getGerbangUp(Map4);
  POINT PGerbang_Map4_Kanan = getGerbangRight(Map4);
  
  /* *********** Stack Aksi *********** */
  Stack S;

  /* *********** Inventory *********** */
  TabInt Inventory;

  /* *********** Informasi Aksi dan Harga Barang *********** */
  TabInt ListAksi;
  TabInt ListMaterial; 

  /* Nama Pemain dan Saldonya (Money) */
  Kata NamaPlayer;
  Kata CurrentPerintah;

  /* Tree Wahana */
  BinTree Wahana1;
  BinTree Wahana2; 
  BinTree Wahana3;

  /* *********** ALGORITMA UTAMA ********** */
  //Inisialisasi
  int Money = 10000;
  boolean prep_status = true;
  boolean main_status = false;
  boolean exit_status = false;

  initJam(&JOpen,&JClose);
  MaxDuration = KurangJAM(JOpen,JClose);

  initAllList(&Inventory, &ListMaterial, &ListAksi);
  CreateEmpty(&S,MaxDuration);

  initWahana(&Wahana1, &Wahana2, &Wahana3);
  
  initGame(&NamaPlayer);

  // Wahana buat testing aja, bisa dihapus nnti
  PlaceWahana(&MapActive, getPlayer(MapActive));
  BuildWahana(&MapActive);

  while (!exit_status) {    
    // Membuat copy dari inventory untuk pengecekan
    TabInt InventoryCopy;
    int s;
    
    //ALGORITMA
    MakeEmpty(&InventoryCopy);
    NeffArray(InventoryCopy) = NeffArray(Inventory);
    for (s=0; s<NeffArray(InventoryCopy); s++){
        ElmtArray(InventoryCopy,s) = ElmtArray(Inventory,s);
    }

    while (prep_status && !main_status) {
      // Show description
      JCurrent = TambahJAM(JClose, CurrentDuration(S));
      Remaining = KurangJAM(JCurrent, JOpen);
      prepDescription(MapActive, NamaPlayer, Money, JCurrent, JOpen, Remaining, S);

      // Input perintah
      printf("Masukkan Perintah: \n$ ");
      inputPerintah(&CurrentPerintah);
      cekPerintahPrep(CurrentPerintah, &MapActive, &S, &ListMaterial, &Inventory, &InventoryCopy, &Money, &prep_status, &main_status, &exit_status, &ListAksi, Wahana1, Wahana2, Wahana3, &GMain, &MapNameAsal, &MapNameTujuan, &MapNameActive, MapList);
    }

    while (!prep_status && main_status) {
      printf("Your final inventory: ");
      TulisIsiTab(Inventory);
      printf("\nYour final status\n");
      prepDescription(MapActive, NamaPlayer, Money, JCurrent, JOpen, Remaining, S);
      printf("Selamat datang di main phase yang belum terimplementasikan :\") ");
      break;
    }
    break;
  }

  printf("\nTerima kasih telah bermain.");
  return 0;
}

/******* REALISASI FUNGSI-FUNGSI UTAMA *******/
/*********************************************/
/******* INISIALISASI *******/
void initGame(Kata * NamaPlayer) {
  /**** MAIN MENU ****/
  printf("// Welcome to Willy wangky's fun factory!!//\n// New game / load game / exit? //\n$ ");

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

void cekPerintahPrep(Kata CurrentPerintah, MATRIKS *Map1, Stack *S, TabInt *ListMaterial, TabInt *Inventory, TabInt *InventoryCopy, int *Money, boolean *prep_status, boolean *main_status, boolean *exit_status, TabInt *ListAksi, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, Graph *GMain, Map *MapNameAsal, Map *MapNameTujuan, Map *MapNameActive, MATRIKS *MapList[4]) {
    aksitype CurrentAksi;
    aksitype AksiTypeTrash;
    boolean Valid = true;

    int CurrentWahana;
    int CurrentUpgrade;
    char MoveCommand;

    if (IsEQKata(CurrentPerintah,StringToKata("w",1)) || IsEQKata(CurrentPerintah,StringToKata("a",1)) || IsEQKata(CurrentPerintah,StringToKata("s",1)) || IsEQKata(CurrentPerintah,StringToKata("d",1))) {
      if (IsEQKata(CurrentPerintah, StringToKata("w",1))) {
            MoveCommand = 'w';
          } else if (IsEQKata(CurrentPerintah, StringToKata("a",1))) {
            MoveCommand = 'a';
          } else if (IsEQKata(CurrentPerintah, StringToKata("s",1))) {
            MoveCommand = 's';
          } else if (IsEQKata(CurrentPerintah, StringToKata("d",1))) {
            MoveCommand = 'd';
          }
      
      POINT Player = getPlayer(*Map1);
      
      if (isNearGerbang(*Map1, Player)) {
        if (isAllowedToChangeMap(*Map1, *GMain, Player, *MapNameAsal, MoveCommand) && IsSrcByReqMoveExist(*GMain, *MapNameAsal, MoveCommand)) {
          /*** berpindah ke Map lain ***/
          *MapNameTujuan = ReturnMapDest(GMain, *MapNameAsal, MoveCommand);
          goToOtherMap(Map1, MapList[*MapNameAsal-1], MapList[*MapNameTujuan-1], MapNameActive, &Player, *GMain, MoveCommand);
          *MapNameAsal = *MapNameActive;
        }

        if (MoveCommand == 'w') {
          moveUp(Map1);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 's') {
          moveDown(Map1);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 'a') {
          moveLeft(Map1);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 'd') {
          moveRight(Map1);
          Player = getPlayer(*Map1);
        }
      } else {
          if (MoveCommand == 'w') {
            moveUp(Map1);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 's') {
            moveDown(Map1);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 'a') {
            moveLeft(Map1);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 'd') {
            moveRight(Map1);
            Player = getPlayer(*Map1);
          }
        }
      } else if (IsEQKata(CurrentPerintah,StringToKata("buy",3))) {
          Aksi(CurrentAksi) = StringToKata("buy",3);
          Durasi(CurrentAksi) = DetikToJAM(GetValue(ListAksi, CurrentPerintah));
          MenuBuy(Inventory, ListMaterial, Money, &CurrentAksi, &Valid);
          if (Valid) {
            AddAksi(S, CurrentAksi);
          }
      } else if (IsEQKata(CurrentPerintah,StringToKata("build",5))){
          Aksi(CurrentAksi) = StringToKata("build",5);
          Durasi(CurrentAksi) = DetikToJAM(GetValue(ListAksi, CurrentPerintah));
          MenuBuild(Map1, InventoryCopy, Wahana1, Wahana2, Wahana3, &CurrentWahana, &Valid);
          InfoJumlahAksi(CurrentAksi) = CurrentWahana;
          if (Valid) {
            AddAksi(S, CurrentAksi);
          }
      } else if (IsEQKata(CurrentPerintah,StringToKata("upgrade",7))){
          if (isNearWahana(*Map1, getPlayer(*Map1))) {
            Aksi(CurrentAksi) = StringToKata("upgrade",7);
            Durasi(CurrentAksi) = DetikToJAM(GetValue(ListAksi, CurrentPerintah));
            
            // BUAT DEBUG, NANTI HARUS DI GET OTOMATIS
            CurrentWahana = 1;

            MenuUpgrade(Map1, InventoryCopy, Wahana1, Wahana2, Wahana3, CurrentWahana, &Valid, &CurrentUpgrade);
            InfoJumlahAksi(CurrentAksi) = CurrentWahana;
            if (Valid) {
              AddAksi(S, CurrentAksi);
            }
          } else {
            printf("Anda sedang tidak berada di dekat wahana.\n");
          }
      } else if (IsEQKata(CurrentPerintah,StringToKata("undo",4))){
        Undo(S, &AksiTypeTrash);
      } else if (IsEQKata(CurrentPerintah,StringToKata("execute",7))){
        Execute(Map1, S, Money, Inventory, ListMaterial, Wahana1, Wahana2, Wahana3, prep_status, main_status);
      }
      else if (IsEQKata(CurrentPerintah,StringToKata("main",4))){
        *prep_status = false;
        *main_status = true;
      }
}

/******* INISIALISASI *******/
void initMap1(MATRIKS *Map) {
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

  MakeEmpty(ListAksi);
  BacaAksi(ListAksi);
}

void initWahana (BinTree *Wahana1, BinTree *Wahana2, BinTree *Wahana3) {
  BacaWahana(Wahana1, Wahana2, Wahana3);
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