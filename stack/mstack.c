#include <stdio.h>
#include <stdlib.h>
#include "stack.h"
#include "../boolean.h"
#include "../jam/jam.h"

int main() {   
    /* KAMUS */
    Stack S;
    JAM JOpen, JClose;
    JAM MaxDuration;
    aksitype A1;

    /* ALGORITMA */
    Durasi(A1) = MakeJAM(1, 0, 0);

    JOpen = MakeJAM(9, 0, 0);
    JClose = MakeJAM(13, 0, 0);
    MaxDuration = KurangJAM(JClose, JOpen);

    // Inisiasi
    CreateEmpty(&S, MaxDuration);
    TulisJAM(MaxDuration);
    printf("\n");

    // Test Add Aksi
    AddAksi(&S, A1);
    AddAksi(&S, A1);
    AddAksi(&S, A1);
    AddAksi(&S, A1);

    // Test Undo
    Undo(&S, &A1);
    printf("\n");
    TulisJAM(CurrentDuration(S));
    printf("\n");
    return 0;
}