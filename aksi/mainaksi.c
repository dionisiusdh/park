/* MODUL AKSI PREPARATION */

#include <stdio.h>
#include <stdlib.h>
#include "mainaksi.h"

/* ********** AKSI ********** */
void Serve (Queue *Q, ListWahana *LWahana, Kata NamaWahana, TabInt *Kapasitas, TabTime *Waktu, TabInt Durasi, JAM Current, int *Money, boolean *serve_gagal) {
    /* KAMUS */
    boolean rusak;
    queuetype X;
    int lokasi = SearchQueue(*Q,NamaWahana); //Lokasi dari elemen queue dengan nama wahana di dalamnya

    /* ALGORITMA */
    if (AdaWahana(*Kapasitas,NamaWahana)){
        //Apabila tidak ada elemen di queue yang memiliki wahana NamaWahana sebagai wahana yang ingin dinaiki
        if (lokasi != NilQueue){
            //Apabila wahana rusak
            if (GetStatusNamaWahana(LWahana, NamaWahana)){
                //Apabila kapasitas wahana penuh
                if (!KapasitasFull(*Kapasitas, NamaWahana)) { 
                    /* KERUSAKAN WAHANA SETELAH SERVE */
                    DelQueue(Q,&X,NamaWahana);
                    rusak = BrokenRandomizer();
                    if (rusak) {
                        // Jika randomizer menghasilkan 'rusak', elemen X ditambahkan prioritasnya dan dimasukkan kembali ke dalam queue
                        PrioQueue(X) += 1;
                        SetStatusNamaWahana(LWahana, NamaWahana, false);
                        printf("Wahana ");
                        PrintKata(NamaWahana);
                        printf(" rusak! Harap perbaiki wahana agar dapat digunakan.\n");
                        AddQueue(Q,X);
                        *serve_gagal = true;
                    } 
                    else {
                        PrioQueue(X) += 1;
                        DellPengunjung(&Pengunjung(X),NamaWahana);
                        KurangKapasitas(Kapasitas,NamaWahana);
                        AddTime(Waktu,GetTime(Current,NamaWahana,X,Durasi));
                        AddMoney(*LWahana,Money,NamaWahana);
                        *serve_gagal = false;
                    }
                } else {
                    printf("Kapasitas wahana ");
                    PrintKata(NamaWahana);
                    printf(" penuh sehingga tidak dapat digunakan.\n");
                    *serve_gagal = true;
                }
            } 
            else{
                printf("Wahana ");
                PrintKata(NamaWahana);
                printf(" rusak sehingga tidak dapat digunakan.\n");
                *serve_gagal = true;
            }
        }
        else{
            printf("Tidak ada pengunjung di antrian yang ingin menaiki wahana tersebut\n");
            *serve_gagal = true;
        }
    }
    else{
        printf("Wahana belum dibangun\n");
        *serve_gagal = true;
    }
}

void Repair(MATRIKS *Map, ListWahana *LWahana) {
    /* KAMUS */
    POINT NearTitikWahana;
    Wahana NearWahana;
    boolean CurrentStatus;
    
    /* ALGORITMA */
    if (isNearWahana(*Map, getPlayer(*Map))) {
        NearTitikWahana = GetTitikNearWahana(*Map);
        NearWahana = GetNearWahana(Map, *LWahana);
        CurrentStatus = GetStatusWahana(NearWahana);
        if (CurrentStatus) {
            // Jika wahana tidak rusak
            printf("Wahana sedang berfungsi dengan baik dan tidak rusak.\n");
        } else {
            // Set status wahana menjadi berfungsi (true)
            SetStatusNamaWahana(LWahana, AkarNama(DeskripsiWahana(NearWahana)), true);
        }
    } else {
        printf("Anda sedang tidak berada di dekat wahana\n");
    }
}

void Detail(MATRIKS *Map, ListWahana LWahana) {
    /* KAMUS */
    POINT NearTitikWahana;
    Wahana NearWahana;

    /* ALGORITMA */
    if (isNearWahana(*Map, getPlayer(*Map))) {
        NearTitikWahana = GetTitikNearWahana(*Map);
        NearWahana = GetNearWahana(Map, LWahana);
        PrintInfoWahana(NearWahana);
    } else {
        printf("Anda sedang tidak berada di dekat wahana");
    }
}

