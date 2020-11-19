#include "prioqueue.h"
#include <stdlib.h>
#include <stdio.h>

/* ********* Prototype ********* */
boolean IsEmpty (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return (Head(Q)==Nil) && (Tail(Q)==Nil);
}

boolean IsFull (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    return NBElmt(Q)==MaxEl(Q);
}

int NBElmt (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if(IsEmpty(Q)){
        return 0;
    }
    else{
        if(Head(Q)<=Tail(Q)){
            return Tail(Q)-Head(Q)+1;
        }
        else{
            return (MaxEl(Q)-Head(Q)+1+Tail(Q));
        }
    }
}
/* *** Kreator *** */
void CreateEmpty (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{
    (*Q).T = (infotype*) malloc ((Max+1)*sizeof(infotype));
    if((*Q).T!=NULL){
        MaxEl(*Q) = Max;
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else{
        MaxEl(*Q) = 0;
    }
}
/* *** Destruktor *** */
void DeAlokasi(Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    free((*Q).T);
    MaxEl(*Q) = 0;
}

/* *** Primitif Add/Delete *** */
void Add (Queue * Q, infotype X)
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer;
        elemen baru disisipkan pada posisi yang tepat sesuai dengan prioritas */
{
    if(IsEmpty(*Q)){
        (*Q).T[Nil+1] = X;
        Head(*Q) = Nil+1;
        Tail(*Q) = Nil+1;
    }
    else{
        if((Head(*Q)<=Tail(*Q)) && (Tail(*Q)<MaxEl(*Q)-1)) {
            address i = Head(*Q);
            while(Prio(Elmt(*Q,i))>Prio(X)){
                i++;
            }
            int j;
            for(j=Tail(*Q)+1;j>i;j--){
                (*Q).T[j] = (*Q).T[j-1];
            }
            (*Q).T[i] = X;
            Tail(*Q) += 1;
        }
        else if((Head(*Q)>Tail(*Q))) {
            address i = Head(*Q);
            while(Prio(Elmt(*Q,i))>Prio(X) && i<MaxEl(*Q)){
                i++;
            }
            if(i==MaxEl(*Q)){
                i = Nil+1;
                while(Prio(Elmt(*Q,i))>Prio(X)){
                    i++;
                }
                int j;
                for(j=Tail(*Q)+1;j>i;j--){
                    (*Q).T[j] = (*Q).T[j-1];
                }
                (*Q).T[i] = X;
            }
            else{
                int j;
                for(j=Tail(*Q)+1;j>Nil+1;j--){
                    (*Q).T[j] = (*Q).T[j-1];
                }
                (*Q).T[j] = (*Q).T[MaxEl(*Q)-1];
                for(j=MaxEl(*Q)-1;j>i;j--){
                    (*Q).T[j] = (*Q).T[j-1];
                }
                (*Q).T[i] = X;
            }
            Tail(*Q) += 1;
        }
        else if(Head(*Q)<=Tail(*Q) && Tail(*Q)==MaxEl(*Q)-1){
            if(Prio(Elmt(*Q,MaxEl(*Q)-1))>Prio(X)){
                (*Q).T[Nil+1] = X;
                Tail(*Q) = Nil+1;
            }
            else{
                address i = Head(*Q);
                while(Prio(Elmt(*Q,i))>Prio(X)){
                    i++;
                }
                int j;
                (*Q).T[Nil+1] = InfoTail(*Q);
                for(j=Tail(*Q);j>i;j--){
                    (*Q).T[j] = (*Q).T[j-1];
                }
                (*Q).T[i] = X;
                Tail(*Q) = Nil+1;
            }
            Tail(*Q) += 1;   
        }
    }
}

void Del (Queue * Q, infotype * X)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = nilai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{
    if(NBElmt(*Q)==1){
        *X = InfoHead(*Q);
        Head(*Q) = Nil;
        Tail(*Q) = Nil;
    }
    else if(Head(*Q)==MaxEl(*Q)-1){
        *X = InfoHead(*Q);
        Head(*Q) = Nil+1;
    }
    else{
        *X = InfoHead(*Q);
        Head(*Q)++;
    }
}
/* Operasi Tambahan */
void PrintQueue (Queue Q)
/* Mencetak isi queue Q ke layar */
/* I.S. Q terdefinisi, mungkin kosong */
/* F.S. Q tercetak ke layar dengan format:
<prio-1> <elemen-1>
...
<prio-n> <elemen-n>
#
*/
{ 
    int i;
    if(Tail(Q)<Head(Q)){
        for(i=Head(Q);i<=MaxEl(Q)-1;i++){
            printf("%d %d\n",Prio(Elmt(Q,i)),Info(Elmt(Q,i)));
        }
        for(i=1;i<=Tail(Q);i++){
            printf("%d %d\n",Prio(Elmt(Q,i)),Info(Elmt(Q,i)));
        }
    }
    else{
        for(i=Head(Q);i<=Tail(Q);i++){
            printf("%d %d\n",Prio(Elmt(Q,i)),Info(Elmt(Q,i)));
        }
    }  
}