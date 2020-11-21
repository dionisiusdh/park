/* File: stackt.c */
/* *** Body ADT stackt *** */

#include <stdio.h>
#include "stack.h"
#include "../boolean.h"
#include "../jam/jam.h"
#include "../mesin/mesinkata.h"
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S, JAM MaxDuration){
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* serta memiliki durasi maksimum MaxDuration */
/* Ciri stack kosong : TOP berNilStackai NilStack, CurrentDuration berNilStackai JAM(0,0,0) */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    Top(*S) = NilStack;
    CurrentDuration(*S) = MakeJAM(0,0,0);
    MaxDuration(*S) = MaxDuration;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S){
/* Mengirim true jika Stack kosong: lihat definisi di atas */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return (Top(S) == NilStack && JEQ(CurrentDuration(S), MakeJAM(0,0,0)));
}
boolean IsFullStack (Stack S){
/* Mengirim true jika tabel penampung NilStackai elemen stack penuh */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return (Top(S) == (MaxEl - 1) || JGT(CurrentDuration(S), MaxDuration(S)) || JEQ(CurrentDuration(S), MaxDuration(S)));
}
/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, aksitype X){
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1, CurrenDuration bertambah sebanyak Durasi(X) */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    Top(*S)++;
    InfoTop(*S) = X;
}

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, aksitype * X){
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah NilStackai elemen TOP yang lama, TOP berkurang 1 */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    *X = InfoTop(*S);
    Top(*S)--;
}