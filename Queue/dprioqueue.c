#include "prioqueue.h"
#include "../pengunjung/pengunjung.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// gcc -std=c99 -o dprioqueue dprioqueue.c prioqueue.o ../pengunjung/pengunjung.o ../mesin/mesinkata.o ../mesin/mesinkar.o

int main(){
    Queue Q;
    queuetype X,X1,X2,X3;
    initQueue(&Q);
    PrintQueue(Q);
    return 0;
}

/*
    PrioQueue(X) = 1;
    PrioQueue(X1) = 3;
    PrioQueue(X2) = 2;
    PrioQueue(X3) = 4;
    NamaPengunjung(X) = 'A';
    NamaPengunjung(X1) = 'B';
    NamaPengunjung(X2) = 'C';
    NamaPengunjung(X3) = 'D';
    MakePENGUNJUNG(&(Pengunjung(X)), 1);
    MakePENGUNJUNG(&(Pengunjung(X1)), 1);
    MakePENGUNJUNG(&(Pengunjung(X2)), 2);
    MakePENGUNJUNG(&(Pengunjung(X3)), 3);
*/