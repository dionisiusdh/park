#include <stdio.h>
#include <stdlib.h>
#include "listlinier.h"
#include "../boolean.h"

/* File : listlinier.c */
/* contoh ADT list berkait dengan representasi fisik pointer  */
/* Representasi address dengan pointer */
/* infotype adalah integer */

/* PROTOTYPE */
/****************** TEST LIST KOSONG ******************/
boolean IsEmptyListLinier (List L){
/* Mengirim true jika list kosong */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return First(L) == Nil;
}

/****************** PEMBUATAN LIST KOSONG ******************/
void CreateEmptyListLinier (List *L){
/* I.S. sembarang             */
/* F.S. Terbentuk list kosong */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    First(*L) = Nil;
}

/****************** Manajemen Memori ******************/
address Alokasi (infotype X){
/* Mengirimkan address hasil alokasi sebuah elemen */
/* Jika alokasi berhasil, maka address tidak nil, dan misalnya */
/* menghasilkan P, maka Info(P)=X, Next(P)=Nil */
/* Jika alokasi gagal, mengirimkan Nil */
    /* KAMUS LOKAL */
    address P;

    /* ALGORITMA */
    P = (address) malloc (sizeof(ElmtList));

    if (P != Nil) {
        Info(P) = X;
        Next(P) = Nil;
        return P;
    } else {
        return Nil;
    }
}
void DealokasiListLinier (address *P){
/* I.S. P terdefinisi */
/* F.S. P dikembalikan ke sistem */
/* Melakukan DealokasiListLinier/pengembalian address P */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    free(*P);
}

/****************** PENCARIAN SEBUAH ELEMEN LIST ******************/
address Search (List L, infotype X){
/* Mencari apakah ada elemen list dengan Info(P)= X */
/* Jika ada, mengirimkan address elemen tersebut. */
/* Jika tidak ada, mengirimkan Nil */
    /* KAMUS LOKAL */
    address P;

    /* ALGORITMA */
    P = First(L);

    while (P != Nil && Info(P) != X) {
        P = Next(P);
    }

    return P;
}
boolean FSearch (List L, address P){
/* Mencari apakah ada elemen list yang beralamat P */
/* Mengirimkan true jika ada, false jika tidak ada */
    /* KAMUS LOKAL */
    boolean found;
    address X;

    /* ALGORITMA */
    found = false;

    if (!IsEmptyListLinier(L)) {
        X = First(L);
        while (X != Nil && !found) {
            if (P == X) {
                found = true;
            }
            X = Next(X);
        }
    }

    return found;
}
address SearchPrec (List L, infotype X){
/* Mengirimkan address elemen sebelum elemen yang nilainya=X */
/* Mencari apakah ada elemen list dengan Info(P)=X */
/* Jika ada, mengirimkan address Prec, dengan Next(Prec)=P dan Info(P)=X. */
/* Jika tidak ada, mengirimkan Nil */
/* Jika P adalah elemen pertama, maka Prec=Nil */
/* Search dengan spesifikasi seperti ini menghindari */
/* traversal ulang jika setelah Search akan dilakukan operasi lain */
    /* KAMUS LOKAL */
    address P, Prec;

    /* ALGORITMA */
    P = First(L);
    Prec = Nil;

    if (!IsEmptyListLinier(L) && NbElmtList(L) > 1) {
        while (Next(P) != Nil && Info(P) != X) {
            Prec = P;
            P = Next(P);
        }
        if (Info(P) == X) {
            return Prec;
        }
        return Nil;
    }

    return Nil;
}

