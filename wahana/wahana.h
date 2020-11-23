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
#include <stdlib.h>

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

typedef struct tElmtlistWahana *address;
typedef struct tElmtlistWahana { 
	Wahana infoWahana;
	address nextWahana;
} ElmtListWahana;

typedef struct {
	address FirstWahana;
} ListWahana;



/* Indeks yang digunakan [IdxMin..MaxEl-1] */
/* ********** SELEKTOR ********** */
#define Deskripsi(W) (W).datawahana
#define Posisi(W) (W).posisiwahana
#define History(W) (W).historyupgrade

#define InfoWahana(P) (P)->infoWahana
#define NextWahana(P) (P)->nextWahana
#define FirstWahana(L) ((L).FirstWahana)

/* ^^^^^^^^^^ WAHANA ^^^^^^^^^^^ */


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

/* ^^^^^^^^^^ LIST WAHANA ^^^^^^^^^^^ */
/* ********** KONSTRUKTOR ********** */
boolean IsEmptyListWahana (ListWahana L);
/* Mengirim true jika list wahana kosong */

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyListWahana (ListWahana *L);
/* I.S. sembarang             */
/* F.S. Terbentuk list wahana kosong */

/****************** Manajemen Memori ******************/
address AlokasiWahana (Wahana W);
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokasiWahana (address *P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian address P */

/****************** MENGENALI APAKAH 2 WAHANA SAMA ******************/
boolean IsWahanaSama (Wahana W1, Wahana W2);
/* Mengembalikan true apabila Wahana W1 = W2, yaitu

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address SearchWahana (ListWahana L, Wahana W);
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

void InsertLastWahana (ListWahana *L, Wahana W);
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */

void DeleteWahana (ListWahana *L, Wahana W);
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan info(P)=X  */
/* Maka P dihapus dari list dan di-dealokasi */
/* Jika tidak ada elemen list dengan info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */

#endif
