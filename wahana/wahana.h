/* MODUL ADT Wahana (ADT Tambahan) */
/* Berisi definisi dan semua primitif pemrosesan wahana */

#ifndef WAHANA_H
#define WAHANA_H

#include "../boolean.h"
#include "../mesin/mesinkata.h"
#include "../mesin/mesinkar.h"
#include "../Tree/bintree.h"
#include "../point/point.h"
#include "../list-linier/listlinier.h"

/*  Kamus Umum */
#define IdxMin 0
/* Indeks minimum array */
#define IdxUndef -1
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int IdxType; /* type indeks */

typedef struct {
    wahanatype datawahana;  /* Berisi datawahana berjenis wahanatype dari bintree.h */
    POINT posisiwahana;  /* Berisi posisi wahana dalam bentuk (X,Y) dari point.h */
    List historyupgrade; /* Digunakan untuk melakukan tracking terhadap status upgrade wahana. Menggunakan list linier */
} Wahana;

/* Indeks yang digunakan [IdxMin..MaxEl-1] */

/* ********** SELEKTOR ********** */
#define Deskripsi(W) (W).datawahana
#define Posisi(W) (W).posisiwahana
#define History(W) (W).historyupgrade

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create Wahana Baru  */
void MakeWahana(Wahana *W, wahanatype datawahana, POINT posisiwahana, List historyupgrade);
/* I.S. W, datawahana, posisiwahana, dan historyupgrade sudah terdefinisi */
/* F.S. Wahana W terbentuk */

/* ********** GETTER ********** */
wahanatype GetDataWahana(Wahana W);
/* Sebuah Getter untuk mengembalikan data wahana dalam bentuk wahanatype */

POINT GetPosisiWahana(Wahana W);
/* Sebuah Getter untuk mengembalikan posisi wahana dalam bentuk POINT */

List GetHistoryWahana(Wahana W);
/* Sebuah Getter untuk mengembalikan history upgrade wahana dalam bentuk List */

/* ********** SETTER ********** */
void SetDataWahana(Wahana *W, wahanatype X);
/* Mengubah attribut datawahana pada W menjadi X */

void SetPosisiWahana(Wahana *W, POINT X);
/* Mengubah attribut posisi pada W menjadi X */

void SetHistoryWahana(Wahana *W, List X);
/* Mengubah attribut historyupgrade pada W menjadi X */

#endif
