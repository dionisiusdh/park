#include "prioqueue.h"
#include "../pengunjung/pengunjung.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

/* ********* Prototype ********* */
boolean IsEmptyQueue (Queue Q)
/* Mengirim true jika Q kosong: lihat definisi di atas */
{
    return (Head(Q)==NilQueue) && (Tail(Q)==NilQueue);
}

boolean IsFullQueue (Queue Q)
/* Mengirim true jika tabel penampung elemen Q sudah penuh */
/* yaitu mengandung elemen sebanyak MaxEl */
{
    return NBElmtQueue(Q)==MaxElQueue(Q);
}

int NBElmtQueue (Queue Q)
/* Mengirimkan banyaknya elemen queue. Mengirimkan 0 jika Q kosong. */
{
    if(IsEmptyQueue(Q)){
        return 0;
    }
    else{
        if(Head(Q)<=Tail(Q)){
            return Tail(Q)-Head(Q)+1;
        }
        else{
            return (MaxElQueue(Q)-Head(Q)+1+Tail(Q));
        }
    }
}
/* *** Kreator *** */
void CreateEmptyQueue (Queue * Q, int Max)
/* I.S. sembarang */
/* F.S. Sebuah Q kosong terbentuk dan salah satu kondisi sbb: */
/* Jika alokasi berhasil, Tabel memori dialokasi berukuran Max+1 */
/* atau : jika alokasi gagal, Q kosong dg MaxEl=0 */
/* Proses : Melakukan alokasi, membuat sebuah Q kosong */
{   (*Q).T = (queuetype*) malloc ((Max+1)*sizeof(queuetype));
    if((*Q).T!=NULL){
        MaxElQueue(*Q) = Max;
        Head(*Q) = NilQueue;
        Tail(*Q) = NilQueue;
    }
    else{
        MaxElQueue(*Q) = 0;
    }
}
/* *** Destruktor *** */
void DeAlokasiQueue (Queue * Q)
/* Proses: Mengembalikan memori Q */
/* I.S. Q pernah dialokasi */
/* F.S. Q menjadi tidak terdefinisi lagi, MaxEl(Q) diset 0 */
{
    free((*Q).T);
    MaxElQueue(*Q) = 0;
}

