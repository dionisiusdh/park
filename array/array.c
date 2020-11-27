/* File: array.c */
/* *** Body ADT array *** */

#include <stdio.h>
#include <stdlib.h>
#include "array.h"
#include "../boolean.h"
#include "../mesin/mesinkata.h"
#include "../mesin/mesinkar.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty(TabInt *T){ //, int maxel){
/* I.S. T sembarang, maxel > 0 */
/* F.S. Terbentuk tabel T kosong dengan kapasitas maxel */
    /*KAMUS LOKAL*/

    /*ALGORITMA*/
    //TI(*T) = (ElArrayType *) malloc (maxel*sizeof(ElArrayType));
    NeffArray(*T) = 0;
    //MaxElArray(*T) = maxel;
}

void Dealokasi(TabInt *T){
/* I.S. T terdefinisi; */
/* F.S. TI(T) dikembalikan ke system, MaxElArray(T)=0; NeffArray(T)=0 */
    free(TI(*T));
    //MaxElArray(*T) = 0;
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
    return 0;
    //return MaxElArray(T);
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
            printf("(");         
            PrintKata(Nama(ElmtArray(T,i)));
            printf(", %d", Value(ElmtArray(T,i)));
            printf(")");
         } else {
            printf("(");  
            PrintKata(Nama(ElmtArray(T,i)));
            printf(", %d", Value(ElmtArray(T,i)));
            printf("),");  
         }
      }
      printf("]");
   }
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

/* ********** COPY ********** */
TabInt CopyTab (TabInt TIn)
/* Mereturn sebuah tabint hasil copy dari TIn */
{   //KAMUS
    TabInt Tout;
    int i;
    
    //ALGORITMA
    MakeEmpty(&Tout);
    NeffArray(Tout) = NeffArray(TIn);
    for (i=0; i<NeffArray(Tout); i++){
        ElmtArray(Tout,i) = ElmtArray(TIn,i);
    }
}

/* ********** VALUE ********** */
void SetAllValueZero (TabInt *T)
/* Mengganti semua value dari T menjadi 0 */
{
    /* KAMUS */
    int i;
    
    /* ALGORITMA */
    for(i=0;i<NeffArray(*T);i++){
        Value(ElmtArray(*T,i)) = 0;
    }
}

void SetAllValueX (TabInt *T, int X)
/* Mengganti semua value dari T menjadi X */
{
    /* KAMUS */
    int i;
    
    /* ALGORITMA */
    for(i=0;i<NeffArray(*T);i++){
        Value(ElmtArray(*T,i)) = X;
    }
}

void ChangeValue (TabInt *TInventory, Kata NamaBarang, int NewValue){
/* Mengganti value dari NamaBarang menjadi NewValue */
    /* KAMUS */
    int i;
    
    /* ALGORITMA */
    for (i=0;i<NeffArray(*TInventory);i++){
        if (IsEQKata(Nama(ElmtArray(*TInventory, i)), NamaBarang)) {
            Value(ElmtArray(*TInventory, i)) = NewValue;
            break;
        }
    }
}

int GetValue (TabInt *TInventory, Kata NamaBarang) {
    /* KAMUS */
    int i;
    
    /* ALGORITMA */
    for (i=0;i<NeffArray(*TInventory);i++){
        if (IsEQKata(Nama(ElmtArray(*TInventory, i)), NamaBarang)) {
            return Value(ElmtArray(*TInventory, i));
        }
    }
}

/* ********** PEMBACAAN FILE EKSTERNAL ********** */
void BacaMaterial (TabInt *ListMaterial)
/* Membaca material dan harga material dari file material.txt */
{
  /* KAMUS */
  FILE *PFile;
  int i,j,k,l;
  char val;
  Kata tempnama;
  Kata tempharga;
  ElArrayType element;

  /* ALGORITMA */
  PFile = fopen("./material.txt", "r");

  if (PFile != NULL){
      val = fgetc(PFile);
      i = 0;
      while(val != '.'){
        j = 0;
        tempnama.Length = 0;
        while (val != BLANK && val != '.') {
          tempnama.TabKata[j] = val;
          tempnama.Length ++;
          j++;
          val = fgetc(PFile);
        }
        
        // Prevent bug
        if (i != 0) {
            for (l=0;l<tempnama.Length-1;l++) {
                tempnama.TabKata[l] = tempnama.TabKata[l+1];
            }
            tempnama.Length--;
        }

        k = 0;
        val = fgetc(PFile);
        tempharga.Length = 0;
        while (val != MARK && val != '.') {
          tempharga.TabKata[k] = val;
          tempharga.Length ++;
          k++;
          val = fgetc(PFile);
        }
        Nama(element) = tempnama;
        Value(element) = KataToInteger(tempharga);
        AddAsLastEl(ListMaterial, element);
        i++;
      }
  }
  printf("\n");
}

