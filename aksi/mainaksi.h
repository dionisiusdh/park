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
#include "../wahana/wahana.h"
#include "../pengunjung/pengunjung.h"
#include "../list-linier/listlinier.h"
#include "../Queue/prioqueue.h"
#include "../array/timeserve.h"

/* ********** AKSI ********** */
void Serve (Queue *Q, ListWahana *LWahana, Kata NamaWahana, TabInt *Kapasitas, TabTime *Waktu, TabInt Durasi, JAM Current, int *Money, boolean *serve_gagal, TabInt *MainToday, TabInt *CuanToday, TabInt *MainTotal, TabInt *CuanTotal);

void Repair(MATRIKS *Map, ListWahana *LWahana);

void Detail(MATRIKS *Map, ListWahana LWahana);

/* ********** OFFICE ********** */
void MenuOffice(MATRIKS *Map, ListWahana *LWahana, POINT office, TabInt Inventory, TabInt *MainToday, TabInt *CuanToday, TabInt *MainTotal, TabInt *CuanTotal );

void DetailsOffice(ListWahana *LWahana);

void MaterialOffice (TabInt Inventory);

void ReportOffice(ListWahana *LWahana, TabInt *MainToday, TabInt *CuanToday, TabInt *MainTotal, TabInt *CuanTotal);

#endif