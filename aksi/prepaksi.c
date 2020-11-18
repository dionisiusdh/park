#include <stdio.h>
#include "prepaksi.h"

void Buy(TabInt *Material){
/* I.S. Terdapat File Eksternal Material. */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
    //KAMUS
    // int i;
    // Kata bahan,jumlah,jenis;
    // //ALGORITMA
    // printf("Ingin membeli apa?\n");
    // printf("List: \n");
    // for (i=0; (i<NeffArray(*Material)); i++){
    //     printf("    - ");
    //     PrintKata(Nama(ElmtArray(*Material,i)));
    //     printf("\n");
    // }
    // printf("$ ");
    // STARTKATA();
    // while (!EndKata){
    //   ADVKATA();  
    // }
    // bahan = CKata;
}

/* ************ FUNGSI-FUNGSI PROGRAM ************ */
void Undo (Stack * S, aksitype *X) {
/* Melakukan undo dengan pop elemen dari stack */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (!IsEmptyStack(*S)) {
        Pop(S, X);
        CurrentDuration(*S) = KurangJAM(CurrentDuration(*S), Durasi(*X));
        printf("Berhasil undo.");
    } else {
        printf("Anda belum memasukkan aksi apapun.");
    }
}

void Execute(Stack *S, int *Money, TabInt *Bahan){
/* I.S. Terdapat stack perintah sembarang yang mungkin kosong */
/* F.S. Semua perintah dijalankan satu per satu dari top hingga stack kosong, 
        kemudian fase berubah dari preparation ke main*/
}

void Main(Stack *S){
/* I.S. Execute tidak dijalankan */
/* F.S. Stack Kosong dan Memulai Main Phase */
}

void AddAksi (Stack *S, aksitype X) {
/* Menambahkan aksi ke dalam stack aksi */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    if (!IsFullStack(*S)) {
        Push(S, X);
        CurrentDuration(*S) = TambahJAM(CurrentDuration(*S), Durasi(X));
        printf("Berhasil menambahkan aksi.");
    } else {
        printf("Anda tidak memiliki durasi yang cukup.");
    }
}

int JumlahAksi(Stack S){
    //KAMUS
    int jumlah = 0;
    aksitype X;
    //ALGORITMA
    while (!IsEmptyStack(S)){
        Pop(&S,&X);
        jumlah += 1;
    }
    return jumlah;
}

int JumlahBiaya (Stack S) {
    //KAMUS
    int biaya = 0;
    aksitype X;
    //ALGORITMA
    while (!IsEmptyStack(S)){
        biaya += Harga(InfoTop(S));
        Pop(&S,&X);
    }
    return biaya;
}