/****************** PRIMITIF BERDASARKAN NILAI ******************/
/*** PENAMBAHAN ELEMEN ***/
void InsVFirst (List *L, infotype X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen pertama dengan nilai X jika alokasi berhasil */
    /* KAMUS LOKAL */
    address P;

    /* ALGORITMA */
    P = Alokasi(X);

    if (P != Nil) {
        InsertFirst(L, P);
    }
}
void InsVLast (List *L, infotype X){
/* I.S. L mungkin kosong */
/* F.S. Melakukan alokasi sebuah elemen dan */
/* menambahkan elemen list di akhir: elemen terakhir yang baru */
/* bernilai X jika alokasi berhasil. Jika alokasi gagal: I.S.= F.S. */
    /* KAMUS LOKAL */
    address P;

    /* ALGORITMA */
    if (IsEmptyListLinier(*L)) {
        InsVFirst(L, X);
    } else {
        P = Alokasi(X);

        if (P != Nil) {
            InsertLast(L, P);
        }
    }
}

/*** PENGHAPUSAN ELEMEN ***/
void DelVFirst (List *L, infotype *X){
/* I.S. List L tidak kosong  */
/* F.S. Elemen pertama list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen pertama di-DealokasiListLinier */
    /* KAMUS LOKAL */
    address P;
    /* ALGORITMA */
    DelFirst(L, &P);
    *X = Info(P);
    DealokasiListLinier(&P);
}
void DelVLast (List *L, infotype *X){
/* I.S. list tidak kosong */
/* F.S. Elemen terakhir list dihapus: nilai info disimpan pada X */
/*      dan alamat elemen terakhir di-DealokasiListLinier */
    /* KAMUS LOKAL */
    address Last;

    /* ALGORITMA */
    DelLast(L, &Last);
    *X = Info(Last);
    DealokasiListLinier(&Last);
}

/****************** PRIMITIF BERDASARKAN ALAMAT ******************/
/*** PENAMBAHAN ELEMEN BERDASARKAN ALAMAT ***/
void InsertFirst (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. Menambahkan elemen ber-address P sebagai elemen pertama */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    Next(P) = First(*L);
    First(*L) = P;
}
void InsertAfter (List *L, address P, address Prec){
/* I.S. Prec pastilah elemen list dan bukan elemen terakhir, */
/*      P sudah dialokasi  */
/* F.S. Insert P sebagai elemen sesudah elemen beralamat Prec */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    Next(P) = Next(Prec);
    Next(Prec) = P;
}
void InsertLast (List *L, address P){
/* I.S. Sembarang, P sudah dialokasi  */
/* F.S. P ditambahkan sebagai elemen terakhir yang baru */
    /* KAMUS LOKAL */
    address Last;

    /* ALGORITMA */
    if (IsEmptyListLinier(*L)) {
        InsertFirst(L, P);
    } else {
        Last = First(*L);
        while(Next(Last) != Nil) {
            Last = Next(Last);
        }
    	InsertAfter(L, P, Last);
    }
}

