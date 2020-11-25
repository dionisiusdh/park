/* ADT Pohon Biner */
/* Implementasi dengan menggunakan pointer */
/* Penamaan type wahanatype, type addrNode, dan beberapa fungsi disesuikan karena melibatkan modul list rekursif. */

#ifndef _BINTREE_H_
#define _BINTREE_H_

/* Modul lain yang digunakan : */
#include "../boolean.h"
#include "../mesin/mesinkata.h"

#define Nil NULL  /* konstanta Nil sesuai pada modul listrek */

/* *** Definisi Type Pohon Biner *** */
/* typedef int wahanatype; */ /* type wahanatype sesuai pada modul listrek */
typedef struct tNodeWahana *addrNodeWahana;

typedef struct {
   Kata nama;
   int harga;
   int kapasitas;
   int durasi;
   Kata deskripsi;
   int cost_up;
   int mat_up[5];   
} wahanatype;

typedef struct tNodeWahana{
    wahanatype info;
    addrNodeWahana left;
    addrNodeWahana right;
} NodeWahana;

/* Definisi PohonBiner : */
/* Pohon Biner kosong : P = Nil */
typedef addrNodeWahana BinTree;

/* *** PROTOTYPE *** */

/* *** Selektor *** */
#define Akar(P) (P)->info
#define AkarNama(P) (P)->info.nama
#define AkarHarga(P) (P)->info.harga
#define AkarKapasitas(P) (P)->info.kapasitas
#define AkarDurasi(P) (P)->info.durasi
#define AkarDeskripsi(P) (P)->info.deskripsi
#define AkarCostUp(P) (P)->info.cost_up
#define AkarMatUp(P,i) (P)->info.mat_up[(i)]
#define Left(P) (P)->left
#define Right(P) (P)->right
#define WahanaNama(E) (E).nama
#define WahanaHarga(E) (E).harga
#define WahanaKapasitas(E) (E).kapasitas
#define WahanaDurasi(E) (E).durasi
#define WahanaDeskripsi(E) (E).deskripsi
#define WahanaCostUp(E) (E).cost_up
#define WahanaMatUp(E,i) (E).mat_up[(i)]

/* *** Konstruktor *** */
BinTree Tree(wahanatype Akar, BinTree L, BinTree R);
/* Menghasilkan sebuah pohon biner dari A, L, dan R, jika alokasi berhasil */
/* Menghasilkan pohon kosong (Nil) jika alokasi gagal */
void MakeTree(wahanatype Akar, BinTree L, BinTree R, BinTree *P);
/* I.S. Akar, L, R terdefinisi. P Sembarang */
/* F.S. Membentuk pohon P dengan Akar(P)=Akar, Left(P)=L, dan Right(P)=R
   jika alokasi berhasil. P = Nil jika alokasi gagal. */

/* Manajemen Memory */
addrNodeWahana AlokNode(wahanatype X);
/* Mengirimkan addrNode hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka addrNode tidak Nil, dan misalnya menghasilkan P,
  maka Akar(P) = X, Left(P) = Nil, Right(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
void DealokNode(addrNodeWahana P);
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan dealokasi/pengembalian addrNode P */

/* *** Predikat-Predikat Penting *** */
boolean IsTreeEmpty(BinTree P);
/* Mengirimkan true jika P adalah pohon biner kosong */
boolean IsTreeOneElmt(BinTree P);
/* Mengirimkan true jika P adalah pohon biner tidak kosong dan hanya memiliki 1 elemen */
boolean IsUnerLeft(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerleft: hanya mempunyai subpohon kiri */
boolean IsUnerRight(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon unerright: hanya mempunyai subpohon kanan*/
boolean IsBiner(BinTree P);
/* Mengirimkan true jika pohon biner tidak kosong P adalah pohon biner: mempunyai subpohon kiri dan subpohon kanan*/

/* *** Traversal *** */
void PrintPreorder(BinTree P);
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara preorder: akar, pohon kiri, dan pohon kanan.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (A()()) adalah pohon dengan 1 elemen dengan akar A
   (A(B()())(C()())) adalah pohon dengan akar A dan subpohon kiri (B()()) dan subpohon kanan (C()()) */
void PrintInorder(BinTree P);
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara inorder: pohon kiri, akar, dan pohon kanan.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (()A()) adalah pohon dengan 1 elemen dengan akar A
   ((()B())A(()C())) adalah pohon dengan akar A dan subpohon kiri (()B()) dan subpohon kanan (()C()) */
void PrintPostorder(BinTree P);
/* I.S. P terdefinisi */
/* F.S. Semua simpul P sudah dicetak secara postorder: pohon kiri, pohon kanan, dan akar.
   Setiap pohon ditandai dengan tanda kurung buka dan kurung tutup ().
   Pohon kosong ditandai dengan ().
   Tidak ada tambahan karakter apa pun di depan, tengah, atau akhir. */
/* Contoh:
   (()()A) adalah pohon dengan 1 elemen dengan akar A
   ((()()B)(()()C)A) adalah pohon dengan akar A dan subpohon kiri (()()B) dan subpohon kanan (()()C) */
void PrintTree(BinTree P, int h);
/* I.S. P terdefinisi, h adalah jarak indentasi (spasi) */
/* F.S. Semua simpul P sudah ditulis dengan indentasi (spasi) */
/* Penulisan akar selalu pada baris baru (diakhiri newline) */
/* Contoh, jika h = 2: 
1) Pohon preorder: (A()()) akan ditulis sbb:
A
2) Pohon preorder: (A(B()())(C()())) akan ditulis sbb:
A
  B
  C
3) Pohon preorder: (A(B(D()())())(C()(E()()))) akan ditulis sbb:
A
  B
    D
  C
    E
*/

/* *** Fungsi-Fungsi Lain *** */
int NbElmt(BinTree P);
/* Mengirimkan banyaknya elemen (node) pohon biner P */
int NbDaun(BinTree P);
/* Mengirimkan banyaknya daun (node) pohon biner P */
/* Prekondisi: P tidak kosong */
boolean IsSkewLeft(BinTree P);
/* Mengirimkan true jika P adalah pohon condong kiri */
/* Pohon kosong adalah pohon condong kiri */
boolean IsSkewRight(BinTree P);
/* Mengirimkan true jika P adalah pohon condong kanan */
/* Pohon kosong adalah pohon condong kanan */
int Tinggi(BinTree P);
/* Pohon Biner mungkin kosong. Tinggi pohon kosong = 0.
   Mengirim "height" yaitu tinggi dari pohon */

void BacaWahana(BinTree *WahanaTree1, BinTree *WahanaTree2, BinTree *WahanaTree3);
/* Membaca Wahana dan Deskripsinya dari file wahana.txt */

void GetInfoWahana (BinTree Wahana, wahanatype *InfoWahana);
/* Mengambil info wahana dan menyimpan ke dalam Info Wahana */

void PrintNamaWahana (BinTree Wahana1, BinTree Wahana2, BinTree Wahana3);
/* Menampilkan List Nama Wahana yang bisa dibangun ke Layar */

boolean IsWahanaTypeSama (BinTree Wahana1, BinTree Wahana2);
/* Mengembalikan true apabila Wahana1 = Wahana2, dan false apabila tidak */

#endif