/* ********** OFFICE ********** */
void MenuOffice(MATRIKS *Map, ListWahana *LWahana, POINT Office, TabInt Inventory) {
    /* KAMUS */
    boolean exitOffice = false;

    /* ALGORITMA */
    if (!isInOffice(getPlayer(*Map), Office)) {
        printf("Anda sedang tidak berada di titik office!\n");
    } else {
        printf("Memasuki office mode...\n");
        
        while (!exitOffice) {
            printf("\nMasukkan perintah (Details / Report / Material / Exit): \n");
            printf("$ ");
            STARTKATA();

            if (IsEQKata(CKata, StringToKata("Details", 7))) {
                DetailsOffice(LWahana);
            } else if (IsEQKata(CKata, StringToKata("Report", 6))) {
                ReportOffice(LWahana);
            } else if (IsEQKata(CKata, StringToKata("Material", 8))) {
                MaterialOffice(Inventory);
            } else if (IsEQKata(CKata, StringToKata("Exit", 4))) {
                exitOffice = true;
            } else {
                printf("Masukkan anda tidak valid!\n");
            }
        }
    }
}

void DetailsOffice(ListWahana *LWahana) {
/* KAMUS */
    int i, CPerintah;
    Wahana W;

    /* ALGORITMA */
    i = 1;
    addressWahana P = FirstWahana(*LWahana);
    if (IsEmptyListWahana(*LWahana)){
        printf("Wahana kosong");
    } else {
        while (P != Nil){
            printf("%d. ", i);
            PrintKata(AkarNama(DeskripsiWahana(InfoWahana(P))));
            printf("\n");
            P = NextWahana(P);
            i++;
        }
    }
    printf("Masukkan angka wahana yang ingin anda lihat detailnya: \n");
    STARTKATA();
    CPerintah = KataToInteger(CKata)-1;

    if (CPerintah <= i) {
        P = FirstWahana(*LWahana);
        while (CPerintah > 0) {
            P = NextWahana(P);
            CPerintah--;
        }
        printf("\nNama: ");
        PrintKata(AkarNama(DeskripsiWahana(InfoWahana(P))));
        printf("\nDeskripsi: ");
        PrintKata(AkarDeskripsi(DeskripsiWahana(InfoWahana(P))));
        printf("\nLokasi: ");
        TulisPOINT(PosisiWahana(InfoWahana(P)));
        printf("\nHarga: %d", AkarHarga(DeskripsiWahana(InfoWahana(P))));
        printf("\nKapasitas: %d", AkarKapasitas(DeskripsiWahana(InfoWahana(P))));
        printf("\nDurasi: %d", AkarDurasi(DeskripsiWahana(InfoWahana(P))));
        printf("\nStatus: ");
        if (StatusWahana(InfoWahana(P))) {
            printf("Berfungsi\n");
        } else {
            printf("Rusak\n");
        }
    } else {
        printf("Masukkan anda tidak valid!\n");
    }
}

void MaterialOffice (TabInt Inventory) {
    printf("Inventory anda: ");
    TulisIsiTab(Inventory);
    printf("\n");
}

void ReportOffice(ListWahana *LWahana) {                            // BELOM DIIMPLEMENTASIKANNNNNNNNNNNN
    /* KAMUS */
    int i, CPerintah;
    Wahana W;

    /* ALGORITMA */
    i = 1;
    addressWahana P = FirstWahana(*LWahana);
    if (IsEmptyListWahana(*LWahana)){
        printf("Wahana kosong\n");
    } else {
        while (P != Nil){
            printf("%d. ", i);
            PrintKata(AkarNama(DeskripsiWahana(InfoWahana(P))));
            printf("\n");
            P = NextWahana(P);
            i++;
        }
    }
    printf("Masukkan angka wahana yang ingin anda lihat detailnya: \n");
    STARTKATA();
    CPerintah = KataToInteger(CKata);

    if (CPerintah <= i) {
        P = FirstWahana(*LWahana);
        while (CPerintah != 0) {
            P = NextWahana(P);
            CPerintah--;
        }
        printf("\nNama: ");
        PrintKata(AkarNama(DeskripsiWahana(InfoWahana(P))));
        printf("\nLokasi: ");
        TulisPOINT(PosisiWahana(InfoWahana(P)));
        printf("\nHarga: %d", AkarHarga(DeskripsiWahana(InfoWahana(P))));
        printf("\nKapasitas: %d", AkarKapasitas(DeskripsiWahana(InfoWahana(P))));
        printf("\nDurasi: %d", AkarDurasi(DeskripsiWahana(InfoWahana(P))));
        printf("\nDeskripsi: ");
        PrintKata(AkarDeskripsi(DeskripsiWahana(InfoWahana(P))));
    } else {
        printf("Masukkan anda tidak valid!\n");
    }
}