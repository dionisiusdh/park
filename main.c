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
  TabInt StackMaterial;

  /* *********** Informasi Aksi dan Harga Barang *********** */
  TabInt ListAksi;
  TabInt ListMaterial; 

  /* *********** Informasi Kapasitas, Durasi, dan Penghasilan Wahana *********** */
  TabInt Kapasitas;
  TabInt Durasi;
  TabInt MainTotal;
  TabInt CuanTotal;
  TabInt MainToday;
  TabInt CuanToday;

  /* Waktu Keluarnya Pemain Dari Wahana */
  TabTime Waktu;

  /* Nama Pemain dan Saldonya (Money) */
  Kata NamaPlayer;
  Kata CurrentPerintah,CurrentPerintah1,CurrentPerintah2;
  
  /* Informasi wahana yang ada */
  ListWahana LWahana;
  ListWahana LUpgrade;

  /* Tree Wahana */
  BinTree Wahana1;
  BinTree Wahana2; 
  BinTree Wahana3;

  /* Antrian */
  Queue Antrian;

  /* *********** ALGORITMA UTAMA ********** */
  /* *********** Inisiasi seluruh variabel ********** */
  int Money = 10000;
  boolean prep_status = true;
  boolean main_status = false;
  boolean exit_status = false;
  int day = 0;

  initGame(&NamaPlayer,&exit_status);
  if (!exit_status) {
    initJam(&JOpen,&JClose); MaxDuration = KurangJAM(JOpen,JClose);
    initAllList(&Inventory, &ListMaterial, &ListAksi, &MainTotal, &CuanTotal);
    initWahana(&Wahana1, &Wahana2, &Wahana3);
    initListWahana(&LWahana, &LUpgrade);
    initStack(&S, MaxDuration);
  }

  while (!exit_status) {
    //Inisialisasi day ke-berapa
    day++;

    /* ALGORITMA */
    // Reset status
    initStack(&S, MaxDuration); // Reset stack preparation phase
    JAM TotalMainDuration = MakeJAM(0,0,0); // Reset jam main phase
    MakeEmpty(&StackMaterial); // Reset Material di Stack
    BacaMaterial(&StackMaterial);
    SetAllValueX(&StackMaterial, 0);
    
    while (prep_status && !main_status && !exit_status) {
      // Jam dan durasi
      JCurrent = TambahJAM(JClose, CurrentDuration(S));
      Remaining = KurangJAM(JCurrent, JOpen);

      // Show description
      printf("\nPreparation Phase Day %d\n",day);
      prepDescription(MapActive, NamaPlayer, Money, JCurrent, JOpen, Remaining, S);

      // Input perintah
      printf("\nMasukkan Perintah: \n$ ");
      inputPerintah(&CurrentPerintah);
      cekPerintahPrep(CurrentPerintah, &MapActive, &S, &ListMaterial, &Inventory, &StackMaterial, &Money, &prep_status, &main_status, &exit_status, &ListAksi, Wahana1, Wahana2, Wahana3, &GMain, &MapNameAsal, &MapNameTujuan, &MapNameActive, MapList, &LWahana, &LUpgrade, POffice);
    }

    //Inisialisasi Bagian Serve Main Phase (Kapasitas Wahana, Durasi Wahana, Waktu Selesai Wahana, & Antrian)
    Kapasitas = InitKapasitas(LWahana);
    Durasi = InitDurasi(LWahana);
    MainToday = InitMain(LWahana);
    CuanToday = InitCuan(LWahana);

    initQueue(&Antrian, Kapasitas);
    MakeTimeEmpty(&Waktu);

    while (!prep_status && main_status && !exit_status) {
      // Jam dan durasi
      JCurrent = TambahJAM(JOpen, TotalMainDuration);
      Remaining = KurangJAM(JCurrent, JClose);

      //KAMUS TAMBAHAN
      queuetype X;
      boolean keluar_wahana = true;
      boolean serve_gagal;

      //Cek untuk serve apakah pemain sudah turun dari wahana atau belum
      while (!IsEmptyTime(Waktu) && keluar_wahana){
        if (Time(ElmtTime(Waktu,0)) <= JAMToDetik(JCurrent)){
          DellTime(&Waktu,&X,&Kapasitas);
          if (!PengunjungPulang(X)){
            AddQueue(&Antrian,X);
          }
        }
        else{
          keluar_wahana = false;
        }
      }

      // Show description
      printf("\nMain Phase Day %d\n",day);
      mainDescription(MapActive, NamaPlayer, Money, Antrian, JCurrent, JClose, Remaining,LWahana);

      // Input perintah
      printf("Masukkan Perintah\n$ ");
      CurrentPerintah = concatNama();
      Bagi2Kata(CurrentPerintah,&CurrentPerintah1,&CurrentPerintah2);
      cekPerintahMain(CurrentPerintah1, CurrentPerintah2, &TotalMainDuration, &MapActive, &ListMaterial, &Inventory, &StackMaterial, &Money, &prep_status, &main_status, &exit_status, &ListAksi, Wahana1, Wahana2, Wahana3, &GMain, &MapNameAsal, &MapNameTujuan, &MapNameActive, MapList, &LWahana, POffice,&Antrian,&Kapasitas,&Waktu,Durasi,JCurrent,&serve_gagal,&MainToday,&CuanToday,&MainTotal,&CuanTotal);
    }
  }
  printf("Terima kasih telah bermain.");
  return 0;
}