/*** PENGHAPUSAN SEBUAH ELEMEN ***/
void DelFirst (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen pertama list sebelum penghapusan */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* First element yg baru adalah suksesor elemen pertama yang lama */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    *P = First(*L);

    if (Next(*P) != Nil) {
        First(*L) = Next(*P);
        Next(*P) = Nil;
    } else {
        CreateEmptyListLinier(L);
    }
}
void DelP (List *L, infotype X){
/* I.S. Sembarang */
/* F.S. Jika ada elemen list beraddress P, dengan Info(P)=X  */
/* Maka P dihapus dari list dan di-DealokasiListLinier */
/* Jika ada lebih dari satu elemen list dengan Info bernilai X */
/* maka yang dihapus hanya elemen pertama dengan Info = X */
/* Jika tidak ada elemen list dengan Info(P)=X, maka list tetap */
/* List mungkin menjadi kosong karena penghapusan */
    /* KAMUS LOKAL */
    address P, Prec;
    infotype A;
    boolean found=false;

    /* ALGORITMA */
    if (!IsEmptyListLinier(*L)) {
    	P = First(*L);
    	if (Info(P) == X) {
    		DelVFirst(L, &A);
    	} else {
    		Prec = Nil;
    		while ((P != Nil) && !found) {
    			if (Info(P) == X) {
    				DelAfter(L, &P, Prec);
    				DealokasiListLinier(&P);
    				found = true;
    			} else {
    				Prec = P;
    				P = Next(P);
    			}
    		}
    	}
    }
}
void DelLast (List *L, address *P){
/* I.S. List tidak kosong */
/* F.S. P adalah alamat elemen terakhir list sebelum penghapusan  */
/*      Elemen list berkurang satu (mungkin menjadi kosong) */
/* Last element baru adalah predesesor elemen terakhir yg lama, */
/* jika ada */
    /* KAMUS LOKAL */
    address Last, PrecLast;

    /* ALGORITMA */
    Last = First(*L);
    PrecLast = Nil;

    while (Next(Last) != Nil) {
        PrecLast = Last;
        Last = Next(Last);
    }

    *P = Last;

    if (First(*L) != Last) {
        Next(PrecLast) = Nil;
    } else {
    	CreateEmptyListLinier(L);
    }
}
void DelAfter (List *L, address *Pdel, address Prec){
/* I.S. List tidak kosong. Prec adalah anggota list  */
/* F.S. Menghapus Next(Prec): */
/*      Pdel adalah alamat elemen list yang dihapus  */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    *Pdel = Next(Prec);
    Next(Prec) = Next(*Pdel);
    Next(*Pdel) = Nil;     
}

/****************** PROSES SEMUA ELEMEN LIST ******************/
void PrintInfo (List L){
/* I.S. List mungkin kosong */
/* F.S. Jika list tidak kosong, iai list dicetak ke kanan: [e1,e2,...,en] */
/* Contoh : jika ada tiga elemen bernilai 1, 20, 30 akan dicetak: [1,20,30] */
/* Jika list kosong : menulis [] */
/* Tidak ada tambahan karakter apa pun di awal, akhir, atau di tengah */
    /* KAMUS LOKAL */
    address P;
    /* ALGORITMA */
    if (IsEmptyListLinier(L)) {
        printf("[]");
    } else {
        printf("[");
        P = First(L);
        while (P != Nil) {
            if (Next(P) == Nil) {
                printf("%d]", Info(P));
            } else {
                printf("%d,", Info(P));
            }
            P = Next(P);
        }
    }
}
int NbElmtList (List L){
/* Mengirimkan banyaknya elemen list; mengirimkan 0 jika list kosong */
    /* KAMUS LOKAL */
    address P;
    int N=0;

    /* ALGORITMA */
    if (IsEmptyListLinier(L)) {
        return 0;
    }

    P = First(L);

    while (P != Nil) {
        N += 1;
        P = Next(P);
    }

    return N;
}

/*** Prekondisi untuk Max/Min/rata-rata : List tidak kosong ***/
infotype Max (List L){
/* Mengirimkan nilai Info(P) yang maksimum */
    /* KAMUS LOKAL */
    infotype max;
    address P;

    /* ALGORITMA */
    max = Info(First(L));
    P = Next(First(L));

    while (P != Nil) {
        if (Info(P) > max) {
            max = Info(P);
        }
        P = Next(P);
    }

    return max;
}
address AdrMax (List L){
/* Mengirimkan address P, dengan info(P) yang bernilai maksimum */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return Search(L, Max(L));
}
infotype Min (List L) {
/* Mengirimkan nilai Info(P) yang minimum */
    /* KAMUS LOKAL */
    infotype min;
    address P;

    /* ALGORITMA */
    min = Info(First(L));
    P = Next(First(L));

    while (P != Nil) {
        if (Info(P) < min) {
            min = Info(P);
        }
        P = Next(P);
    }

    return min;
}
address AdrMin (List L){
/* Mengirimkan address P, dengan info(P) yang bernilai minimum */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    return Search(L, Min(L));
}

