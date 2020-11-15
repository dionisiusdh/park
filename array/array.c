/* File: arraypos.c */
/* *** Body ADT Arraypos *** */

#include <stdio.h>
#include "../boolean.h"
#include "./array.h"

/* ********** KONSTRUKTOR ********** */
/* Konstruktor : create tabel kosong  */
void MakeEmpty (TabInt * T){
/* I.S. T sembarang */
/* F.S. Terbentuk tabel T kosong dengan kapasitas IdxMax-IdxMin+1 */
/* Proses: Inisialisasi semua elemen tabel T dengan ValUndef */
   /*KAMUS LOKAL*/
   IdxType i;

   /*ALGORITMA*/
   for(i=IdxMin; i<=IdxMax; i++){
      ElmtArray(*T,i) = ValUndef;
   }
}

/* ********** SELEKTOR (TAMBAHAN) ********** */
/* *** Banyaknya elemen *** */
int NbElmt (TabInt T){
/* Mengirimkan banyaknya elemen efektif tabel */
/* Mengirimkan nol jika tabel kosong */
   /*KAMUS LOKAL*/
   IdxType i=IdxMin;
   int n=0;

   /*ALGORITMA*/
   while((ElmtArray(T,i) != ValUndef) && (i <= IdxMax)){
      n += 1;
      i += 1;
   }

   return n;
}
/* *** Daya tampung container *** */
int MaxNbEl (TabInt T){
/* Mengirimkan maksimum elemen yang dapat ditampung oleh tabel */
/* *** Selektor INDEKS *** */
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return (IdxMax - IdxMin + 1);
}
IdxType GetFirstIdx (TabInt T){
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T pertama */
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return IdxMin;
}
IdxType GetLastIdx (TabInt T){
/* Prekondisi : Tabel T tidak kosong */
/* Mengirimkan indeks elemen T terakhir */
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return (NbElmt(T)-1);
}

/* ********** Test Indeks yang valid ********** */
boolean IsIdxValidArray (TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return ((i >= IdxMin) && (i <= IdxMax));
}
boolean IsIdxEffArray (TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return ((i >= GetFirstIdx(T) && (i <= GetLastIdx(T))));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmptyArray (TabInt T){
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return (NbElmt(T) == 0);
}
/* *** Test tabel penuh *** */
boolean IsFullArray (TabInt T){
/* Mengirimkan true jika tabel T penuh, mengirimkan false jika tidak */
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return (NbElmt(T) == IdxMax-IdxMin+1);
}

/* ********** BACA dan TULIS dengan INPUT/OUTPUT device ********** */
/* *** Mendefinisikan isi tabel dari pembacaan *** */
void BacaIsi (TabInt * T){
   /* I.S. T sembarang */
/* F.S. Tabel T terdefinisi */
/* Proses : membaca banyaknya elemen T dan mengisi nilainya */
/* 1. Baca banyaknya elemen diakhiri enter, misalnya N */
/*    Pembacaan diulangi sampai didapat N yang benar yaitu 0 <= N <= MaxNbEl(T) */
/*    Jika N tidak valid, tidak diberikan pesan kesalahan */
/* 2. Jika 0 < N <= MaxNbEl(T); Lakukan N kali: Baca elemen mulai dari indeks 
      IdxMin satu per satu diakhiri enter */
/*    Jika N = 0; hanya terbentuk T kosong */
   /*KAMUS LOKAL*/
   int N;
   IdxType i;
   ElArrayType el;

   /*ALGORITMA*/
   do {
      scanf("%d",&N);
   } while ((N<0) || (N > (MaxNbEl(*T))));

   MakeEmpty(T);

   if (N!=0) {
      for (i=IdxMin; i<N; i++){
         scanf("%d", &el);
         ElmtArray(*T,i) = el;
      }
   }
}
void TulisIsiTab (TabInt T){
/* Proses : Menuliskan isi tabel dengan traversal, tabel ditulis di antara kurung siku; 
   antara dua elemen dipisahkan dengan separator "koma", tanpa tambahan karakter di depan,
   di tengah, atau di belakang, termasuk spasi dan enter */
/* I.S. T boleh kosong */
/* F.S. Jika T tidak kosong: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika tabel kosong : menulis [] */
   /*KAMUS LOKAL*/
   IdxType i=0;

   /*ALGORITMA*/
   if(IsEmptyArray(T)){
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
IdxType Search1 (TabInt T, ElArrayType X){
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
   if(IsEmptyArray(T)){
      return IdxUndef;
   } else {
      while((found == false) && (i<NbElmt(T))){
         if(ElmtArray(T,i) == X){
            found = true;
            idx = i;
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

boolean SearchB (TabInt T, ElArrayType X){
/* Search apakah ada elemen tabel T yang bernilai X */
/* Jika ada, menghasilkan true, jika tidak ada menghasilkan false */
/* Skema searching yang digunakan bebas */
   /*KAMUS LOKAL*/
   IdxType i;
   boolean found = false;
   i = IdxMin;
   /*ALGORITMA*/
   if(IsEmptyArray(T)){
      return false;
   } else {
      while((found == false) && (i<NbElmt(T))){
         if(ElmtArray(T,i) == X){
            found = true;
         }
         i += 1;
      }
   }
   return found;

}

/* ********** OPERASI LAIN ********** */
ElArrayType SumTab (TabInt T){
/* Menghasilkan hasil penjumlahan semua elemen T */
/* Jika T kosong menghasilkan 0 */
   /*KAMUS LOKAL*/
   IdxType i;
   int sum=0;

   /*ALGORITMA*/
   if(IsEmptyArray(T)){
      return 0;
   } else {
      for(i=IdxMin; i<NbElmt(T); i++){
         sum += ElmtArray(T,i);
         }
      }
   return sum;
}
int CountX (TabInt T, ElArrayType X){
/* Menghasilkan berapa banyak kemunculan X di T */
/* Jika T kosong menghasilkan 0 */
   /*KAMUS LOKAL*/
   IdxType i;
   int n = 0;
   
   /*ALGORITMA*/
   if(IsEmptyArray(T)){
      return 0;
   } else {
      for(i=IdxMin; i<NbElmt(T); i++){
         if(ElmtArray(T,i) == X){
            n += 1;
            }
         }
      }
   return n;
}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabInt * T, ElArrayType X){
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
   /*KAMUS LOKAL*/
   
   /*ALGORITMA*/
   if(IsEmptyArray(*T)){
      ElmtArray(*T,0) = X;
   } else {
      ElmtArray(*T, GetLastIdx(*T)+1) = X;
   }
}
/* ********** MENGHAPUS ELEMEN ********** */
void DelLastEl (TabInt * T, ElArrayType * X){
/* Proses : Menghapus elemen terakhir tabel */
/* I.S. Tabel tidak kosong */
/* F.S. X adalah nilai elemen terakhir T sebelum penghapusan, */
/*      Banyaknya elemen tabel berkurang satu */
/*      Tabel T mungkin menjadi kosong */
   /*KAMUS LOKAL*/
   
   /*ALGORITMA*/
   *X = ElmtArray(*T, GetLastIdx(*T));
   ElmtArray(*T, GetLastIdx(*T)) = ValUndef;
}
