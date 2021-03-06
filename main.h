/* File: main.h */
/* *** Definisi MAIN PROGRAM *** */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"

/* ********* ADT ********* */
#include "./mesin/mesinkar.h"
#include "./mesin/mesinkata.h"
#include "./matriks/matriks.h"
#include "./point/point.h"
#include "./jam/jam.h"
#include "./stack/stack.h"
#include "./array/array.h"
#include "./array/timeserve.h"
#include "./Tree/bintree.h"
#include "./Queue/prioqueue.h"
#include "./array/timeserve.h"
#include "./pengunjung/pengunjung.h"
#include "./wahana/wahana.h"

/* ********* Aksi ********* */
#include "./aksi/prepaksi.h"
#include "./aksi/mainaksi.h"

/******* DEKLARASI FUNGSI-FUNGSI UTAMA *******/

void initGame(Kata * Nama, boolean *exit_status);
/* Menginisiasi mulainya permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan input pilihan di main menu. */

void inputPerintah (Kata *Perintah);
/* Membaca perintah dari user dalam bentuk kata */ 

void cekPerintahPrep(Kata CurrentPerintah, MATRIKS *Map1, Stack *S, TabInt *ListMaterial, TabInt *Inventory, TabInt *StackMaterial, int *Money, boolean *prep_status, boolean *main_status, boolean *exit_status, TabInt *ListAksi, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, Graph *GMain, Map *MapNameAsal, Map *MapNameTujuan, Map *MapNameActive, MATRIKS *MapList[4], ListWahana *LWahana, ListWahana *LUpgrade, POINT Office);
/* Mengecek perintah dari user dalam bentuk kata apabila masukan berupa perintah pada preparation phase */

void cekPerintahMain(Kata CurrentPerintah, Kata CurrentPerintah2, JAM *TotalMainDuration, MATRIKS *Map1, TabInt *ListMaterial, TabInt *Inventory, TabInt *StackMaterial, int *Money, boolean *prep_status, boolean *main_status, boolean *exit_status, TabInt *ListAksi, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, Graph *GMain, Map *MapNameAsal, Map *MapNameTujuan, Map *MapNameActive, MATRIKS *MapList[4], ListWahana *LWahana, POINT Office, Queue *Antrian, TabInt *Kapasitas, TabTime *Waktu, TabInt Durasi, JAM JCurrent, boolean *serve_gagal, TabInt *MainToday, TabInt *CuanToday, TabInt *MainTotal, TabInt *CuanTotal);
/* Mengecek perintah dari user dalam bentuk kata apabila masukan berupa perintah pada main phase */

void initMap();
/* Menginisiasi map awal permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan map awal yang terdefinisi di file eksternal. */

void initJam(JAM *JOpen, JAM *JClose);
/* Menginisiasi jam awal (preparation phase) permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan jam awal preparation phase permainan Willy Wangky's World. */

void initWahana (BinTree *Wahana1, BinTree *Wahana2, BinTree *Wahana3);
/* Menginisiasi wahana Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan map awal yang terdefinisi di file eksternal. */

void initAllList (TabInt *Inventory, TabInt *ListMaterial, TabInt *ListAksi, TabInt *MainTotal, TabInt *CuanTotal);
/*Menginisialisasi Inventory*/

void initListWahana (ListWahana *LWahana, ListWahana *LUpgrade);
/* Inisiasi ListWahana berisi semua daftar wahana yang ada */

void initStack (Stack *S, JAM MaxDuration);
/* Inisiasi stack kosong dengan durasi maksimum MaxDuration */

/******* PROSEDUR DESKRIPSI *******/
void printMap (MATRIKS M);
/* Mencetak Map dan Legenda */

void prepDescription (MATRIKS Map, Kata Nama, int Money, JAM JCurrent, JAM JOpen, JAM Remaining, Stack S);
/* Mencetak Deskripsi Pemain saat preparation phase (Termasuk Mencetak Map dan Legenda) */

void mainDescription (MATRIKS Map, Kata Nama, int Money, Queue Antrian, JAM JCurrent, JAM JClose, JAM Remaining, ListWahana LWahana);
/* Mencetak Deskripsi Pemain saat main phase (Termasuk Mencetak Map dan Legenda) */

#endif