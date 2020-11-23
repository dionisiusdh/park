/* MODUL AKSI PREPARATION */

#ifndef MAINAKSI_H
#define MAINAKSI_H

#include "../boolean.h"
#include "../array/array.h"
#include "../mesin/mesinkar.h"
#include "../mesin/mesinkata.h"
#include "../Tree/bintree.h"
#include "../stack/stack.h"
#include "../Jam/jam.h"
#include "../matriks/matriks.h"
#include "../point/point.h"

/* ********** MENU ********** */
void MenuMain();
/* I.S. Sembarang */
/* F.S. Menampilkan peta terkini dan menampilkan informasi dasar seperti nama, nominal uang yang dimiliki,
        waktu sekarang, waktu tutup, waktu tersisa hingga waktu tutup, serta pengunjung yang ada pada antrian.  */

/* ********** AKSI ********** */
void Serve();

void Repair();

void Detail();

/* ********** OFFICE ********** */
void MenuOffice();

void Details();

void Report();

void Exit();

#endif