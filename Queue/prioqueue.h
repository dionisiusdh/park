/* File : prioqueue.h */
/* Definisi ADT Priority Queue dengan representasi array secara eksplisit dan alokasi dinamik */
/* Model Implementasi Versi I */
/* Elemen queue terurut mengecil berdasarkan elemen prio */

#ifndef prioqueue_H
#define prioqueue_H

#include "../boolean.h"
#include "../pengunjung/pengunjung.h"

#define NilQueue -1
/* Konstanta untuk mendefinisikan address tak terdefinisi */

/* Definisi elemen dan address */
typedef struct { int prio;  /* [1..5], prioritas dengan nilai 1..5 (5 adalah prioritas tertinggi) */
                 PENGUNJUNG pengunjung;
                 char nama;
               } queuetype;
typedef int address;   /* indeks tabel */
/* Contoh deklarasi variabel bertype Queue : */
/* Versi I : tabel dinamik, Head dan Tail eksplisit, ukuran disimpan */
typedef struct { queuetype * T;   /* tabel penyimpan elemen */
                 address HEAD;  /* alamat penghapusan */
                 address TAIL;  /* alamat penambahan */
                 int MaxElQueue;     /* Max elemen queue */
               } Queue;
/* Definisi Queue kosong: HEAD=Nil; TAIL=Nil. */

/* ********* AKSES (Selektor) ********* */
/* Jika e adalah infotype dan Q adalah Queue, maka akses elemen : */
#define PrioQueue(e)     (e).prio
#define Pengunjung(e)    (e).pengunjung
#define NamaPengunjung(e) (e).nama         
#define Head(Q)     (Q).HEAD
#define Tail(Q)     (Q).TAIL
#define InfoHead(Q) (Q).T[(Q).HEAD]
#define InfoTail(Q) (Q).T[(Q).TAIL]
#define MaxElQueue(Q)    (Q).MaxElQueue
#define ElmtQueue(Q,i)   (Q).T[(i)]

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q);
/* Mengirim true jika Q kosong: lihat definisi di atas */
boolean IsFullQueue (Queue Q);
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
int NBElmtQueue (Queue Q);
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */

/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max);
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */

/* *** Destruktor *** */
void DeAlokasiQueue (Queue * Q);
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */

/* *** Primitif Add/Delete *** */
void AddQueue (Queue * Q, queuetype X);
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi elemen baru disisipkan pada posisi yang tepat sesuai dengan prioritas. 
        Apabila jumlah wahana yang dimiliki oleh X adalah 0, elemen tidak ditambahkan ke dalam queue */
void DelQueue (Queue * Q, queuetype * X, Kata Wahana);
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */

/* Operasi Tambahan */
void PrintQueue (Queue Q);
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/

int SearchQueue (Queue Q, Kata Wahana);
//Mencari posisi dari elemen pertama queue yang memiliki wahana di dalamnya

void initQueue (Queue *Antrian);
/* Menginisialisasikan antrian wahana */


#endif