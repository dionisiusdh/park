#include <stdio.h>
#include "./prepaksi.h"
#include "../boolean.h"
#include <stdlib.h>
#include "../array/array.h"
#include "../mesin/mesinkar.h"
#include "../mesin/mesinkata.h"
#include "../Tree/bintree.h"
#include "../stack/stack.h"
#include "../Jam/jam.h"
#include "../matriks/matriks.h"
#include "../point/point.h"

int main() {
    TabInt Inven;
    aksitype CurrentAksi;
    int CurrentWahana, CurrentUpgrades;
    boolean cek,valid;
    MakeEmpty(&Inven);
    BinTree W1,W2,W3;
    MATRIKS M1;
    ListWahana LWahana, LUpgrade;
    Wahana WahanaBuilt;
    POINT posisi,posisi2;
    List Upg;
    CreateEmptyListWahana(&LWahana);
    CreateEmptyListWahana(&LUpgrade);
    BacaWahana(&W1,&W2,&W3);
    int money = 5000;
    printf("Initial Money: %d", money);
    BacaMaterial(&Inven);
    SetAllValueX(&Inven, 100);
    TulisIsiTab(Inven);
    printf("\n");
    printf("Initial Inventory:");
    TulisIsiTab(Inven);
    printf("\n");

    TulisIsiTab(Inven);
    posisi = MakePOINT(3,2);
    posisi2 = MakePOINT(3,1);
    MakeWahana(&WahanaBuilt,W1,posisi,Upg,false,1);
    printf("\n");
    InsertLastWahana(&LWahana,WahanaBuilt);
    printf("Wahana: \n");
    PrintListWahana(LWahana);
    return 0;
}