/******* REALISASI FUNGSI-FUNGSI UTAMA *******/
/*********************************************/
/******* INISIALISASI *******/
void initGame(Kata * NamaPlayer, boolean *exit_status) {
/* Inisialisasi game awal */
  /**** MAIN MENU ****/
  printf("// Welcome to Willy Wangky's Fun Factory!!//\n// New game / load game / exit? //\n$ ");

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
    *exit_status = true;
  }
}

/******* MENANGANI PERINTAH *******/
void inputPerintah(Kata *Perintah){
/* Membaca input masukan dari user */
  // Baca masukan 
  STARTKATA();
  while (!EndKata) {
      ADVKATA();  
  }
  *Perintah = CKata;
}

void cekPerintahPrep(Kata CurrentPerintah, MATRIKS *Map1, Stack *S, TabInt *ListMaterial, TabInt *Inventory, TabInt *StackMaterial, int *Money, boolean *prep_status, boolean *main_status, boolean *exit_status, TabInt *ListAksi, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, Graph *GMain, Map *MapNameAsal, Map *MapNameTujuan, Map *MapNameActive, MATRIKS *MapList[4], ListWahana *LWahana, ListWahana *LUpgrade, POINT Office) {
/* Cek perintah yang dilakukan user pada preparation phase dan menindaklanjutinya */    
    /* KAMUS */
    aksitype CurrentAksi;
    aksitype AksiTypeTrash;
    boolean Valid = true;

    int CurrentWahana;
    int CurrentUpgrade;
    char MoveCommand;

    /* ALGORITMA */
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
          Harga(CurrentAksi) = 0;
          MenuBuild(Map1, *Inventory, StackMaterial, Wahana1, Wahana2, Wahana3, &CurrentWahana, &Valid, LWahana);
          InfoJumlahAksi(CurrentAksi) = CurrentWahana;
          if (Valid) {
            AddAksi(S, CurrentAksi);
          }
      } else if (IsEQKata(CurrentPerintah,StringToKata("upgrade",7))){
          if (isNearWahana(*Map1, getPlayer(*Map1))) {
            Aksi(CurrentAksi) = StringToKata("upgrade",7);
            Durasi(CurrentAksi) = DetikToJAM(GetValue(ListAksi, CurrentPerintah));
            Harga(CurrentAksi) = 0;
            
            CurrentWahana = 1;

            MenuUpgrade(*Inventory, StackMaterial, *LWahana, LUpgrade, getPlayer(*Map1), *MapNameAsal, &Valid);
            InfoJumlahAksi(CurrentAksi) = CurrentWahana;
            if (Valid) {
              AddAksi(S, CurrentAksi);
            }
          } else {
            printf("Anda sedang tidak berada di dekat wahana.\n");
          }
      } else if (IsEQKata(CurrentPerintah,StringToKata("undo",4))){
        Undo(S, &AksiTypeTrash, Map1, LWahana, LUpgrade, StackMaterial);
      } else if (IsEQKata(CurrentPerintah,StringToKata("execute",7))){
        if (isThereWahana(Map1)) {
          Execute(Map1, S, Money, Inventory, ListMaterial, LWahana, LUpgrade, Wahana1, Wahana2, Wahana3, prep_status, main_status);
        } else {
          printf("Bangun wahana terlebih dahulu!\n");
        }
      }
      else if (IsEQKata(CurrentPerintah,StringToKata("main",4))){
        if (isThereWahana(Map1)) {
          Main(Map1, S);
          *prep_status = false;
          *main_status = true;
        } else {
          printf("Bangun wahana terlebih dahulu!\n");
        }
      }
      else if (IsEQKata(CurrentPerintah,StringToKata("exit",4))){
        *exit_status = true;
      } else {
        printf("Masukkan anda tidak valid!\n");
      }
}

