#include "wahana.h"

// gcc -std=c99 -o dwahana dwahana.c wahana.o ../mesin/mesinkata.o ../mesin/mesinkar.o ../Tree/bintree.o ../point/point.o ../list-linier/listlinier.o

int main(){
    Wahana W1,W2;
    BinTree Wahana1,Wahana2,Wahana3;
    POINT Posisi = MakePOINT(2,3);
    POINT Posisi1 = MakePOINT(4,5);
    List Upgrade,Upgrade1;
    ListWahana L;
    CreateEmptyListLinier(&Upgrade);
    BacaWahana(&Wahana1,&Wahana2,&Wahana3);
    MakeWahana(&W1,Wahana1,Posisi,Upgrade,true);
    MakeWahana(&W2,Wahana2,Posisi1,Upgrade1,true);
    TulisPOINT(GetPosisiWahana(W1));
    CreateEmptyListWahana(&L);
    InsertFirstWahana(&L,W1);
    InsertLastWahana(&L,W2);
    InsertLastWahana(&L,W2);
    DeleteWahana(&L, W2);
    printf("test\n");
    PrintListWahana(L);
    return 0;
}

// gcc -std=c99 -o dwahana dwahana.c ./wahana.o ../mesin/mesinkata.o ../array/array.o ../mesin/mesinkar.o ../Tree/bintree.o ../stack/stack.o ../jam/jam.o ../matriks/matriks.o ../point/point.o ../Graph/graph.o ../list-linier/listlinier.o