/* *** Primitif Add/Delete *** */
void AddQueue (Queue * Q, queuetype X)
/* Proses: Menambahkan X pada Q dengan aturan priority queue, terurut mengecil berdasarkan prio */
/* I.S. Q mungkin kosong, tabel penampung elemen Q TIDAK penuh */
/* F.S. X menjadi TAIL yang baru, TAIL "maju" dengan mekanisme circular buffer;
        elemen baru disisipkan pada posisi yang tepat sesuai dengan prioritas */
{
    if(IsEmptyQueue(*Q)){
        (*Q).T[NilQueue+1] = X;
        Head(*Q) = NilQueue+1;
        Tail(*Q) = NilQueue+1;
    }
    else{
        if((Head(*Q)<=Tail(*Q)) && (Tail(*Q)<MaxElQueue(*Q)-1)) {
            address i = Head(*Q);
            while(PrioQueue(ElmtQueue(*Q,i))>PrioQueue(X)){
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
            while(PrioQueue(ElmtQueue(*Q,i))>PrioQueue(X) && i<MaxElQueue(*Q)){
                i++;
            }
            if(i==MaxElQueue(*Q)){
                i = NilQueue+1;
                while(PrioQueue(ElmtQueue(*Q,i))>PrioQueue(X)){
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
                for(j=Tail(*Q)+1;j>NilQueue+1;j--){
                    (*Q).T[j] = (*Q).T[j-1];
                }
                (*Q).T[j] = (*Q).T[MaxElQueue(*Q)-1];
                for(j=MaxElQueue(*Q)-1;j>i;j--){
                    (*Q).T[j] = (*Q).T[j-1];
                }
                (*Q).T[i] = X;
            }
            Tail(*Q) += 1;
        }
        else if(Head(*Q)<=Tail(*Q) && Tail(*Q)==MaxElQueue(*Q)-1){
            if(PrioQueue(ElmtQueue(*Q,MaxElQueue(*Q)-1))>PrioQueue(X)){
                (*Q).T[NilQueue+1] = X;
                Tail(*Q) = NilQueue+1;
            }
            else{
                address i = Head(*Q);
                while(PrioQueue(ElmtQueue(*Q,i))>PrioQueue(X)){
                    i++;
                }
                int j;
                (*Q).T[NilQueue+1] = InfoTail(*Q);
                for(j=Tail(*Q);j>i;j--){
                    (*Q).T[j] = (*Q).T[j-1];
                }
                (*Q).T[i] = X;
                Tail(*Q) = NilQueue+1;
            }
            Tail(*Q) += 1;   
        }
    }
}

void DelQueue (Queue * Q, queuetype * X, Kata Wahana)
/* Proses: Menghapus X pada Q dengan aturan FIFO */
/* I.S. Q tidak mungkin kosong */
/* F.S. X = NilQueueai elemen HEAD pd I.S., HEAD "maju" dengan mekanisme circular buffer; 
        Q mungkin kosong */
{   //KAMUS
    int lokasi,i;
    //ALGORITMA
    lokasi = SearchQueue(*Q,Wahana);
    if (lokasi!=0){
        if (NBElmtQueue(*Q)==1){
            *X = InfoHead(*Q);
            Head(*Q) = NilQueue;
            Tail(*Q) = NilQueue;
        }
        else{
            if (lokasi < Head(*Q)){
                *X = ElmtQueue(*Q,lokasi);
                i = lokasi + 1;
                while (i<=Tail(*Q)){
                    ElmtQueue(*Q,i-1) = ElmtQueue(*Q,i);
                }
                if (Tail(*Q) == 1){
                    Tail(*Q) = 5;
                }
                else{
                    Tail(*Q) -= 1;
                }
            }
            else if (lokasi > Head(*Q)){
                if (Head(*Q) < Tail(*Q)){
                    *X = ElmtQueue(*Q,lokasi);
                }
            }     
        } 
    }

    // if(NBElmtQueue(*Q)==1){
    //     *X = InfoHead(*Q);
    //     Head(*Q) = NilQueue;
    //     Tail(*Q) = NilQueue;
    // }
    // else if(Head(*Q)==MaxElQueue(*Q)-1){
    //     *X = InfoHead(*Q);
    //     Head(*Q) = NilQueue+1;
    // }
    // else{
    //     *X = InfoHead(*Q);
    //     Head(*Q)++;
    // }
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
// Wahana | Nama | Kesabaran | 
{   //KAMUS
    int i;
    //ALGORITMA
    printf("Antrian [%d/5]\n", NBElmtQueue(Q));

    if (Tail(Q)<Head(Q)){
        for (i= Head(Q); i<=NBElmtQueue(Q); i++){
            TulisWahana(Pengunjung(ElmtQueue(Q,i)));
            printf(" | Kesabaran: %d", Kesabaran(Pengunjung(ElmtQueue(Q,i))));
            printf(" | Customer %c\n", NamaPengunjung(ElmtQueue(Q,i)));
        }
        for (i= 1; i<=Tail(Q); i++){
            TulisWahana(Pengunjung(ElmtQueue(Q,i)));
            printf(" | Kesabaran: %d", Kesabaran(Pengunjung(ElmtQueue(Q,i))));
            printf(" | Customer %c\n",NamaPengunjung(ElmtQueue(Q,i)));
        }
    }
    else{
        for(i=Head(Q);i<=Tail(Q);i++){
            TulisWahana(Pengunjung(ElmtQueue(Q,i)));
            printf(" | Kesabaran: %d", Kesabaran(Pengunjung(ElmtQueue(Q,i))));
            printf(" | Customer %c\n",NamaPengunjung(ElmtQueue(Q,i)));
        }
    }  
}

int SearchQueue (Queue Q, Kata Wahana){
    //KAMUS LOKAL
    int i=Head(Q);
    boolean found = false;
    //ALGORITMA
    if (Head(Q) > Tail(Q)){
        while (i<=MaxElQueue(Q) && !found){
            if (SearchPengunjung(Pengunjung(ElmtQueue(Q,i)), Wahana)){
                found = true;
            }
            else{
                i++;
            }
        }
        while (i<=Tail(Q) && !found){
            if (SearchPengunjung(Pengunjung(ElmtQueue(Q,i)), Wahana)){
                found = true;
            }
            else{
                i++;
            }
        }
        if (found == true){
            return i;
        }
        else{
            return 0;           
        }
    }
    else {
        while (i<=Tail(Q) && !found){
            if (SearchPengunjung(Pengunjung(ElmtQueue(Q,i)), Wahana)){
                found = true;
            }
            else{
                i++;
            }
        }
        return i;
    }
}

void initQueue (Queue *Antrian) {
  // KAMUS LOKAL
  int jumlahOrang, i, nama;
  PENGUNJUNG P;

  // ALGORITMA
  srand(time(NULL));
  jumlahOrang = 1 + rand()%4;

  CreateEmptyQueue(Antrian, jumlahOrang);
  i=1;
  nama = 65;
  while (i<=jumlahOrang) {
    MakePENGUNJUNG(&P, i);
    Pengunjung(ElmtQueue(*Antrian,i)) = P;
    NamaPengunjung(ElmtQueue(*Antrian,i)) = (char) nama;
    PrioQueue(ElmtQueue(*Antrian,i)) = 0;
    i++;
    nama++;
  }
  Head(*Antrian) = 1;
  Tail(*Antrian) = i-1;
}