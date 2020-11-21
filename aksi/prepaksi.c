#include <stdio.h>
#include "prepaksi.h"

void MenuBuy(TabInt *Inventory, TabInt *ListMaterial, int *Money, aksitype *CurrentAksi)
/* I.S. Terdapat File Eksternal Material.txt */
/* F.S. Menampilkan Daftar Material yang dapat dibeli ke layar, menerima input jumlah material yang dibeli
        Apabila uang mencukupi, masukkan perintah eksekusi ke dalam stack. Apabila uang tidak cukup atau 
        waktu yang tersedia tidak cukup, menampilkan error ke layar (Memakan Waktu)  */
{
    /* KAMUS */
    int Harga, TempPrice, TempMoney, JumlahBarang;
    Kata NamaBarang;

    /* ALGORITMA */
    // Menu Buy Material //
    printf("Ingin membeli apa?\n");
    printf("List: \n");
    int i;
    for (i=0; (i<NeffArray(*ListMaterial)); i++){
        PrintKata(Nama(ElmtArray(*ListMaterial,i)));
        printf("   Harga: %d", Value(ElmtArray(*ListMaterial,i)));
    }
    printf("\nPetunjuk : Input Dalam Format (<Jumlah Barang> <Nama Barang>); Contoh: 1000 Wood\n");

    STARTKATA();
    JumlahBarang = KataToInteger(CKata);
    ADVKATA();
    NamaBarang = CKata;

    Harga = GetValue(ListMaterial, NamaBarang);
    TempMoney = *Money-(Harga*JumlahBarang);
    TempPrice = Harga*JumlahBarang;
    if(TempMoney >= 0){
        InfoNamaAksi(*CurrentAksi) = NamaBarang;
        InfoJumlahAksi(*CurrentAksi) = JumlahBarang;
        Harga(*CurrentAksi) = TempPrice;
        // Buy(Inventory, ListMaterial, Money, NamaBarang, JumlahBarang);
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
        //CurrentDuration(*S) = KurangJAM(CurrentDuration(*S), Durasi(*X));
        printf("Berhasil undo.");
    } else {
        printf("Anda belum memasukkan aksi apapun.");
    }
}

void Execute(Stack *S, int *Money, TabInt *Inventory, TabInt *ListMaterial){
/* I.S. Terdapat stack perintah sembarang yang mungkin kosong */
/* F.S. Semua perintah dijalankan satu per satu dari top hingga stack kosong, 
        kemudian fase berubah dari preparation ke main*/
        /* KAMUS */
        aksitype X;

        /* ALGORITMA */
        *Money -=  JumlahBiaya(*S);
        
        while (!IsEmptyStack(*S)) {
            Pop(S, &X);
            if (IsEQKata(Aksi(X),StringToKata("buy",3))){
                Buy(Inventory, ListMaterial, Money, InfoNamaAksi(X), InfoJumlahAksi(X));
            }
        }
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
    long D1, D2, DHsl;

    /* ALGORITMA */
    if (!IsFullStack(*S)) {
        Push(S,X);
        /*
        D1 = JAMToDetik(Durasi(X));
        D2 = JAMToDetik(CurrentDuration(*S));
        DHsl = D1 + D2;

        CurrentDuration(*S) = DetikToJAM(DHsl);
        */
        
        //CurrentDuration(*S) = TambahJAM(CurrentDuration(*S), Durasi(X));
        TulisJAM(CurrentDuration(*S));
        printf("Berhasil menambahkan aksi.\n");
    } else {
        printf("Anda tidak memiliki durasi yang cukup.\n");
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
        Pop(&S,&X);
        biaya += Harga(X);
    }
    return biaya;
}