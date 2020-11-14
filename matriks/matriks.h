/* File: matriks.h */
/* *** Definisi ABSTRACT DATA TYPE MATRIKS *** */

#ifndef MATRIKS_H
#define MATRIKS_H

#include "../boolean.h"
#include "../point/point.h"

/* Ukuran minimum dan maksimum baris dan kolom */
#define BrsMin 0
#define BrsMax 10
#define KolMin 0
#define KolMax 20

typedef int indeks; /* indeks baris, kolom */
typedef char ElType; 
typedef struct { 
	ElType Mem[BrsMax+1][KolMax+1];
   int NBrsEff; /* banyaknya/ukuran baris yg terdefinisi */
	int NKolEff; /* banyaknya/ukuran kolom yg terdefinisi */
} MATRIKS;
/* NBrsEff >= 1 dan NKolEff >= 1 */
/* Indeks matriks yang digunakan: [BrsMin..BrsMax][KolMin..KolMax] */
/* Memori matriks yang dipakai selalu di "ujung kiri atas" */

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */              
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M); 
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */

/* *** Selektor *** */
#define NBrsEff(M) (M).NBrsEff
#define NKolEff(M) (M).NKolEff
#define Elmt(M,i,j) (M).Mem[(i)][(j)]

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j);
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */

/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M);
/* Mengirimkan indeks baris terkecil M */
indeks GetFirstIdxKol (MATRIKS M);
/* Mengirimkan indeks kolom terkecil M */
indeks GetLastIdxBrs (MATRIKS M);
/* Mengirimkan indeks baris terbesar M */
indeks GetLastIdxKol (MATRIKS M);
/* Mengirimkan indeks kolom terbesar M */
boolean IsIdxEff (MATRIKS M, indeks i, indeks j);
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
ElType GetElmtDiagonal (MATRIKS M, indeks i);
/* Mengirimkan elemen M(i,i) */

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl);
/* Melakukan assignment MHsl  MIn */

/* ********** KELOMPOK BACA/TULIS ********** */ 
void BacaMATRIKS (MATRIKS * M, int NB, int NK);
/* I.S. IsIdxValid(NB,NK) */ 
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10 
*/
void BacaMATRIKSTxt (MATRIKS * M, int NB, int NK, char* filename);
void TulisMATRIKS (MATRIKS M);
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris 
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M);
/* Mengirimkan banyaknya elemen M */

/* ********** Posisi ********** */
POINT getPlayer (MATRIKS M);
/* Mengirimkan posisi player */
/* Posisi dihitung mulai dari 0,0 */

POINT getOffice (MATRIKS M);
/* Mengirimkan posisi office */
/* Posisi dihitung mulai dari 0,0 */

POINT getAntrian (MATRIKS M);
/* Mengirimkan posisi antrian */
/* Posisi dihitung mulai dari 0,0 */

POINT getGerbang (MATRIKS M);
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */

/* ********** Movement Player ********** */
void moveUp (MATRIKS *M);
/* Menggerakan player ke atas 1 tile */

void moveDown (MATRIKS *M);
/* Menggerakan player ke bawah 1 tile */

void moveLeft (MATRIKS *M);
/* Menggerakan player ke kiri 1 tile */

void moveRight (MATRIKS *M);
/* Menggerakan player ke kanan 1 tile */

boolean hitWall (MATRIKS *M, int xNew, int yNew);
/* Cek apakah player menabrak dinding, wahana, atau objek lainnya (Kecuali office) */

/* ********** Checker posisi pemain ********** */
boolean isNearWahana (MATRIKS M, POINT P);
/* Cek apakah ada wahana di posisi sekitar player */

boolean isNearAntrian (MATRIKS M, POINT P);
/* Cek apakah ada antrian di posisi sekitar player */

boolean isInOffice (POINT PPlayer, POINT POffice);
/* Cek apakah player sedang berada di titik office */

#endif