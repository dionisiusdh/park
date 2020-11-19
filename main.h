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

/* ********* ADT ********* */
#include "./aksi/prepaksi.h"

/******* DEKLARASI FUNGSI-FUNGSI UTAMA *******/


void initGame(Kata * Nama);
/* Menginisiasi mulainya permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan input pilihan di main menu. */

void inputPerintah (Kata *Perintah);
/* Membaca perintah dari user dalam bentuk kata */ 

void cekPerintah(Kata CurrentPerintah, MATRIKS *Map, Stack *S, aksitype *AksiTypeTrash);
/* Mengecek perintah dari user dalam bentuk kata */

void initMap();
/* Menginisiasi map awal permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan map awal yang terdefinisi di file eksternal. */

void initJam(JAM *JOpen, JAM *JClose);
/* Menginisiasi jam awal (preparation phase) permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan jam awal preparation phase permainan Willy Wangky's World. */

/******* PROSEDUR DESKRIPSI *******/
void printMap (MATRIKS M);
/* Mencetak Map dan Legenda */

void prepDescription (MATRIKS M, Kata Nama, int saldo, JAM JCurrent, JAM JOpen, JAM Remaining, Stack S);
/* Mencetak Deskripsi Pemain (Termasuk Mencetak Map dan Legenda) */

#endif