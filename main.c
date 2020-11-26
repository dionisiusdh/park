#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "main.h"
#include "boolean.h"

/******* FUNGSI MAIN *******/
int main() {
  /* *********** KAMUS UTAMA ********** */
  /********** GRAPH **********/
  Graph GMain; MakeGMain(&GMain);
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
  MATRIKS MapActive; CopyMATRIKS(Map1, &MapActive);

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
  Kata CurrentPerintah,CurrentPerintah1,CurrentPerintah2;
  
  /* Informasi wahana yang ada */
  ListWahana LWahana;

  /* Tree Wahana */
  BinTree Wahana1;
  BinTree Wahana2; 
  BinTree Wahana3;

  /* Antrian */
  Queue Antrian;

  /* *********** ALGORITMA UTAMA ********** */
  //Inisialisasi
  int Money = 10000;
  boolean prep_status = true;
  boolean main_status = false;
  boolean exit_status = false;
  int day = 0;

  initGame(&NamaPlayer);
  initJam(&JOpen,&JClose); MaxDuration = KurangJAM(JOpen,JClose);
  initAllList(&Inventory, &ListMaterial, &ListAksi);
  initWahana(&Wahana1, &Wahana2, &Wahana3);
  initListWahana(&LWahana);
  initAntrian(&Antrian);
  initStack(&S, MaxDuration);

  while (!exit_status) {
    //Inisialisasi day ke-berapa
    day++;
        
    // Membuat copy dari inventory untuk pengecekan
    TabInt InventoryCopy;
    int s;

    /* ALGORITMA */
    // Reset status
    initStack(&S, MaxDuration); // Reset stack preparation phase
    JAM TotalMainDuration = MakeJAM(0,0,0); // Reset jam main phase

    // Buat copy dari inventory
    MakeEmpty(&InventoryCopy);
    NeffArray(InventoryCopy) = NeffArray(Inventory);
    for (s=0; s<NeffArray(InventoryCopy); s++){
        ElmtArray(InventoryCopy,s) = ElmtArray(Inventory,s);
    }
    
    while (prep_status && !main_status) {
      // Jam dan durasi
      JCurrent = TambahJAM(JClose, CurrentDuration(S));
      Remaining = KurangJAM(JCurrent, JOpen);

      // Show description
      printf("Preparation Phase Day %d\n",day);
      prepDescription(MapActive, NamaPlayer, Money, JCurrent, JOpen, Remaining, S);

      // Input perintah
      printf("Masukkan Perintah: \n$ ");
      inputPerintah(&CurrentPerintah);
      cekPerintahPrep(CurrentPerintah, &MapActive, &S, &ListMaterial, &Inventory, &InventoryCopy, &Money, &prep_status, &main_status, &exit_status, &ListAksi, Wahana1, Wahana2, Wahana3, &GMain, &MapNameAsal, &MapNameTujuan, &MapNameActive, MapList, &LWahana, POffice);
    }

    while (!prep_status && main_status) {
      // Jam dan durasi
      JCurrent = TambahJAM(JOpen, TotalMainDuration);
      Remaining = KurangJAM(JCurrent, JClose);
      
      // Show description
      printf("Main Phase Day %d\n",day);
      mainDescription(MapActive, NamaPlayer, Money, Antrian, JCurrent, JClose, Remaining);

      // Input perintah
      inputPerintah(&CurrentPerintah);
      CurrentPerintah = concatNama();
      Bagi2Kata(CurrentPerintah,&CurrentPerintah1,&CurrentPerintah2);
      cekPerintahMain(CurrentPerintah1, CurrentPerintah2, &TotalMainDuration, &MapActive, &ListMaterial, &Inventory, &InventoryCopy, &Money, &prep_status, &main_status, &exit_status, &ListAksi, Wahana1, Wahana2, Wahana3, &GMain, &MapNameAsal, &MapNameTujuan, &MapNameActive, MapList, &LWahana, POffice);
    }
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

void cekPerintahPrep(Kata CurrentPerintah, MATRIKS *Map1, Stack *S, TabInt *ListMaterial, TabInt *Inventory, TabInt *InventoryCopy, int *Money, boolean *prep_status, boolean *main_status, boolean *exit_status, TabInt *ListAksi, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, Graph *GMain, Map *MapNameAsal, Map *MapNameTujuan, Map *MapNameActive, MATRIKS *MapList[4], ListWahana *LWahana, POINT Office) {
    aksitype CurrentAksi;
    aksitype AksiTypeTrash;
    boolean Valid = true;

    int CurrentWahana;
    int CurrentUpgrade;
    char MoveCommand;

    if (IsEQKata(CurrentPerintah,StringToKata("w",1)) || IsEQKata(CurrentPerintah,StringToKata("a",1)) || IsEQKata(CurrentPerintah,StringToKata("s",1)) || IsEQKata(CurrentPerintah,StringToKata("d",1))) {
      Durasi(CurrentAksi) = DetikToJAM(GetValue(ListAksi, CurrentPerintah));
      
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
          moveUp(Map1, Office);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 's') {
          moveDown(Map1, Office);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 'a') {
          moveLeft(Map1, Office);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 'd') {
          moveRight(Map1, Office);
          Player = getPlayer(*Map1);
        }
      } else {
          if (MoveCommand == 'w') {
            moveUp(Map1, Office);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 's') {
            moveDown(Map1, Office);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 'a') {
            moveLeft(Map1, Office);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 'd') {
            moveRight(Map1, Office);
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
          MenuBuild(Map1, InventoryCopy, Wahana1, Wahana2, Wahana3, &CurrentWahana, &Valid, LWahana);
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

            // MenuUpgrade(Map1, InventoryCopy, Wahana1, Wahana2, Wahana3, CurrentWahana, &Valid, &CurrentUpgrade);
            InfoJumlahAksi(CurrentAksi) = CurrentWahana;
            if (Valid) {
              AddAksi(S, CurrentAksi);
            }
          } else {
            printf("Anda sedang tidak berada di dekat wahana.\n");
          }
      } else if (IsEQKata(CurrentPerintah,StringToKata("undo",4))){
        Undo(S, &AksiTypeTrash, LWahana);
      } else if (IsEQKata(CurrentPerintah,StringToKata("execute",7))){
        Execute(Map1, S, Money, Inventory, ListMaterial, LWahana, Wahana1, Wahana2, Wahana3, prep_status, main_status);
      }
      else if (IsEQKata(CurrentPerintah,StringToKata("main",4))){
        *prep_status = false;
        *main_status = true;
      }
      else if (IsEQKata(CurrentPerintah,StringToKata("exit",4))){
        *exit_status = true;
      }
}

void cekPerintahMain(Kata CurrentPerintah, Kata CurrentPerintah2, JAM *TotalMainDuration, MATRIKS *Map1, TabInt *ListMaterial, TabInt *Inventory, TabInt *InventoryCopy, int *Money, boolean *prep_status, boolean *main_status, boolean *exit_status, TabInt *ListAksi, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, Graph *GMain, Map *MapNameAsal, Map *MapNameTujuan, Map *MapNameActive, MATRIKS *MapList[4], ListWahana *LWahana, POINT Office) {
    aksitype CurrentAksi;
    aksitype AksiTypeTrash;

    char MoveCommand;

    if (IsEQKata(CurrentPerintah,StringToKata("w",1)) || IsEQKata(CurrentPerintah,StringToKata("a",1)) || IsEQKata(CurrentPerintah,StringToKata("s",1)) || IsEQKata(CurrentPerintah,StringToKata("d",1))) {
      *TotalMainDuration = TambahJAM(*TotalMainDuration, DetikToJAM(GetValue(ListAksi, CurrentPerintah)));
      
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
          moveUp(Map1, Office);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 's') {
          moveDown(Map1, Office);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 'a') {
          moveLeft(Map1, Office);
          Player = getPlayer(*Map1);
        }
        else if (MoveCommand == 'd') {
          moveRight(Map1, Office);
          Player = getPlayer(*Map1);
        }
      } else {
          if (MoveCommand == 'w') {
            moveUp(Map1, Office);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 's') {
            moveDown(Map1, Office);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 'a') {
            moveLeft(Map1, Office);
            Player = getPlayer(*Map1);
          }
          else if (MoveCommand == 'd') {
            moveRight(Map1, Office);
            Player = getPlayer(*Map1);
          }
        }
      } 
      else if (IsEQKata(CurrentPerintah,StringToKata("serve",5))) {
        *TotalMainDuration = TambahJAM(*TotalMainDuration, DetikToJAM(GetValue(ListAksi, CurrentPerintah)));

        POINT Player = getPlayer(*Map1);
        if (isNearAntrian(*Map1, Player)){
          //Serve()
        }
        else{
          printf("Anda tidak berada di dekat antrian.\n");    
        }
      } 
      else if (IsEQKata(CurrentPerintah,StringToKata("repair",6))) {
        *TotalMainDuration = TambahJAM(*TotalMainDuration, DetikToJAM(GetValue(ListAksi, CurrentPerintah)));

        Repair(Map1, LWahana);
      } 
      else if (IsEQKata(CurrentPerintah,StringToKata("detail",6))) {
        Detail(Map1, *LWahana);
      } 
      else if (IsEQKata(CurrentPerintah,StringToKata("office",6))) {
        MenuOffice(Map1, LWahana);
      } 
      else if (IsEQKata(CurrentPerintah,StringToKata("prepare",7))){
        *prep_status = true;
        *main_status = false;
      }
      else if (IsEQKata(CurrentPerintah,StringToKata("exit",7))){
        *exit_status = true;
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

void initListWahana (ListWahana *LWahana) {
/* Inisiasi ListWahana berisi semua daftar wahana yang ada */

    CreateEmptyListWahana(LWahana);
    /*
    Wahana W1,W2;
    BinTree Wahana1,Wahana2,Wahana3;
    POINT Posisi = MakePOINT(2,3);
    POINT Posisi1 = MakePOINT(4,5);
    List Upgrade,Upgrade1;
    ListWahana L;
    CreateEmptyListLinier(&Upgrade);
    BacaWahana(&Wahana1,&Wahana2,&Wahana3);
    MakeWahana(&W1,Wahana1,Posisi,Upgrade,true);
    MakeWahana(&W2,Wahana2,Posisi1,Upgrade1,true);
    TulisPOINT(GetPosisiWahana(W1));
    CreateEmptyListWahana(&L);
    InsertFirstWahana(&L,W1);
    InsertLastWahana(&L,W2);
    InsertLastWahana(&L,W2);*/
}

void initStack (Stack *S, JAM MaxDuration) {
/* Inisiasi stack kosong dengan durasi maksimum MaxDuration */
  CreateEmpty(S, MaxDuration);
}

void initAntrian (Queue *Antrian) {
/* Inisialisasi Queue, Antrian kosong */
  CreateEmptyQueue(Antrian, 0);
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

void mainDescription (MATRIKS Map, Kata Nama, int Money, Queue Antrian, JAM JCurrent, JAM JClose, JAM Remaining){
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
    printf("Closing Time: ");
    TulisJAM(JClose);
    printf("\n");
    printf("Time Remaining: ");
    printf("%02d Hour(s) %02d Minute(s)", Hour(Remaining), Minute(Remaining));
    printf("\n");
    PrintQueue(Antrian);
}