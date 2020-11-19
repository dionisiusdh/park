#include <stdio.h>
#include "prepaksi.h"

void MenuBuy(TabInt *Inventory, TabInt *ListMaterial, int *Money)
/* I.S. Terdapat File Eksternal Material.txt */
/* F.S. Menampilkan Daftar Material yang dapat dibeli ke layar, menerima input jumlah material yang dibeli
        Apabila uang mencukupi, masukkan perintah eksekusi ke dalam stack. Apabila uang tidak cukup atau 
        waktu yang tersedia tidak cukup, menampilkan error ke layar (Memakan Waktu)  */
{
    /* KAMUS */
    int Harga, TempPrice, JumlahBarang;
    Kata NamaBarang;

    /* ALGORITMA */
    // Menu Buy Material //
    printf("Ingin membeli apa?\n");
    printf("List: \n");
    int i;
    for (i=0; (i<NeffArray(*ListMaterial)); i++){
        PrintKata(Nama(ElmtArray(*ListMaterial,i)));
        printf("   Harga: $%d", Value(ElmtArray(*ListMaterial,i)));
    }
    printf("Petunjuk : Input Dalam Format (<Jumlah Barang> <Nama Barang>); Contoh: 1000 Wood\n");

    STARTKATA();
    JumlahBarang = KataToInteger(CKata);
    ADVKATA();
    NamaBarang = CKata;

    Harga = GetValue(ListMaterial, NamaBarang);
    TempPrice = *Money-(Harga*JumlahBarang);
    if(TempPrice >= 0){
        Buy(Inventory, ListMaterial, Money, NamaBarang, JumlahBarang);
    }
    else{
        // Uang Tidak Cukup
        printf("\nUang Anda tidak memenuhi untuk melakukan pembelian material tersebut.\n");
    }
}

void Buy(TabInt *Inventory, TabInt *ListMaterial, int *Money, Kata NamaBarang, int JumlahBarang){
/* Membeli barang. Menambahkan NamaBarang pada TempInventory sebanyak JumlahBarang */
/* Mengurangi money dengan nilai total harga material dikali JumlahBarang */
    /* KAMUS */
    int CurrentJumlah, NewJumlah;
    int Harga;

    /* ALGORITMA */
    CurrentJumlah = GetValue(Inventory, NamaBarang);
    NewJumlah = CurrentJumlah + JumlahBarang; 
    ChangeValue(Inventory, NamaBarang, NewJumlah);

    Harga = GetValue(ListMaterial, NamaBarang) * JumlahBarang;
    *Money -= Harga;
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
    /* KAMUS LOKAL */
    aksitype X;

    /* ALGORITMA */
    while(Top(*S) != NilStack){
        Pop(S,&X);
    }
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