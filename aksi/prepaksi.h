/* MODUL AKSI PREPARATION */

#ifndef PREPAKSI_H
#define PREPAKSI_H

#include "../boolean.h"
#include "../array/array.h"
#include "../mesin/mesinkar.h"
#include "../mesin/mesinkata.h"
#include "../Tree/bintree.h"
#include "../stack/stack.h"
#include "../Jam/jam.h"
#include "../matriks/matriks.h"
#include "../point/point.h"
#include "../wahana/wahana.h"
#include "../pengunjung/pengunjung.h"
#include "../list-linier/listlinier.h"

/* ********** MENU ********** */
/* *********** BUY ***********  */
void MenuBuy(TabInt *Inventory, TabInt *ListMaterial, int *Money, aksitype *CurrentAksi, boolean *Valid);
/* I.S. Terdapat File Eksternal Material.txt */
/* F.S. Menampilkan Daftar Material yang dapat dibeli ke layar, menerima input jumlah material yang dibeli
        Apabila uang mencukupi, masukkan perintah eksekusi ke dalam stack. Apabila uang tidak cukup atau 
        waktu yang tersedia tidak cukup, menampilkan error ke layar (Memakan Waktu)  */

void Buy(TabInt *Inventory, TabInt *ListMaterial, Kata NamaBarang, int JumlahBarang);
/* Membeli barang. Menambahkan NamaBarang pada TempInventory sebanyak JumlahBarang */
/* Mengurangi money dengan nilai total harga material dikali JumlahBarang */

/* *********** BUILD ***********  */
void MenuBuild(MATRIKS *Map, TabInt *Inventory, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, int *CurrentWahana, boolean *Valid, ListWahana *LWahana);
/* I.S. Terdapat file eksternal wahana.txt yang memberi info bahan bangunan yang dibutuhkan */
/* F.S. Menampilkan ingin membangun apa kemudian meminta masukan dari pemain akan wahana apa yang hendak
        dibangun kemudian akan menyimpan perintah bangun ke dalam stack yang akan dijalankan saat execute.
        Apabila bahan bangunan tidak cukup atau waktu tidak cukup, maka akan ditampilkan error (Memakan Waktu) */

void Build(MATRIKS *Map, TabInt *Inventory, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, int CurrentWahana);

/* *********** UPGRADE ***********  */
void MenuUpgrade(TabInt *Inventory, ListWahana CurrentDataWahana, ListWahana *LUpgrade, POINT Player, Map CurrentMap, boolean *Valid);
/* I.S. Terdapat file eksternal wahana.txt yang memberi info bahan bangunan dan uang yang dibutuhkan*/
/* F.S. Menampilkan ingin upgrade apa kemudian meminta masukan dari pemain akan wahana apa yang hendak
        di-upgrade kemudian akan menyimpan perintah upgrade ke dalam stack yang akan dijalankan saat execute.
        Apabila bahan bangunan tidak cukup atau waktu tidak cukup atau uang tidak cukup, maka akan ditampilkan error (Memakan Waktu) */

void Upgrade(MATRIKS *Map, TabInt *Inventory, ListWahana *LUpgrade, ListWahana *LWahana);
/* I.S. Pemain berada di sekitar wahana yang dapat di-upgrade */
/* F.S. Menampikan daftar upgrade yang mungkin untuk wahana tersebut ke layar. Apabila material yang dimiliki tidak cukup
atau waktu tidak cukup, maka akan menampilkan error ke layar pengguna. Apabila kedua syarat (waktu dan material) terpenuhi,
maka akan memasukkan perintah eksekusi ke dalam stack (Memakan Waktu) */

/* *********** UNDO AND EXECUTE ***********  */
void Undo (Stack * S, aksitype *X, MATRIKS *Map, ListWahana *LWahana, ListWahana *LUpgrade);
/* I.S. Terdapat stack perintah sembarang, T mungkin kosong */
/* F.S. Top stack perintah T telah di pop (Current top hilang, perintah paling atas pada stack menjadi new top),
        apabila I.S. kosong maka tidak dilakukan apa-apa (TidakMemakan Waktu) */

void Execute(MATRIKS *Map, Stack *S, int *Money, TabInt *Inventory, TabInt *ListMaterial, ListWahana *LWahana, ListWahana *LUpgrade, BinTree Wahana1, BinTree Wahana2, BinTree Wahana3, boolean *prep_status, boolean *main_status);
/* I.S. Terdapat stack perintah sembarang yang mungkin kosong */
/* F.S. Semua perintah dijalankan satu per satu dari top hingga stack kosong, 
        kemudian fase berubah dari preparation ke main*/

void Main(MATRIKS *Map, Stack *S);
/* I.S. Execute tidak dijalankan */
/* F.S. Stack Kosong dan Memulai Main Phase */

/* ************ FUNGSI STACK ************ */
/* Melakukan undo dengan pop elemen dari stack */
void AddAksi (Stack *S, aksitype X);
/* Menambahkan aksi ke dalam stack aksi */

int JumlahAksi(Stack S);
/* Mengembalikan jumlah aksi di dalam stack */

int JumlahBiaya(Stack S);
/*Mengembalikan jumlah dari biaya di dalam stack*/

#endif