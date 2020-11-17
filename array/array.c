/* File: array.c */
/* *** Body ADT array *** */

#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "../boolean.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty(TabInt *T, int maxel){
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
    /*KAMUS LOKAL*/

    /*ALGORITMA*/
    TI(*T) = (ElArrayType *) malloc (maxel*sizeof(ElArrayType));
    NeffArray(*T) = 0;
    MaxElArray(*T) = maxel;
}

void Dealokasi(TabInt *T){
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxElArray(T)=0; NeffArray(T)=0 */
    free(TI(*T));
    MaxElArray(*T) = 0;
    NeffArray(*T) = 0;
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmtArray(TabInt T){
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
/* *** Daya tampung container *** */
    /*KAMUS LOKAL*/
    
    /*ALGORITMA*/
    return NeffArray(T);
}
int MaxElement(TabInt T){
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
    /*KAMUS LOKAL*/
    
    /*ALGORITMA*/
    return MaxElArray(T);
}
/* *** Selektor INDEKS *** */
IdxType GetFirstIdx(TabInt T){
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
    /*KAMUS LOKAL*/
    
    /*ALGORITMA*/
    return IdxMin;
}
IdxType GetLastIdx(TabInt T){
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
    /*KAMUS LOKAL*/
    
    /*ALGORITMA*/
    return (NbElmtArray(T)-1);
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValid(TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
    /*KAMUS LOKAL*/
    
    /*ALGORITMA*/
    return ((i >= IdxMin) && (i <= MaxElement(T)-1));
}
boolean IsIdxEff(TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
    /*KAMUS LOKAL*/
    
    /*ALGORITMA*/
    return ((i >= IdxMin) && (i <= NbElmtArray(T)-1));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty(TabInt T){
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
    /*KAMUS LOKAL*/
    
    /*ALGORITMA*/
    return (NeffArray(T) == 0);
}
/* *** Test tabel penuh *** */
boolean IsFull(TabInt T){
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
    /*KAMUS LOKAL*/
    
    /*ALGORITMA*/
    return (NbElmtArray(T) == MaxElement(T));
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi(TabInt *T){
/* I.S. T sembarang dan sudah dialokasikan sebelumnya */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxElement(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxElement(T); Lakukan N kali: Baca elemen mulai dari indeks
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
    /*KAMUS LOKAL*/
    int N;
    IdxType i;

    /*ALGORITMA*/
    do {
        scanf("%d",&N);
    } while ((N<0) || (N > (MaxElement(*T))));

    for (i=IdxMin; i<N; i++){
        scanf("%d", &ElmtArray(*T,i));
    }

    NeffArray(*T) = N;
}
void TulisIsiTab(TabInt T){
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku;
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
    /*KAMUS LOKAL*/
   IdxType i;

   /*ALGORITMA*/
   if(IsEmpty(T)){
      printf("[]");
   } else {
      printf("[");
      for(i=IdxMin; i<=GetLastIdx(T);i++){
         if (i == GetLastIdx(T)){
            printf("%d",ElmtArray(T,i));
         } else {
            printf("%d,",ElmtArray(T,i));
         }
      }
      printf("]");
   }
}

/* ********** SEARCHING ********** */
/* ***  Perhatian : Tabel boleh kosong!! *** */
IdxType Search1(TabInt T, Kata X){
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan indeks i terkecil, dengan elemen ke-i = X */
/* Jika tidak ada, mengirimkan IdxUndef */
/* Menghasilkan indeks tak terdefinisi (IdxUndef) jika tabel T kosong */
/* Skema Searching yang digunakan bebas */
    /*KAMUS LOKAL*/
    IdxType i;
    IdxType idx;
    boolean found = false;
    i = IdxMin;

    /*ALGORITMA*/
    if(IsEmpty(T)){
        return IdxUndef;
    } else {
        while((found == false) && (i<=GetLastIdx(T))){
            if(IsEQKata(Nama(ElmtArray(T,i)), X)){
                idx = i;
                found = true;
            }
            i += 1;
        }
    }

    if(found == true){
            return idx;
    } else {
        return IdxUndef;
    }
}
boolean SearchB(TabInt T, Kata X){
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
    /*KAMUS LOKAL*/

    /*ALGORITMA*/
    return Search1(T,X) != IdxUndef;
}


/* ********** OPERASI LAIN ********** */
int SumTab(TabInt T){
/* Menghasilkan hasil penjumlahan semua elemen T */
/* Jika T kosong menghasilkan 0 */
    /*KAMUS LOKAL*/
    IdxType i;
    int sum=0;

    /*ALGORITMA*/
    for(i=IdxMin; i<=GetLastIdx(T); i++){
        sum += Value(ElmtArray(T,i));
    }
    
    return sum;
}
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl(TabInt *T, ElArrayType X){
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
    /*ALGORITMA*/
   ElmtArray(*T, NeffArray(*T)) = X;
   NeffArray(*T) += 1;
}
/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl(TabInt *T, ElArrayType *X){
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
    /*KAMUS LOKAL*/
   
   /*ALGORITMA*/
   *X = ElmtArray(*T, GetLastIdx(*T));
   NeffArray(*T) -= 1;
}

/* ********* MENGUBAH UKURAN ARRAY ********* */
void GrowTab(TabInt *T, int num){
/* Proses : Menambahkan max element sebanyak num */
/* I.S. Tabel sudah terdefinisi */
/* F.S. Ukuran tabel bertambah sebanyak num */
    /*KAMUS LOKAL*/
    TabInt temp;
    int i;

    /*ALGORITMA*/
    MakeEmpty(&temp, MaxElement(*T));
    CopyTab(*T,&temp);

    Dealokasi(T);
    MakeEmpty(T, MaxElement(temp)+num);

    NeffArray(*T) = NeffArray(temp);
    for (i = GetFirstIdx(temp); i  <= GetLastIdx(temp);  ++i){
        ElmtArray(*T, i) = ElmtArray(temp, i);
    }

    Dealokasi(&temp);
}

void ShrinkTab(TabInt *T, int num){
/* Proses : Mengurangi max element sebanyak num */
/* I.S. Tabel sudah terdefinisi, ukuran MaxEl > num, dan NeffArray < MaxEl - num. */
/* F.S. Ukuran tabel berkurang sebanyak num. */
    /*KAMUS LOKAL*/
    TabInt temp;
    int i;

    /*ALGORITMA*/
    MakeEmpty(&temp, MaxElement(*T));
    CopyTab(*T,&temp);

    Dealokasi(T);
    MakeEmpty(T, MaxElement(temp)-num);
    
    NeffArray(*T) = NeffArray(temp);
    for (i = GetFirstIdx(temp); i  <= GetLastIdx(temp);  ++i){
        ElmtArray(*T, i) = ElmtArray(temp, i);
    }

    Dealokasi(&temp);
}

void CompactTab(TabInt *T){
/* Proses : Mengurangi max element sehingga NeffArray = MaxEl */
/* I.S. Tabel tidak kosong */
/* F.S. Ukuran MaxEl = NeffArray */
    /*KAMUS LOKAL*/
    TabInt temp;

    /*ALGORITMA*/
    MakeEmpty(&temp, MaxElement(*T));
    CopyTab(*T,&temp);

    Dealokasi(T);
    MakeEmpty(T, NbElmtArray(temp));
    
    CopyTab(temp,T);

    Dealokasi(&temp);
    MaxElArray(*T) = NbElmtArray(*T);
}
