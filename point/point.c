/* File: point.c */
/* *** Realisasi ABSTRACT DATA TYPE POINT *** */

#include "point.h"
#include "../boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/* *** REALISASI PROTOTIPE PRIMITIF *** */
/* *** Konstruktor membentuk POINT *** */
POINT MakePOINT (int X, int Y){
/* Membentuk sebuah POINT dari komponen-komponennya */
    // KAMUS LOKAL
    POINT P;
    // ALGORITMA
    Absis(P) = X;
    Ordinat(P) = Y;
    return P;
}

/* *** Kelompok operasi relasional terhadap POINT *** */
boolean EQ (POINT P1, POINT P2){
/* Mengirimkan true jika P1 = P2 : absis dan ordinatnya sama */
    // KAMUS LOKAL
    // ALGORITMA
    return ((Absis(P1)==Absis(P2)) && (Ordinat(P1)==Ordinat(P2)));
}
boolean NEQ (POINT P1, POINT P2){
/* Mengirimkan true jika P1 tidak sama dengan P2 */
    // KAMUS LOKAL
    // ALGORITMA
    return ((Absis(P1)!=Absis(P2)) || (Ordinat(P1)!=Ordinat(P2)));
}

/* ******HANYA UNTUK TESTING ****** */
/* *** KELOMPOK Interaksi dengan I/O device, BACA/TULIS  *** */
void BacaPOINT (POINT *P){
/* Membaca nilai absis dan ordinat dari keyboard dan membentuk
   POINT P berdasarkan dari nilai absis dan ordinat tersebut */
/* Komponen X dan Y dibaca dalam 1 baris, dipisahkan 1 buah spasi */
/* Contoh: 1 2
   akan membentuk POINT <1,2> */
/* I.S. Sembarang */
/* F.S. P terdefinisi */
    // KAMUS LOKAL
    int A,B;
    // ALGORITMA
    scanf("%d",&A);
    scanf("%d",&B);
    *P = MakePOINT(A,B);
}
void TulisPOINT (POINT P){
/* Nilai P ditulis ke layar dengan format "(X,Y)"
   tanpa spasi, enter, atau karakter lain di depan, belakang,
   atau di antaranya
   Output X dan Y harus dituliskan dalam bilangan riil dengan 2 angka di belakang koma.
*/
/* I.S. P terdefinisi */
/* F.S. P tertulis di layar dengan format "(X,Y)" */
    // KAMUS LOKAL
    // ALGORITMA
    printf("(%d,%d)",Absis(P),Ordinat(P));
}