/* MODUL AKSI */

#ifndef AKSI_H
#define AKSI_H

#include "../boolean.h"
#include "../mesin/mesinkata.h"
#include "../array/array.h"
#include "../stack/stack.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MenuBuy(TabInt *ListMaterial, int *Money);
/* I.S. Terdapat File Eksternal Material.txt */
/* F.S. Menampilkan Daftar Material yang dapat dibeli ke layar, menerima input jumlah material yang dibeli
        Apabila uang mencukupi, masukkan perintah eksekusi ke dalam stack. Apabila uang tidak cukup atau 
        waktu yang tersedia tidak cukup, menampilkan error ke layar (Memakan Waktu)  */

void Buy(TabInt *ListMaterial, int *Money, Kata NamaBarang, int JumlahBarang);
/* Membeli barang. Menambahkan NamaBarang pada TempInventory sebanyak JumlahBarang */
/* Mengurangi money dengan nilai total harga material dikali JumlahBarang */

void Build(TabInt *T);
/* I.S. Terdapat file eksternal wahana.txt yang memberi info bahan bangunan yang dibutuhkan */
/* F.S. Menampilkan ingin membangun apa kemudian meminta masukan dari pemain akan wahana apa yang hendak
        dibangun kemudian akan menyimpan perintah bangun ke dalam stack yang akan dijalankan saat execute.
        Apabila bahan bangunan tidak cukup atau waktu tidak cukup, maka akan ditampilkan error (Memakan Waktu) */

void Upgrade(TabInt *T);
/* I.S. Pemain berada di sekitar wahana yang dapat di-upgrade */
/* F.S. Menampikan daftar upgrade yang mungkin untuk wahana tersebut ke layar. Apabila material yang dimiliki tidak cukup
atau waktu tidak cukup, maka akan menampilkan error ke layar pengguna. Apabila kedua syarat (waktu dan material) terpenuhi,
maka akan memasukkan perintah eksekusi ke dalam stack (Memakan Waktu) */

void Undo (Stack * S, aksitype *X);
/* I.S. Terdapat stack perintah sembarang, T mungkin kosong */
/* F.S. Top stack perintah T telah di pop (Current top hilang, perintah paling atas pada stack menjadi new top),
        apabila I.S. kosong maka tidak dilakukan apa-apa (TidakMemakan Waktu) */

void Execute(Stack *S, int *Money, TabInt *Bahan);
/* I.S. Terdapat stack perintah sembarang yang mungkin kosong */
/* F.S. Semua perintah dijalankan satu per satu dari top hingga stack kosong, 
        kemudian fase berubah dari preparation ke main*/

void Main(Stack *S);
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