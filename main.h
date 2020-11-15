/* File: main.h */
/* *** Definisi MAIN PROGRAM *** */

#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "boolean.h"
#include "./mesin/mesinkar.h"
#include "./mesin/mesinkata.h"
#include "./matriks/matriks.h"
#include "./point/point.h"
#include "./jam/jam.h"
#include "./stack/stack.h"
#include "./array/array.h"

/******* DEKLARASI FUNGSI-FUNGSI UTAMA *******/
void initGame();
/* Menginisiasi mulainya permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan input pilihan di main menu. */

void initMap();
/* Menginisiasi map awal permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan map awal yang terdefinisi di file eksternal. */

void initJam();
/* Menginisiasi jam awal (preparation phase) permainan Willy Wangky's World.
   I.S. Game belum dimulai.
   F.S. Game dimulai dengan jam awal preparation phase permainan Willy Wangky's World. */

void concatNama();
/* Menerima input dan menyatukan kata-kata yang diakuisisi oleh mesin kata ke dalam satu array of character.
   I.S. Input sembarang.
   F.S. Didapat sebuah array of character yang berisi kata-kata terakuisisi dengan dipisahkan spasi. */

/******* FUNGSI-FUNGSI MAP *******/
void printMap (MATRIKS M);
/* Mencetak Map dan Legenda */

#endif