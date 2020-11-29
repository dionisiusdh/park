/* MODUL ADT Wahana (ADT Tambahan) */
/* Berisi definisi dan semua primitif pemrosesan wahana */

#ifndef ADTWAHANA_H
#define ADTWAHANA_H

#include <stdio.h>
#include <stdlib.h>
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
    BinTree datawahana;         /* Berisi datawahana berjenis wahanatype dari bintree.h */
    POINT posisiwahana;         /* Berisi posisi wahana dalam bentuk (X,Y) dari point.h */
    List historyupgrade;        /* Digunakan untuk melakukan tracking terhadap status upgrade wahana. Menggunakan list linier */
    boolean statuswahana;       /* Status wahana apakah sedang rusak (false) atau tidak (true) */
    int mapwahana;              /* Wahana berada di map berapa */
} Wahana;

typedef struct tElmtlistWahana *addressWahana;
typedef struct tElmtlistWahana { 
	Wahana infoWahana; 
	addressWahana nextWahana;
} ElmtListWahana;

typedef struct {
	addressWahana FirstWahana;
} ListWahana;

/* Indeks yang digunakan [IdxMin..MaxEl-1] */
/* ********** SELEKTOR ********** */
#define DeskripsiWahana(W) (W).datawahana
#define PosisiWahana(W) (W).posisiwahana
#define HistoryWahana(W) (W).historyupgrade
#define StatusWahana(W) (W).statuswahana
#define MapWahana(W) (W).mapwahana

#define InfoWahana(P) (P)->infoWahana
#define NextWahana(P) (P)->nextWahana
#define FirstWahana(L) ((L).FirstWahana)

/* ^^^^^^^^^^ WAHANA ^^^^^^^^^^^ */

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create Wahana Baru  */
void MakeWahana(Wahana *W, BinTree datawahana, POINT posisiwahana, List historyupgrade, boolean statuswahana, int mapwahana);
/* I.S. W, datawahana, posisiwahana, dan historyupgrade sudah terdefinisi */
/* F.S. Wahana W terbentuk */

/* ********** GETTER ********** */
BinTree GetDataWahana(Wahana W);
/* Sebuah Getter untuk mengembalikan data wahana dalam bentuk wahanatype */

POINT GetPosisiWahana(Wahana W);
/* Sebuah Getter untuk mengembalikan posisi wahana dalam bentuk POINT */

List GetHistoryWahana(Wahana W);
/* Sebuah Getter untuk mengembalikan history upgrade wahana dalam bentuk List */

boolean GetStatusWahana(Wahana W);
/* Sebuah Getter untuk mengembalikan status wahana dalam bentuk boolean */

boolean GetStatusNamaWahana(ListWahana *LWahana, Kata NamaWahana);
/* Mengubah status wahana dalam bentuk boolean berdasarkan nama wahana */

int GetMapWahana(Wahana W);
/* Sebuah Getter untuk mengembalikan nomor wahana dalam bentuk integer */

ListWahana GetWahanaNearPlayer (ListWahana L, POINT P, int CurrentMap);
/* Mengembalikan ListWahana yang ada di sekitar Player */

Wahana GetInfoWahanaAtTitik (ListWahana L, POINT P);
/* Mengambil informasi wahana dari list wahana pada titik P */

/* ********** SETTER ********** */
void SetDataWahana(Wahana *W, BinTree X);
/* Mengubah attribut datawahana pada W menjadi X */

void SetPosisiWahana(Wahana *W, POINT X);
/* Mengubah attribut posisi pada W menjadi X */

void SetHistoryWahana(Wahana *W, List X);
/* Mengubah attribut historyupgrade pada W menjadi X */

void SetStatusWahana(Wahana *W, boolean X);
/* Mengubah status wahana dalam bentuk boolean */

void SetStatusNamaWahana(ListWahana *LWahana, Kata NamaWahana, boolean X);
/* Mengubah status wahana dalam bentuk boolean berdasarkan nama wahana */

void SetMapWahana(Wahana *W, int X);
/* Mengubah map wahana dalam bentuk integer */

/* ^^^^^^^^^^ LIST WAHANA ^^^^^^^^^^^ */
/* ********** KONSTRUKTOR ********** */
boolean IsEmptyListWahana (ListWahana L);
/* Mengirim true jika list wahana kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyListWahana (ListWahana *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list wahana kosong */

/****************** Manajemen Memori ******************/
addressWahana AlokasiWahana (Wahana W);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiWahana (addressWahana *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** MENGENALI APAKAH 2 WAHANA SAMA ******************/
boolean IsWahanaSama (Wahana W1, Wahana W2);
/* Mengembalikan true apabila Wahana W1 = W2, yaitu wahanatype W1 = wahanatype W2, Posisi W1 = Posisi W2, History W1 = History W2. */

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
addressWahana SearchWahana (ListWahana L, Wahana W);
/* Mencari apakah ada elemen list dengan info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */

boolean SearchPosisiWahana (ListWahana L, POINT P);
/* Mencari apakah ada Wahana yang menempati Posisi P*/
/* Jika ada, mengirimkan true. */
/* Jika tidak ada, mengirimkan false */

void InsertFirstWahana (ListWahana *L, Wahana W);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */

void InsertAfterWahana (ListWahana *L, addressWahana P, addressWahana Prec);
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */

void InsertLastWahana (ListWahana *L, Wahana W);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void DelFirstWahana (ListWahana *L, addressWahana *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */


void DelAfterWahana (ListWahana *L, addressWahana *Pdel, addressWahana Prec);
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */ 

void DeleteWahana (ListWahana *L, Wahana W);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

void DeleteWahanaByPosition (ListWahana *L, POINT P, int MapWahana);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

void DelLastWahana (ListWahana *L, addressWahana *P);
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */

void PrintListWahana (ListWahana L);
/* I.S. ListWahana L terdefinisi */
/* F.S. Menampilkan List Wahana dalam format : [(<NamaWahana>,<PosisiWahana>)]  */

void PrintHistoryUpgradeWahana (Wahana W);
/* I.S. ListWahana L terdefinisi */
/* F.S. Menampilkan List Wahana dalam format : <NamaWahana> -> <NamaWahana2> */

void PrintNamaUpgradeWahana (ListWahana AvailableWahanas);
/* I.S. ListWahana AvailableWahanas terdefinisi dan mungkin kosong*/
/* Menampilkan List Nama Upgrade Wahana yang bisa dibangun ke Layar apabila AvailableWahanas 
(Wahana yang sudah terbuild dan belum terupgrade di sekitar pemain)*/

void PrintOpsiUpgradeWahana (BinTree UpgradeWahana);
/* Menampilkan List Nama Upgrade Wahana yang bisa dibangun ke Layar */

addressWahana GetWahanaByIndex (ListWahana L, int i);
/* Mengambil Wahana pada ListWahana L dengan index i (index pertama = 0) */

addressWahana GetAddressByWahana (ListWahana L, Wahana W);
/* Mengembalikan address dari Wahana W di dalam ListWahana */

boolean BrokenRandomizer ();
/* Menghasilkan true or false secara acak untuk membuat sebuah wahana rusak, jika true, wahana akan rusak */
/* 20% Wahana akan rusak */

void AddMoney(ListWahana L,int *Money, Kata NamaWahana);
/*Menambahkan uang dengan biaya dari wahana*/

void PrintWahanaRusak(ListWahana L);
/*Mencetak wahana-wahana apa saja yang rusak*/

#endif
