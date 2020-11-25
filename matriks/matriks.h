/* File: matriks.h */
/* *** Definisi ABSTRACT DATA TYPE MATRIKS *** */

#ifndef MATRIKS_H
#define MATRIKS_H

#include "../boolean.h"
#include "../point/point.h"
#include "../Graph/graph.h"
#include "../wahana/wahana.h"
#include "../list-linier/listlinier.h"
#include "../array/array.h"

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
POINT initializePlayerPosition (MATRIKS* M);
/* Menentukan posisi Player pertama kali */

POINT getPlayer (MATRIKS M);
/* Mengirimkan posisi player */
/* Posisi dihitung mulai dari 0,0 */

POINT getOffice (MATRIKS M);
/* Mengirimkan posisi office */
/* Posisi dihitung mulai dari 0,0 */

POINT getAntrian (MATRIKS M);
/* Mengirimkan posisi antrian */
/* Posisi dihitung mulai dari 0,0 */

POINT getGerbangUp (MATRIKS M);
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */
POINT getGerbangDown (MATRIKS M);
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */
POINT getGerbangLeft (MATRIKS M);
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */
POINT getGerbangRight (MATRIKS M);
/* Mengirimkan posisi gerbang */
/* Posisi dihitung mulai dari 0,0 */
POINT getPlayerTransportedPosition (MATRIKS MDest, POINT GDest);
/* Mengirimkan posisi Player setelah berindah Map berdasarkan
   posisi Gerbang pada Map tujuan */


/* ********** Movement Player ********** */
void moveUp (MATRIKS *M, POINT Office);
/* Menggerakan player ke atas 1 tile */

void moveDown (MATRIKS *M, POINT Office);
/* Menggerakan player ke bawah 1 tile */

void moveLeft (MATRIKS *M, POINT Office);
/* Menggerakan player ke kiri 1 tile */

void moveRight (MATRIKS *M, POINT Office);
/* Menggerakan player ke kanan 1 tile */

boolean hitWall (MATRIKS *M, int xNew, int yNew);
/* Cek apakah player menabrak dinding, wahana, atau objek lainnya (Kecuali office) */

void goToOtherMap (MATRIKS* MActive, MATRIKS* MAsal, MATRIKS* MTujuan, Map* ActiveMap, POINT* Player, Graph G, char MoveCommand);
/**
 * I.S. Player bergerak menuju gerbang dan terdapat graf yang menghubungkan Map asal ke tujuan
 * F.S. Jika Gagal, tidak ada yang berubah.
 *      Jika berhasil:
 *      Posisi Player pada Map lama dihapus
 *      Map aktif MActive menjadi Map selanjutnya
 *      Posisi Player pada Map baru bergantung dari posisi gerbang ia keluar
 * Proses:
 *      Menghapus 'P' dari Map Asal
 *      Menempatkan 'P' pada Map Tujuan
 *      Mengubah Map Aktif ke Map tujuan
*/

/* ********** Checker posisi pemain ********** */
boolean isNearWahana (MATRIKS M, POINT P);
/* Cek apakah ada wahana di posisi sekitar player */

boolean isNearAntrian (MATRIKS M, POINT P);
/* Cek apakah ada antrian di posisi sekitar player */

boolean isInOffice (POINT PPlayer, POINT POffice);
/* Cek apakah player sedang berada di posisi office */

boolean isNearGerbang (MATRIKS M, POINT P);
/* Cek apakah ada Gerbang di posisi sekitar player */

boolean isAllowedToChangeMap (MATRIKS M, Graph G, POINT P, Map Src, char MoveCommand);
/* P berada di dekat gerbang.
   Cek berdasarkan input Move apakah Player menuju Gerbang
   Fungsi mengecek pada graph, apakah Player dapat berpindah Map*/

// boolean isInOffice (POINT PPlayer, POINT POffice);
/* Cek apakah player sedang berada di titik office */

void PlaceRancanganWahana (MATRIKS* M, POINT Player);
    /* Menempatkan posisi rancangan pembangunan wahana pada MapActive */
    /* Menempatkan posisi rancangan wahana 'w' (w kecil) di atas, bawah, kiri atau kanan Player */
    /**
     * I.S. Setidaknya masih ada ruang diantar keempat posisi relatif dari Player
     * F.S. Ditambahkan rencana wahana 'w' di M, di atas, bawah, kiri, atau kanan Player
     * Proses: Cek posisi yang tersedia untuk membangun wahana berdasarkan posisi Player
     *         Perhatikan bahwa tidak boleh menmpatkan wahana persis di sebelah gerbang
    */
    // Cek dengan urutan Atas, Bawah, Kiri, Kanan

void UndoBuildWahana (MATRIKS* M);
   /* Menghapus semua rancangan wahana 'w' di M menjadi '-' */

void BuildWahana (MATRIKS* M);
    /* Membangun setiap rancangan wahana 'w' di M menjadi wahana 'W' */

/* **** GETTER INFORMASI WAHANA DI DEKAT PEMAIN**** */
POINT GetTitikNearWahana (MATRIKS M);
/* Mendapatkan titik wahana di sekitar pemain */

POINT GetTitikNearRancanganWahana (MATRIKS M);
/* Mendapatkan titik rancangan wahana di sekitar pemain */

Wahana GetNearWahana (MATRIKS* M, ListWahana Wahana);
/* Mendapatkan informasi wahana di sekitar pemain */

void PrintInfoWahana (Wahana W);
/* Mencetak informasi wahana disekitar pemain sesuai dengan spek */

#endif