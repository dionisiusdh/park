// Realisasi Dari wahana.h

#include "wahana.h"

/* ********** KONSTRUKTOR ********** */
void MakeWahana(Wahana *W, wahanatype datawahana, POINT posisiwahana, List historyupgrade){
    /* KAMUS */

    /* ALGORITMA */
    Deskripsi(*W) = datawahana;
    Posisi(*W) = posisiwahana;
    History(*W) = historyupgrade;
}

/* ********** GETTER ********** */
wahanatype GetDataWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan data wahana dalam bentuk wahanatype */
{
    /* KAMUS */

    /* ALGORITMA */
    return Deskripsi(W);
}

POINT GetPosisiWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan posisi wahana dalam bentuk POINT */
{
    /* KAMUS */

    /* ALGORITMA */
    return Posisi(W);
}

List GetHistoryWahana(Wahana W)
/* Sebuah Getter untuk mengembalikan history upgrade wahana dalam bentuk List */
{
    /* KAMUS */

    /* ALGORITMA */
    return History(W);
}

/* ********** SETTER ********** */
void SetDataWahana(Wahana *W, wahanatype X)
/* Mengubah attribut datawahana pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    Deskripsi(*W) = X;
}

void SetPosisiWahana(Wahana *W, POINT X)
/* Mengubah attribut posisi pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    Posisi(*W) = X;
}

void SetHistoryWahana(Wahana *W, List X)
/* Mengubah attribut historyupgrade pada W menjadi X */
{
    /* KAMUS */

    /* ALGORITMA */
    History(*W) = X;
}