/* File : stackt.h */
/* deklarasi stack yang diimplementasi dengan tabel kontigu dan ukuran sama */
/* TOP adalah alamat elemen puncak */
/* Implementasi dalam bahasa C dengan alokasi statik */
#ifndef stack_H
#define stack_H

#include "../boolean.h"
#include "../jam/jam.h"
#include "../mesin/mesinkata.h"

#define NilStack -1
#define MaxEl 100
/* Nil adalah stack dengan elemen kosong . */

typedef struct {
    Kata aksi;  /* Aksi yang akan dilakukan build/upgrade/buy/undo/dll. */
    Kata info_nama_aksi;  /* Wahana yang ingin dibangun/diupgrade, Bahan yang ingin dibeli */
    int info_jumlah_aksi; /* Jumlah untuk apapun */
    int harga; /* Harga dari aksi yang akan dilakukan */
    JAM durasi; /* Durasi aksi */
} aksitype;
typedef int addressStack;   /* indeks tabel */

/* Contoh deklarasi variabel bertype stack dengan ciri TOP : */
/* Versi I : dengan menyimpan tabel dan alamat top secara eksplisit*/
typedef struct { 
  aksitype T[MaxEl]; /* tabel penyimpan elemen */
  addressStack TOP;  /* alamat TOP: elemen puncak */
  int TotalAksi; /* Total jumlah semua aksi dalam stack */
  int TotalBiaya; /* Total seluruh biaya aksi dalam stack */
  JAM CurrentDuration; /* Total durasi aksi-aksi yang ada pada kondisi sekarang */
  JAM MaxDuration; /* Durasi maksimum aksi-aksi yang dapat ditampung stack */
} Stack;
/* Definisi stack S kosong : S.TOP = Nil */
/* Elemen yang dipakai menyimpan nilai Stack T[0]..T[MaxEl-1] */
/* Jika S adalah Stack maka akses elemen : */
   /* S.T[(S.TOP)] untuk mengakses elemen TOP */
   /* S.TOP adalah alamat elemen TOP */

/* Definisi akses dengan Selektor : Set dan Get */
#define Aksi(e) (e).aksi
#define InfoNamaAksi(e) (e).info_nama_aksi
#define InfoJumlahAksi(e) (e).info_jumlah_aksi
#define Harga(e) (e).harga
#define Durasi(e) (e).durasi
#define Top(S) (S).TOP
#define InfoTop(S) (S).T[(S).TOP]
#define CurrentDuration(S) (S).CurrentDuration
#define MaxDuration(S) (S).MaxDuration
#define TotalAksi(S) (S).TotalAksi
#define TotalBiaya(S) (S).TotalBiaya

/* ************ Prototype ************ */
/* *** Konstruktor/Kreator *** */
void CreateEmpty (Stack *S, JAM MaxDuration);
/* I.S. sembarang; */
/* F.S. Membuat sebuah stack S yang kosong berkapasitas MaxEl */
/* jadi indeksnya antara 0.. MaxEl */
/* serta memiliki durasi maksimum MaxDuration */
/* Ciri stack kosong : TOP bernilai Nil, CurrentDuration bernilai JAM(0,0,0) */

/* ************ Predikat Untuk test keadaan KOLEKSI ************ */
boolean IsEmptyStack (Stack S);
/* Mengirim true jika Stack kosong: lihat definisi di atas */
boolean IsFullStack (Stack S);
/* Mengirim true jika tabel penampung nilai elemen stack penuh */

/* ************ Menambahkan sebuah elemen ke Stack ************ */
void Push (Stack * S, aksitype X);
/* Menambahkan X sebagai elemen Stack S. */
/* I.S. S mungkin kosong, tabel penampung elemen stack TIDAK penuh */
/* F.S. X menjadi TOP yang baru,TOP bertambah 1 */

/* ************ Menghapus sebuah elemen Stack ************ */
void Pop (Stack * S, aksitype* X);
/* Menghapus X dari Stack S. */
/* I.S. S  tidak mungkin kosong */
/* F.S. X adalah nilai elemen TOP yang lama, TOP berkurang 1 */

#endif
