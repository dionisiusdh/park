#include <stdio.h>
#include <stdlib.h>
#include "matriks.h"


int main () {
    /***
     * KAMUS:
     * GMain        : Graph     { Graph yang merepresentasikan keterhubungan Map }
     * MapNameActive: Map (int) { Nama Map yang sedang aktif (int) }
     * MapNameAsal  : Map (int) { Nama Map asal (int) }
     * MapNameTujuan: Map (int) { Nama Map tujuan (int) }
     * M1,M2,M3,M4  : MATRIKS   { Matriks yang menyimpan Map 1,2,3,4 }
     * MActive      : MATRIKS   { Matriks yang menyimpan Map yang sedang aktif }
     * MapList      : array of pointer to MATRIKS { mempermudah pemanggilan variabel berdasrakan MapName }
     * Player       : POINT     { Posisi P pada matriks }
     * 
     * ***/
    /*** ADT Graph ***/
    Graph GMain;
    MakeGMain(&GMain);
    
    PrintGraph(GMain);
    Map MapNameActive, MapNameAsal, MapNameTujuan;
    /*** ADT Matriks ***/
    MATRIKS M1, M2, M3, M4, MActive;
    MATRIKS* MapList[4] = {&M1, &M2, &M3, &M4};
    /*** ADT Point ***/
    POINT Player, POffice;

    char MoveCommand;

    /*** Read MATRIKS ***/
    BacaMATRIKSTxt(&M1, 10, 20, "../map1.txt");
    BacaMATRIKSTxt(&M2, 10, 20, "../map2.txt");
    BacaMATRIKSTxt(&M3, 10, 20, "../map3.txt");
    BacaMATRIKSTxt(&M4, 10, 20, "../map4.txt");
    printf("\nM1:\n"); TulisMATRIKS(M1);
    //printf("\nM2:\n"); TulisMATRIKS(M2);
    //printf("\nM3:\n"); TulisMATRIKS(M3);
    //printf("\nM4:\n"); TulisMATRIKS(M4);

    /*** Initialize Map ***/
    CopyMATRIKS(M1, &MActive);
    MapNameActive = 1;
    MapNameAsal = 1;
    //initializePlayerPosition(&MActive);
    Player = getPlayer(MActive);
    POffice = getOffice(MActive);
    printf("posisi player: "); TulisPOINT(Player);printf("\n");
    TulisMATRIKS(MActive);

    /*** EXPLORATION ***/
    do {
      /*** Check Surrounding Location ***/
      if (isNearAntrian(MActive, Player)) {
        /*** What to do when near Antrian ***/
        printf("Player is near by the Antrian\n");
      }
      if (isNearWahana(MActive, Player)) {
        /*** What to do when near Wahana ***/
        printf("Player is near by the Wahana\n");
      }
      if (isInOffice(POffice, Player)) {
        /*** What to do when near Wahana ***/
        printf("Player is in the Office\n");
      }

      /*** Cek apakah Player berpindah Map ***/
      if (isNearGerbang(MActive, Player)) {
        printf("Player is near Gerbang\n");
        printf("Where to move?\n");
        scanf(" %c", &MoveCommand);
        if (isAllowedToChangeMap(MActive, GMain, Player, MapNameAsal, MoveCommand) && IsSrcByReqMoveExist(GMain, MapNameAsal, MoveCommand)) {
          /*** berpindah ke Map lain ***/
          printf("Player is passing through Gerbang\n");
          MapNameTujuan = ReturnMapDest(&GMain, MapNameAsal, MoveCommand);
          printf("passed Evaluating MapNameTujuan %d\n", MapNameTujuan);
          goToOtherMap(&MActive, MapList[MapNameAsal-1], MapList[MapNameTujuan-1], &MapNameActive, &Player, GMain, MoveCommand);
          printf("passed changing Map\n");
          MapNameAsal = MapNameActive;
          //TulisMATRIKS(MActive);
          goto AfterMove;
        }
        goto Move;
      }

      printf("Where to move?\n");
      scanf(" %c", &MoveCommand);

      if (MoveCommand == '?') {
        // Quit Exploring
        break;
      }
      
      /*** Move ***/
      Move:
      if (MoveCommand == 'w') {
        moveUp(&MActive);
        Player = getPlayer(MActive);
      }
      else if (MoveCommand == 's') {
        moveDown(&MActive);
        Player = getPlayer(MActive);
      }
      else if (MoveCommand == 'a') {
        moveLeft(&MActive);
        Player = getPlayer(MActive);
      }
      else if (MoveCommand == 'd') {
        moveRight(&MActive);
        Player = getPlayer(MActive);
      }

      /*** AfterMove ***/
      AfterMove:
      printf("\n\nPosition sesudah: "); TulisPOINT(Player);
      printf("\n");
      TulisMATRIKS(MActive);
    } while (true);
    /*** EXPLORATION END ***/
  return 0;
}