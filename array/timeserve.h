/*ADT untuk keep track waktu dari proses serve pelanggan, kapan mereka turun*/

#ifndef TIMESERVE_H
#define TIMESERVE_H

#include "../queue/prioqueue.h"
#include "../Jam/jam.h"
#include "array.h"

typedef struct {
    int time;  /* Waktu pelanggan turun dari wahana dalam detik */
    queuetype value;  /* Harga material */
} ElArrayTime;

typedef struct {
  ElArrayTime TI[100]; /* memori tempat penyimpan elemen (container) */
  int Neff;   /* >=0, banyaknya elemen efektif */
} TabTime;

/* ********** SELEKTOR ********** */
#define NeffTime(T) (T).Neff
#define TI(T) (T).TI
#define ElmtTime(T, i) (T).TI[(i)]
#define Time(E) (E).time
#define Value(E) (E).value

/* ********** KONSTRUKTOR ********** */
void MakeTimeEmpty(TabTime *T);
//Membuat sebuah TabTime baru yang Neff-nya 0
boolean IsEmptyTime(TabTime T);
//Mengecek apakah TabTime kosong / Neff-nya 0 atau tidak
ElArrayTime GetTime(JAM Current, Kata Wahana, queuetype X, TabInt Durasi);
//Mendapatkan dan menyusun ElArrayTime
void AddTime(TabTime *T, ElArrayTime X);
//Menambah sebuah elemen ElArrayTime ke dalam array yang diurutkan berdasarkan value Elemen dari terkecil ke terbesar 
void DellTime(TabTime *T, queuetype *Q);
//Menghapus elemen pertama dari ElArrayTime
boolean PengunjungPulang(queuetype Q);
//Cek apakah wahana yang ingin dikunjungi oleh pengunjung sudah habis

#endif