void cekPerintahMain(Kata CurrentPerintah, Kata CurrentPerintah2, JAM *TotalMainDuration, MATRIKS *Map1, TabInt *ListMaterial, TabInt *Inventory, TabInt *StackMaterial,int *Money, boolean *prep_status, boolean *main_status, boolean *exit_status, TabInt *ListAksi, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, Graph *GMain, Map *MapNameAsal, Map *MapNameTujuan, Map *MapNameActive, MATRIKS *MapList[4], ListWahana *LWahana, POINT Office, Queue *Antrian, TabInt *Kapasitas, TabTime *Waktu, TabInt Durasi, JAM JCurrent, boolean *serve_gagal, TabInt *MainToday, TabInt *CuanToday, TabInt *MainTotal, TabInt *CuanTotal) {
/* Cek perintah yang dilakukan user pada main phase dan menindaklanjutinya */       
    /* KAMUS */
    aksitype CurrentAksi;
    aksitype AksiTypeTrash;

    char MoveCommand;

    /* ALGORITMA */
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
          /*  ** Berpindah ke Map lain ** */
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
        POINT Player = getPlayer(*Map1);
        if (isNearAntrian(*Map1, Player)){
          Serve(Antrian, LWahana, CurrentPerintah2, Kapasitas, Waktu, Durasi, JCurrent, Money, serve_gagal, MainToday, CuanToday, MainTotal, CuanTotal);
          if (!*(serve_gagal)){
            *TotalMainDuration = TambahJAM(*TotalMainDuration, DetikToJAM(GetValue(ListAksi, CurrentPerintah)));
          }
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
        MenuOffice(Map1, LWahana, Office, *Inventory, MainToday, CuanToday, MainTotal, CuanTotal);
      } 
      else if (IsEQKata(CurrentPerintah,StringToKata("prepare",7))){
        *prep_status = true;
        *main_status = false;
      }
      else if (IsEQKata(CurrentPerintah,StringToKata("exit",4)) || IsEQKata(CurrentPerintah2,StringToKata("exit",4))){
        *exit_status = true;
      } else {
        printf("Masukkan anda tidak valid!\n");
      }
}

/******* INISIALISASI *******/
void initMap1(MATRIKS *Map) {
/* Inisiasi map */
  BacaMATRIKSTxt(Map, 10, 20, "./map1.txt");
}

void initPosisi (MATRIKS *MAP, POINT *PPlayer, POINT *POffice, POINT *PAntrian) {
/* Inisiasi semua posisi */
  *PPlayer = getPlayer(*MAP);
  *POffice = getOffice(*MAP);
  *PAntrian = getAntrian(*MAP);
}

void initJam (JAM *JOpen, JAM *JClose) {
/* Inisiasi semua jam */
  /* ALGORITMA */
  *JOpen = MakeJAM(10, 00, 00);
  *JClose = MakeJAM(22, 00, 00);
}

void initAllList (TabInt *Inventory, TabInt *ListMaterial, TabInt *ListAksi, TabInt *MainTotal, TabInt *CuanTotal) {
/* Inisiasi semua list */
  /* ALGORITMA */
  MakeEmpty(ListMaterial);
  MakeEmpty(Inventory);

  BacaMaterial(ListMaterial);
  BacaMaterial(Inventory);
  SetAllValueX(Inventory, 10);

  MakeEmpty(ListAksi);
  BacaAksi(ListAksi);

  MakeEmpty(MainTotal);
  MakeEmpty(CuanTotal);
}

void initWahana (BinTree *Wahana1, BinTree *Wahana2, BinTree *Wahana3) {
/* Inisiasi semua data tree wahana */
  BacaWahana(Wahana1, Wahana2, Wahana3);
}

void initListWahana (ListWahana *LWahana, ListWahana *LUpgrade) {
/* Inisiasi ListWahana berisi semua daftar wahana yang ada */
    CreateEmptyListWahana(LWahana);
    CreateEmptyListWahana(LUpgrade);
}

void initStack (Stack *S, JAM MaxDuration) {
/* Inisiasi stack kosong dengan durasi maksimum MaxDuration */
  CreateEmpty(S, MaxDuration);
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
/* Mencetak Deskripsi Pemain saat preparation phase (Termasuk Mencetak Map dan Legenda) */
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

void mainDescription (MATRIKS Map, Kata Nama, int Money, Queue Antrian, JAM JCurrent, JAM JClose, JAM Remaining, ListWahana LWahana){
/* Mencetak Deskripsi Pemain saat main phase (Termasuk Mencetak Map dan Legenda) */
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
    PrintWahanaRusak(LWahana);
    printf("\n");
}