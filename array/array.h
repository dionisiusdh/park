/* MODUL TABEL INTEGER */
/* Berisi definisi dan semua primitif pemrosesan tabel integer */
/* Penempatan elemen selalu rapat kiri */
/* Versi II : dengan banyaknya elemen didefinisikan secara eksplisit,
   memori tabel dinamik */

#ifndef ARRAY_H
#define ARRAY_H

#include "../boolean.h"
#include "../mesin/mesinkata.h"
#include "../mesin/mesinkar.h"

/*  Kamus Umum */
#define IdxMin 0
/* Indeks minimum array */
#define IdxUndef -1
/* Indeks tak terdefinisi*/

/* Definisi elemen dan koleksi objek */
typedef int IdxType; /* type indeks */
typedef struct {
    Kata nama;  /* Nama material / aksi */
    int value;  /* Harga material / durasi aksi*/
} ElArrayType;
typedef struct
{
  ElArrayType TI[100]; /* memori tempat penyimpan elemen (container) */
  int Neff;   /* >=0, banyaknya elemen efektif */
  int MaxElArray;  /* ukuran elemen */
} TabInt;
/* Indeks yang digunakan [IdxMin..MaxEl-1] */
/* Jika T adalah TabInt, cara deklarasi dan akses: */
/* Deklarasi : T : TabInt */
/* Maka cara akses:
   T.Neff  untuk mengetahui banyaknya elemen
   T.TI    untuk mengakses seluruh nilai elemen tabel
   T.TI[i] untuk mengakses elemen ke-i */
/* Definisi :
  Tabel kosong: T.Neff = 0
  Definisi elemen pertama : T.TI[i] dengan i=0
  Definisi elemen terakhir yang terdefinisi: T.TI[i] dengan i=T.Neff */

/* ********** SELEKTOR ********** */
#define NeffArray(T) (T).Neff
#define TI(T) (T).TI
#define ElmtArray(T, i) (T).TI[(i)]
#define Nama(E) (E).nama
#define Value(E) (E).value

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty(TabInt *T);
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */

void Dealokasi(TabInt *T);
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxEl(T)=0; Neff(T)=0 */

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtArray(TabInt T);
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
int MaxElement(TabInt T);
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
IdxType GetFirstIdx(TabInt T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
IdxType GetLastIdx(TabInt T);
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty(TabInt T);
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
/* *** Test tabel penuh *** */
boolean IsFull(TabInt T);
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi(TabInt *T);
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
void TulisIsiTab(TabInt T);
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */

void AddAsLastEl(TabInt *T, ElArrayType X);
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */

/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl(TabInt *T, ElArrayType *X);
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */

/* ********** COPY ********** */
TabInt CopyTab (TabInt TIn);
/* Mereturn sebuah tabint hasil copy dari TIn */

void SetAllValueZero (TabInt *T);
/* Mengganti semu value dari T menjadi 0 */

void BacaMaterial (TabInt *ListMaterial);
/* Membaca material dan harga material dari file material.txt */

void BacaAksi (TabInt *ListAksi);
/* Membaca material dan harga material dari file material.txt */

#endif
