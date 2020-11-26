#include "pengunjung.h"
#include "../boolean.h"

int main() {
    /* KAMUS */
    PENGUNJUNG P;

    /* ALGORITMA */
    MakePENGUNJUNG(&P, 2);
    GetRandomWahana(&P, 3);
    TulisWahana(P);
    
    return 0;
}