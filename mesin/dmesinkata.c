#include "mesinkata.c"
#include "mesinkar.c"
#include "../boolean.h"

int main() {
    Kata K,K1;
    int i;
    K.Length = 0;
    K1.Length = 0;
    for(i=0;i<5;i++){
        K.TabKata[i] = '1';
        K1.TabKata[i] = '1';
        K.Length ++;
        K1.Length ++;
    }
    K1.TabKata[5] = '1';
    K1.Length ++;
    PrintKata(K);
    printf("\n");
    PrintKata(K1);
    printf("\n");
    printf("%d",KataToInteger(K));
    printf("\n");
    printf("%d",IsEQKata(K,K1));
    printf("\n");
    return 0;
}