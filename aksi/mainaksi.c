/* MODUL AKSI PREPARATION */

#include <stdio.h>
#include <stdlib.h>
#include "mainaksi.h"

/* ********** MENU ********** */
void MenuMain(){
/* I.S. Sembarang */
/* F.S. Menampilkan peta terkini dan menampilkan informasi dasar seperti nama, nominal uang yang dimiliki,
        waktu sekarang, waktu tutup, waktu tersisa hingga waktu tutup, serta pengunjung yang ada pada antrian.  */

}

/* ********** AKSI ********** */
void Serve() {
    /* KAMUS */

    /* ALGORITMA */

}

void Repair() {
    /* KAMUS */

    /* ALGORITMA */

}

void Detail(MATRIKS *Map, ListWahana LWahana) {
    /* KAMUS */
    POINT NearTitikWahana;
    Wahana NearWahana;

    /* ALGORITMA */
    if (isNearWahana(*Map, getPlayer(*Map))) {
        NearTitikWahana = GetTitikNearWahana(*Map);
        NearWahana = GetNearWahana(Map, LWahana);
        PrintInfoWahana(NearWahana);
    } else {
        printf("Anda sedang tidak berada di dekat wahana");
    }
}

/* ********** OFFICE ********** */
void MenuOffice() {
    /* KAMUS */

    /* ALGORITMA */

}

void DetailsOffice(MATRIKS M) {
    /* KAMUS */

    /* ALGORITMA */

}

void ReportOffice() {
    /* KAMUS */

    /* ALGORITMA */

}

void ExitOffice() {
    /* KAMUS */

    /* ALGORITMA */
}
