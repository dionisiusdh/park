#include "prioqueue.h"
#include "../pengunjung/pengunjung.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){
    // KAMUS 
    Queue Q;
    queuetype X,X1,X2,X3;
    TabInt Kapasitas;
    
    // ALGORITMA
    MakeEmpty(&Kapasitas);
    initQueue(&Q, Kapasitas);
    PrintQueue(Q);
    return 0;
}