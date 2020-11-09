/* File: matriks.c */
/* *** Realisasi ABSTRACT DATA TYPE MATRIKS *** */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "matriks.h"
#include "../boolean.h"

/* ********** DEFINISI PROTOTIPE PRIMITIF ********** */
/* *** Konstruktor membentuk MATRIKS *** */
void MakeMATRIKS (int NB, int NK, MATRIKS * M){
/* Membentuk sebuah MATRIKS "kosong" yang siap diisi berukuran NB x NK di "ujung kiri" memori */
/* I.S. NB dan NK adalah valid untuk memori matriks yang dibuat */
/* F.S. Matriks M sesuai dengan definisi di atas terbentuk */
    NBrsEff(*M) = NB;
    NKolEff(*M) = NK;
}

/* *** Selektor "DUNIA MATRIKS" *** */
boolean IsIdxValid (int i, int j){
/* Mengirimkan true jika i, j adalah indeks yang valid untuk matriks apa pun */
    boolean valid = false;
    if ((i>=BrsMin && i<=BrsMax)&&(j>=BrsMin&&j<=BrsMax)){
        valid = true;
    }
    return valid;
}
/* *** Selektor: Untuk sebuah matriks M yang terdefinisi: *** */
indeks GetFirstIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terkecil M */
    return BrsMin;
}
indeks GetFirstIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terkecil M */
    return KolMin;
}
indeks GetLastIdxBrs (MATRIKS M){
/* Mengirimkan indeks baris terbesar M */
    return (NBrsEff(M) - 1);
}
indeks GetLastIdxKol (MATRIKS M){
/* Mengirimkan indeks kolom terbesar M */
    return NKolEff(M)-1;
}
boolean IsIdxEff (MATRIKS M, indeks i, indeks j){
/* Mengirimkan true jika i, j adalah indeks efektif bagi M */
    return ((i>=BrsMin && i<=(GetLastIdxBrs(M))) && (j>=KolMin && j<=(GetLastIdxKol(M))));
}
ElType GetElmtDiagonal (MATRIKS M, indeks i){
/* Mengirimkan elemen M(i,i) */
    return (Elmt(M,i,i));
}

/* ********** Assignment  MATRIKS ********** */
void CopyMATRIKS (MATRIKS MIn, MATRIKS * MHsl){
/* Melakukan assignment MHsl  MIn */
    //KAMUS LOKAL
    *MHsl = MIn;
}

/* ********** KELOMPOK BACA/TULIS ********** */
void BacaMATRIKS (MATRIKS * M, int NB, int NK){
/* I.S. IsIdxValid(NB,NK) */
/* F.S. M terdefinisi nilai elemen efektifnya, berukuran NB x NK */
/* Proses: Melakukan MakeMATRIKS(M,NB,NK) dan mengisi nilai efektifnya */
/* Selanjutnya membaca nilai elemen per baris dan kolom */
/* Contoh: Jika NB = 3 dan NK = 3, maka contoh cara membaca isi matriks :
1 2 3
4 5 6
8 9 10
*/
    //KAMUS LOKAL
    int i,j; int val;
    //ALGORITMA
    MakeMATRIKS(NB, NK,&*M);
    for (i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++){
        for (j=GetFirstIdxKol(*M); j<=GetLastIdxKol(*M); j++){
            scanf("%d",&val);
            Elmt(*M,i,j) = val;
        }
    }
}
void TulisMATRIKS (MATRIKS M){
/* I.S. M terdefinisi */
/* F.S. Nilai M(i,j) ditulis ke layar per baris per kolom, masing-masing elemen per baris
   dipisahkan sebuah spasi */
/* Proses: Menulis nilai setiap elemen M ke layar dengan traversal per baris dan per kolom */
/* Contoh: menulis matriks 3x3 (ingat di akhir tiap baris, tidak ada spasi)
1 2 3
4 5 6
8 9 10
*/
    //KAMUS LOKAL
    int i,j;
    //ALGORITMA
    for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++){
        for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
            if (j==GetLastIdxKol(M)){
                printf("%d",Elmt(M,i,j));
            }
            else{
                printf("%d",Elmt(M,i,j));
            }
        }
        printf("\n");
    }
}

