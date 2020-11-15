/* File: arraypos.c */
/* *** Body ADT Arraypos *** */

#include <stdio.h>
#include "boolean.h"
#include "../array.h"

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
      Elmt(*T,i) = ValUndef;
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
   while((Elmt(T,i) != ValUndef) && (i <= IdxMax)){
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
boolean IsIdxValid (TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang valid utk ukuran tabel */
/* yaitu antara indeks yang terdefinisi utk container*/
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return ((i >= IdxMin) && (i <= IdxMax));
}
boolean IsIdxEff (TabInt T, IdxType i){
/* Mengirimkan true jika i adalah indeks yang terdefinisi utk tabel */
/* yaitu antara FirstIdx(T)..LastIdx(T) */
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return ((i >= GetFirstIdx(T) && (i <= GetLastIdx(T))));
}

/* ********** TEST KOSONG/PENUH ********** */
/* *** Test tabel kosong *** */
boolean IsEmpty (TabInt T){
/* Mengirimkan true jika tabel T kosong, mengirimkan false jika tidak */
   /*KAMUS LOKAL*/

   /*ALGORITMA*/
   return (NbElmt(T) == 0);
}
/* *** Test tabel penuh *** */
boolean IsFull (TabInt T){
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
         Elmt(*T,i) = el;
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
   if(IsEmpty(T)){
      printf("[]");
   } else {
      printf("[");
      for(i=IdxMin; i<=GetLastIdx(T);i++){
         if (i == GetLastIdx(T)){
            printf("%d",Elmt(T,i));
         } else {
            printf("%d,",Elmt(T,i));
         }
      }
      printf("]");
   }
}

/* ********** OPERATOR ARITMATIKA ********** */
/* *** Aritmatika tabel : Penjumlahan, pengurangan, perkalian, ... *** */
TabInt PlusMinusTab (TabInt T1, TabInt T2, boolean plus){
/* Prekondisi : T1 dan T2 berukuran sama dan tidak kosong */
/* Jika plus = true, mengirimkan  T1+T2, yaitu setiap elemen T1 dan T2 pada indeks yang sama dijumlahkan */
/* Jika plus = false, mengirimkan T1-T2, yaitu setiap elemen T1 dikurangi elemen T2 pada indeks yang sama */
   /*KAMUS LOKAL*/
   IdxType i;
   TabInt T3;
   MakeEmpty(&T3);

   /*ALGORITMA*/
   if(plus == true){
      for(i=IdxMin; i<NbElmt(T1); i++){
         Elmt(T3,i) = Elmt(T1,i) + Elmt(T2,i);
      }
   } else {
      for(i=IdxMin; i<NbElmt(T1); i++){
         Elmt(T3,i) = Elmt(T1,i) - Elmt(T2,i);
      }
   }

   return T3;
}
/* ********** OPERATOR RELASIONAL ********** */
/* *** Operasi pembandingan tabel : < =, > *** */
boolean IsEQ (TabInt T1, TabInt T2){
/* Mengirimkan true jika T1 sama dengan T2 yaitu jika ukuran T1 = T2 dan semua elemennya sama */
   /*KAMUS LOKAL*/
   IdxType i=0;
   boolean equal;

   equal = true;

   /*ALGORITMA*/
   if(NbElmt(T1) == NbElmt(T2)){
      while((equal == true) && (i<NbElmt(T1))){
            if(Elmt(T1,i) != Elmt(T2,i)){
               equal = false;
            }
         i += 1;
      }
   } else {
      equal = false;
   }
   return equal;
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
   if(IsEmpty(T)){
      return IdxUndef;
   } else {
      while((found == false) && (i<NbElmt(T))){
         if(Elmt(T,i) == X){
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
   if(IsEmpty(T)){
      return false;
   } else {
      while((found == false) && (i<NbElmt(T))){
         if(Elmt(T,i) == X){
            found = true;
         }
         i += 1;
      }
   }
   return found;

}

/* ********** NILAI EKSTREM ********** */
void MaxMin (TabInt T, ElArrayType * Max, ElArrayType * Min){
/* I.S. Tabel T tidak kosong */
/* F.S. Max berisi nilai maksimum T;
        Min berisi nilai minimum T */
   /*KAMUS LOKAL*/
   IdxType i;
   *Max = Elmt(T,0);
   *Min = Elmt(T,0);
   
   /*ALGORITMA*/
   for(i=IdxMin; i<NbElmt(T); i++){
      if(Elmt(T,i) > *Max){
         *Max = Elmt(T,i);
      }
      if(Elmt(T,i) < *Min){
         *Min = Elmt(T,i);
      }
   }
}

/* ********** OPERASI LAIN ********** */
ElArrayType SumTab (TabInt T){
/* Menghasilkan hasil penjumlahan semua elemen T */
/* Jika T kosong menghasilkan 0 */
   /*KAMUS LOKAL*/
   IdxType i;
   int sum=0;

   /*ALGORITMA*/
   if(IsEmpty(T)){
      return 0;
   } else {
      for(i=IdxMin; i<NbElmt(T); i++){
         sum += Elmt(T,i);
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
   if(IsEmpty(T)){
      return 0;
   } else {
      for(i=IdxMin; i<NbElmt(T); i++){
         if(Elmt(T,i) == X){
            n += 1;
            }
         }
      }
   return n;
}
boolean IsAllGenap (TabInt T){
/* Menghailkan true jika semua elemen T genap */
   /*KAMUS LOKAL*/
   IdxType i;
   boolean genap;

   i = IdxMin;
   genap = true;

   /*ALGORITMA*/
   if(IsEmpty(T)){
      return false;
   } else {
      while((genap == true) && (i<NbElmt(T))){
         if(Elmt(T,i)%2 != 0){
            genap=false;
            }
         i += 1;
         }
      }
   return genap;
}

/* ********** SORTING ********** */
void Sort (TabInt * T, boolean asc){
/* I.S. T boleh kosong */
/* F.S. Jika asc = true, T terurut membesar */
/*      Jika asc = false, T terurut mengecil */
/* Proses : Mengurutkan T dengan salah satu algoritma sorting,
   algoritma bebas */
   /*KAMUS LOKAL*/
   IdxType i, j;
   IdxType n;
   ElArrayType temp;
   /*ALGORITMA*/
   n = GetLastIdx(*T);

   if(asc == true){
      for(i=IdxMin; i<=n; i++){
         for(j=i+1; j<=n;j++){
            if(T->TI[i] > T->TI[j]){
               temp = T->TI[i];
               T->TI[i] = T->TI[j];
               T->TI[j] = temp;
            }
         }
      }
   } else {
      for(i=IdxMin; i<=n; i++){
         for(j=i+1; j<=n;j++){
            if(T->TI[i] < T->TI[j]){
               temp = T->TI[i];
               T->TI[i] = T->TI[j];
               T->TI[j] = temp;
            }
         }
      }
   }

}

/* ********** MENAMBAH DAN MENGHAPUS ELEMEN DI AKHIR ********** */
/* *** Menambahkan elemen terakhir *** */
void AddAsLastEl (TabInt * T, ElArrayType X){
/* Proses: Menambahkan X sebagai elemen terakhir tabel */
/* I.S. Tabel T boleh kosong, tetapi tidak penuh */
/* F.S. X adalah elemen terakhir T yang baru */
   /*KAMUS LOKAL*/
   
   /*ALGORITMA*/
   if(IsEmpty(*T)){
      Elmt(*T,0) = X;
   } else {
      Elmt(*T, GetLastIdx(*T)+1) = X;
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
   *X = Elmt(*T, GetLastIdx(*T));
   Elmt(*T, GetLastIdx(*T)) = ValUndef;
}