void BacaAksi (TabInt *ListAksi)
/* Membaca aksi dan durasi material dari file aksi.txt */
{
  /* KAMUS */
  FILE *PFile;
  int i,j,k,l;

  long harga;
  char val;
  Kata tempaksi;
  Kata tempwaktu;
  ElArrayType element;

  /* ALGORITMA */
  PFile = fopen("./aksi.txt", "r");

  if (PFile != NULL){
      val = fgetc(PFile);
      i = 0;
      while(val != '.'){
        j = 0;
        tempaksi.Length = 0;
        while (val != BLANK && val != '.') {
          tempaksi.TabKata[j] = val;
          tempaksi.Length ++;
          j++;
          val = fgetc(PFile);
        }
        
        // Prevent bug
        if (i != 0) {
            for (l=0;l<tempaksi.Length-1;l++) {
                tempaksi.TabKata[l] = tempaksi.TabKata[l+1];
            }
            tempaksi.Length--;
        }

        k = 0;
        val = fgetc(PFile);
        tempwaktu.Length = 0;
        while (val != MARK && val != '.') {
          tempwaktu.TabKata[k] = val;
          tempwaktu.Length ++;
          k++;
          val = fgetc(PFile);
        }
        Nama(element) = tempaksi;
        Value(element) = KataToInteger(tempwaktu);
        AddAsLastEl(ListAksi, element);
        i++;
      }
  }
  printf("\n");
}

boolean SearchArray(TabInt ListWahana, Kata X)
/*Mencari apakah ada elemen X pada ListWahana*/{
    /* KAMUS */
    int i=0;
    boolean found = false;
    
    /* ALGORITMA */
    while (i<NeffArray(ListWahana) && !found){
        if (IsEQKata(Nama(ElmtArray(ListWahana, i)), X)) {
            found = true;
        }
        else{
            i++;
        }
    }
    return found;
}

int SearchBArray(TabInt ListWahana, Kata X)
/*Mencari lokasi dari elemen X pada ListWahana. Apabila tidak ada, mengembalikan -1*/
{   /* KAMUS */
    int i=0;
    boolean found = false;
    
    /* ALGORITMA */
    while (i<NeffArray(ListWahana) && !found){
        if (IsEQKata(Nama(ElmtArray(ListWahana, i)), X)) {
            found = true;
        }
        else{
            i++;
        }
    }
    if (found){
        return i;
    }
    else{
        return -1;
    }
}

TabInt InitKapasitas(ListWahana L){
    //KAMUS
    addressWahana P;
    TabInt Kapasitas;
    ElArrayType X;
    //ALGORITMA
    MakeEmpty(&Kapasitas);
    P = FirstWahana(L);
    while (P!= Nil){
        Nama(X) = AkarNama(DeskripsiWahana(InfoWahana(P)));
        Value(X) = AkarKapasitas(DeskripsiWahana(InfoWahana(P)));
        AddAsLastEl(&Kapasitas,X);
    }
    return Kapasitas;
}

TabInt InitDurasi(ListWahana L){
    //KAMUS
    addressWahana P;
    TabInt Durasi;
    ElArrayType X;
    //ALGORITMA
    MakeEmpty(&Durasi);
    P = FirstWahana(L);
    while (P!= Nil){
        Nama(X) = AkarNama(DeskripsiWahana(InfoWahana(P)));
        Value(X) = AkarDurasi(DeskripsiWahana(InfoWahana(P)));
        AddAsLastEl(&Durasi,X);
    }
    return Durasi;
}

boolean KapasitasFull(TabInt Kapasitas, Kata Wahana)
/*Mengecek apakah wahana yang dinaiki sudah penuh atau value dari list kapasitas 0*/
{   //KAMUS
    //ALGORITMA
    boolean full = true;
    int i=0;
    boolean found = false;
    /* ALGORITMA */
    if (SearchArray(Kapasitas,Wahana)){
        while (i<NeffArray(Kapasitas) && !found){
            if (IsEQKata(Nama(ElmtArray(Kapasitas, i)), Wahana)) {
                if (Value(ElmtArray(Kapasitas, i)) == 0){
                    full = true;
                }
                found = true;
            }
            else{
                i++;
            }
        }
    }
    return full;
}

void TambahKapasitas(TabInt *Kapasitas, Kata Wahana){
    //KAMUS
    int i = SearchBArray(*Kapasitas,Wahana);
    //ALGORITMA
    Value(ElmtArray(*Kapasitas, i)) += 1;
}

void KurangKapasitas(TabInt *Kapasitas, Kata Wahana){
    //KAMUS
    int i = SearchBArray(*Kapasitas,Wahana);
    //ALGORITMA
    Value(ElmtArray(*Kapasitas, i)) -= 1;
}