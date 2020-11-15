/* File: stackt.c */
/* *** Body ADT stackt *** */

#include <stdio.h>
#include "stack.h"
#include "../boolean.h"
#include "../jam/jam.h"

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
/* Ciri stack kosong : TOP bernilai Nil, CurrentDuration bernilai JAM(0,0,0) */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    Top(*S) = Nil;
    CurrentDuration(*S) = MakeJAM(0,0,0);
    MaxDuration(*S) = MaxDuration;
}

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S){
/* Mengirim true jika Stack kosong: lihat definisi di atas */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return (Top(S) == Nil && JEQ(CurrentDuration(S), MakeJAM(0,0,0)));
}
boolean IsFullStack (Stack S){
/* Mengirim true jika tabel penampung nilai elemen stack penuh */
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
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    *X = InfoTop(*S);
    Top(*S)--;
}

/* ************ FUNGSI-FUNGSI PROGRAM ************ */
void Undo (Stack * S, aksitype *X) {
/* Melakukan undo dengan pop elemen dari stack */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (!IsEmptyStack(*S)) {
        Pop(S, X);
        CurrentDuration(*S) = KurangJAM(CurrentDuration(*S), Durasi(*X));
        printf("Berhasil undo.");
    } else {
        printf("Anda belum memasukkan aksi apapun.");
    }
}

void AddAksi (Stack *S, aksitype X) {
/* Menambahkan aksi ke dalam stack aksi */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (!IsFullStack(*S)) {
        Push(S, X);
        CurrentDuration(*S) = TambahJAM(CurrentDuration(*S), Durasi(X));
        printf("Berhasil menambahkan aksi.");
    } else {
        printf("Anda tidak memiliki durasi yang cukup.");
    }
}

/* void Execute (Stack *S, long *Money, List *Bahan){
/* Eksekusi aksi-aksi di dalam stack */
    /* KAMUS LOKAL */
    //aksitype CAksi;

    /* ALGORITMA */
    //Pop(S, &CAksi);
//}

int JumlahAksi(Stack S){
    //KAMUS
    int jumlah = 0;
    aksitype X;
    //ALGORITMA
    while (!IsEmptyStack(S)){
        Pop(&S,&X);
        jumlah += 1;
    }
    return jumlah;
}

int JumlahBiaya (Stack S) {
    //KAMUS
    int biaya = 0;
    aksitype X;
    //ALGORITMA
    while (!IsEmptyStack(S)){
        biaya += Harga(InfoTop(S));
        Pop(&S,&X);
    }
    return biaya;
}