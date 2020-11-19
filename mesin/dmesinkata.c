#include "mesinkata.h"
#include "mesinkar.h"
#include "../boolean.h"
#include "../array/array.h"
#include <stdio.h>

int main() {
    //KAMUS
    Kata K,K1,K2;
    char (nama[21]) = "Jordan Daniel Joshua";

    //ALGORITMA
    K = StringToKata(nama,21);
    PrintKata(K);
    printf("\n");
    Bagi2Kata(K,&K1,&K2);
    PrintKata(K1);
    printf("\n");
    PrintKata(K2);
    printf("\n");
    return 0;
}