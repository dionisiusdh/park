#include "prioqueuechar.c"
#include "stdio.h"

int main(){
    PrioQueueChar Q,Q2;
    MakeEmpty(&Q,4);
    MakeEmpty(&Q2,3);
    infotype X,X1,X2,X3;
    X.prio = 1;
    X.info = 'j';
    X1.prio = 2;
    X1.info = 'd';
    X2.prio = 2;
    X2.info = 'g';
    X3.prio = 4;
    X3.info = 'o';
    Enqueue(&Q,X2);
    Enqueue(&Q,X);
    Enqueue(&Q,X1);
    Enqueue(&Q,X3);
    PrintPrioQueueChar(Q);
    PrintPrioQueueChar(Q2);
    printf("%c",Elmt(Q,Tail(Q)).info);
    return 0;
}