float Average (List L){
/* Mengirimkan nilai rata-rata info(P) */
    /* KAMUS LOKAL */
    address P;
    float sum, count;

    /* ALGORITMA */
    sum = 0;
    count = 0;

    if (!IsEmptyListLinier(L)) {
        P = First(L);

        while (P != Nil) {  
            sum += Info(P);
            count += 1;
            P = Next(P);
        }

        return (sum/count);
    } else {
        return 0;
    }
}
/****************** PROSES TERHADAP LIST ******************/
void DelAll (List *L){
/* Delete semua elemen list dan alamat elemen di-DealokasiListLinier */
    /* KAMUS LOKAL */
    infotype X;

    /* ALGORITMA */
    while (!IsEmptyListLinier(*L)) {
        DelVFirst(L, &X);
    }
}

void InversList (List *L){
/* I.S. sembarang. */
/* F.S. elemen list dibalik : */
/* Elemen terakhir menjadi elemen pertama, dan seterusnya. */
/* Membalik elemen list, tanpa melakukan alokasi/DealokasiListLinier. */
    /* KAMUS LOKAL */
    address P;
    List result;

    /* ALGORITMA */
    if (!IsEmptyListLinier(*L) && NbElmtList(*L)>1) {
        CreateEmptyListLinier(&result);
        while (!IsEmptyListLinier(*L)) {
            DelLast(L, &P);
            InsertLast(&result, P);
        }
        First(*L) = First(result);
    }
}

List FInversList (List L){
/* Mengirimkan list baru, hasil invers dari L */
/* dengan menyalin semua elemn list. Alokasi mungkin gagal. */
/* Jika alokasi gagal, hasilnya list kosong */
/* dan semua elemen yang terlanjur di-alokasi, harus diDealokasiListLinier */
    /* KAMUS LOKAL */
    List result;
    boolean error = false;
    infotype X;

    /* ALGORITMA */
    CreateEmptyListLinier(&result);
    while(!error && !IsEmptyListLinier(L)) {
        DelVFirst(&L, &X);
        
        if (Alokasi(X) == Nil) {
            error = true;
        } else {
            InsVFirst(&result, X);
        }
    }

    if (error) {
        DelAll(&result);
    }
    return result;
}

void CopyList (List *L1, List *L2){
/* I.S. L1 sembarang. F.S. L2=L1 */
/* L1 dan L2 "menunjuk" kepada list yang sama.*/
/* Tidak ada alokasi/DealokasiListLinier elemen */
    /* KAMUS LOKAL */

    /* ALGORITMA */
    CreateEmptyListLinier(L2);
    First(*L2) = First(*L1);
}

List FCopyList (List L){
/* Mengirimkan list yang merupakan salinan L */
/* dengan melakukan alokasi. */
/* Jika ada alokasi gagal, hasilnya list kosong dan */
/* semua elemen yang terlanjur di-alokasi, harus diDealokasiListLinier */
    /* KAMUS LOKAL */
    List result;
    boolean error = false;
    address P;
    address X;

    /* ALGORITMA */
    CreateEmptyListLinier(&result);
    P = First(L);

    while(!error && P != Nil) {
        X = Alokasi(Info(P));
        
        if (X == Nil) {
            error = true;
        } else {
            InsertLast(&result, X);
            P = Next(P);
        }
    }

    if (error) {
        DelAll(&result);
    }
    return result;
}

void CpAlokList (List Lin, List *Lout){
/* I.S. Lin sembarang. */
/* F.S. Jika semua alokasi berhasil,maka Lout berisi hasil copy Lin */
/* Jika ada alokasi yang gagal, maka Lout=Nil dan semua elemen yang terlanjur dialokasi, diDealokasiListLinier */
/* dengan melakukan alokasi elemen. */
/* Lout adalah list kosong jika ada alokasi elemen yang gagal */
    /* KAMUS LOKAL */
    List copy;

    /* ALGORITMA */
    copy = FCopyList(Lin);
    First(*Lout) = First(copy);
}