/* ********** KELOMPOK OPERASI ARITMATIKA TERHADAP TYPE ********** */
MATRIKS TambahMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : M1  berukuran sama dengan M2 */
/* Mengirim hasil penjumlahan matriks: M1 + M2 */
    //KAMUS LOKAL
    int i,j;
    MATRIKS MAdd;
    //ALGORITMA
    CopyMATRIKS(M1,&MAdd);
    for (i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++){
        for (j=GetFirstIdxKol(M1); j<=GetLastIdxKol(M1); j++){
            Elmt(MAdd,i,j) = Elmt(M1,i,j) + Elmt(M2,i,j);
        }
    }
    return MAdd;
}
MATRIKS KurangMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : M berukuran sama dengan M */
/* Mengirim hasil pengurangan matriks: salinan M1 � M2 */
    //KAMUS LOKAL
    int i,j;
    MATRIKS MSub;
    //ALGORITMA
    MakeMATRIKS(NBrsEff(M1),NKolEff(M1),&MSub);
    for (i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++){
        for (j=GetFirstIdxKol(M1); j<=GetLastIdxKol(M1); j++){
            Elmt(MSub,i,j) = Elmt(M1,i,j) - Elmt(M2,i,j);
        }
    }
    return MSub;
}
MATRIKS KaliMATRIKS (MATRIKS M1, MATRIKS M2){
/* Prekondisi : Ukuran kolom efektif M1 = ukuran baris efektif M2 */
/* Mengirim hasil perkalian matriks: salinan M1 * M2 */
    //KAMUS LOKAL
    int i,j,k;
    MATRIKS MMul;
    //ALGORITMA
    MakeMATRIKS(NBrsEff(M1),NKolEff(M2),&MMul);
    for (i=GetFirstIdxBrs(M1); i<=GetLastIdxBrs(M1); i++){
        for (j=GetFirstIdxKol(M2); j<=GetLastIdxKol(M2); j++){
            for (k=GetFirstIdxKol(M1); k<=GetLastIdxKol(M1); k++){
                Elmt(MMul,i,j) += Elmt(M1,i,k) * Elmt(M2,k,j);
            }
        }
    }
    return MMul;
}
MATRIKS KaliKons (MATRIKS M, ElType X){
/* Mengirim hasil perkalian setiap elemen M dengan X */
    //KAMUS LOKAL
    int i,j;
    MATRIKS MMulCon;
    //ALGORITMA
    MakeMATRIKS(NBrsEff(M),NKolEff(M),&MMulCon);
    for (i=GetFirstIdxBrs(M); i<=GetLastIdxBrs(M); i++){
        for (j=GetFirstIdxKol(M); j<=GetLastIdxKol(M); j++){
            Elmt(MMulCon,i,j) = Elmt(M,i,j) * X;
        }
    }
    return MMulCon;
}
void PKaliKons (MATRIKS * M, ElType K){
/* I.S. M terdefinisi, K terdefinisi */
/* F.S. Mengalikan setiap elemen M dengan K */
    //KAMUS LOKAL
    int i,j;
    //ALGORITMA
    for (i=GetFirstIdxBrs(*M); i<=GetLastIdxBrs(*M); i++){
        for (j=GetFirstIdxKol(*M); j<=GetLastIdxKol(*M); j++){
            Elmt(*M,i,j) = Elmt(*M,i,j) * K;
        }
    }
}

/* ********** KELOMPOK OPERASI RELASIONAL TERHADAP MATRIKS ********** */
boolean EQ (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika M1 = M2, yaitu NBElmt(M1) = NBElmt(M2) dan */
/* untuk setiap i,j yang merupakan indeks baris dan kolom M1(i,j) = M2(i,j) */
/* Juga merupakan strong EQ karena GetFirstIdxBrs(M1) = GetFirstIdxBrs(M2)
   dan GetLastIdxKol(M1) = GetLastIdxKol(M2) */
    //KAMUS LOKAL
    boolean equal = false;
    int i,j;
    //ALGORITMA
    if ((NBrsEff(M1)==NBrsEff(M2)) && (NKolEff(M1)==NKolEff(M2))){
        equal = true;
        i = GetFirstIdxBrs(M1);
        while (equal && (i<=GetLastIdxBrs(M1))){
            j = GetFirstIdxKol(M1);
            while (equal && (j<=GetLastIdxKol(M1))){
                if (Elmt(M1,i,j)!=Elmt(M2,i,j)){
                    equal = false;
                }
                j+=1;
            }
            i+=1;
        }
    }
    return equal;
}
boolean NEQ (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika M1 tidak sama dengan M2 */
    return !EQ(M1,M2);
}
boolean EQSize (MATRIKS M1, MATRIKS M2){
/* Mengirimkan true jika ukuran efektif matriks M1 sama dengan ukuran efektif M2 */
/* yaitu GetBrsEff(M1) = GetNBrsEff (M2) dan GetNKolEff (M1) = GetNKolEff (M2) */
    return (NBrsEff(M1)==NBrsEff(M2) && NKolEff(M1)==NKolEff(M2));
}

/* ********** Operasi lain ********** */
int NBElmt (MATRIKS M){
/* Mengirimkan banyaknya elemen M */
    return (NBrsEff(M)*NKolEff(M));
}