void Konkat (List L1, List L2, List * L3){
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 tetap, L3 adalah hasil konkatenasi L1 & L2 */
/* Jika semua alokasi berhasil, maka L3 adalah hasil konkatenasi*/
/* Jika ada alokasi yang gagal, semua elemen yang sudah dialokasi */
/* harus di-DealokasiListLinier dan L3=Nil*/
/* Konkatenasi dua buah list : L1 & L2 menghasilkan L3 yang "baru" */
/* Elemen L3 adalah hasil alokasi elemen yang “baru”. */
/* Jika ada alokasi yang gagal, maka L3 harus bernilai Nil*/
/* dan semua elemen yang pernah dialokasi diDealokasiListLinier */
    /* KAMUS LOKAL */
    boolean error;
    infotype X;

    /* ALGORITMA */
    error = false;

    if (IsEmptyListLinier(L1) && IsEmptyListLinier(L2)) {
        CreateEmptyListLinier(L3);
    } else if (IsEmptyListLinier(L1) && !IsEmptyListLinier(L2)) {
        CpAlokList(L2, L3);
    } else if (!IsEmptyListLinier(L1) && IsEmptyListLinier(L2)) {
        CpAlokList(L1, L3);
    } else {
        CpAlokList(L1, L3);
        if (!IsEmptyListLinier(*L3)) {
            while (!IsEmptyListLinier(L2) && !error) {
                DelVFirst(&L2, &X);
                
                if (Alokasi(X) == Nil) {
                    error = true;
                } else {
                    InsVLast(L3, X);
                }
            }
            if (error) {
                DelAll(L3);
            }
        }
    }
}

void Konkat1 (List *L1, List *L2, List *L3){
/* I.S. L1 dan L2 sembarang */
/* F.S. L1 dan L2 kosong, L3 adalah hasil konkatenasi L1 & L2 */
/* Konkatenasi dua buah list : L1 dan L2    */
/* menghasilkan L3 yang baru (dengan elemen list L1 dan L2) */
/* dan L1 serta L2 menjadi list kosong.*/
/* Tidak ada alokasi/DealokasiListLinier pada prosedur ini */
    /* KAMUS LOKAL */
    address P;

    /* ALGORITMA */
    if (IsEmptyListLinier(*L1)) {
        First(*L3) = First(*L2);
    } else if (IsEmptyListLinier(*L2)) {
        First(*L3) = First(*L1);
    } else {
        First(*L3) = First(*L1);
        P = First(*L1);
        while (Next(P) != Nil) {
            P = Next(P);
        }
        Next(P) = First(*L2);
    }
    CreateEmptyListLinier(L1);
    CreateEmptyListLinier(L2);
}

void PecahList (List *L1, List *L2, List L){
/* I.S. L mungkin kosong */
/* F.S. Berdasarkan L, dibentuk dua buah list L1 dan L2 */
/* L tidak berubah: untuk membentuk L1 dan L2 harus alokasi */
/* L1 berisi separuh elemen L dan L2 berisi sisa elemen L */
/* Jika elemen L ganjil, maka separuh adalah NbElmt(L) div 2 */
    /* KAMUS LOKAL */
    infotype X;
    int start, end;
    int i, j;

    /* ALGORITMA */
    CreateEmptyListLinier(L1);
    CreateEmptyListLinier(L2);

    if (!IsEmptyListLinier(L)) {
        if (NbElmtList(L) == 1) {
            DelVFirst(&L, &X);
            InsVFirst(L2, X);
        } else {
            start = NbElmtList(L)/2;
            end = NbElmtList(L) - start;

            for (i = 0; i < start; i++) {
                DelVFirst(&L, &X);
                InsVLast(L1, X);
            }

            for (j = 0; j < end; j++) {
                DelVFirst(&L, &X);
                InsVLast(L2, X);
            }
        }
    }
}